#include "Window.h"


void Window::CreateWindow(int width, int height)  {
    std::cout << "(Window.cpp) Creating GLFW window + setting context" << std::endl;
    /* Initialize the library */
    if (!glfwInit())
        return;

    //set our program to use vertex arrays
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Draco Voyage", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    //set private variables to save pixel dimensions for Camera matrices
    w_PixelWidth = width;
    w_PixelHeight = height;

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
        
    //synchronize fps cap to monitor's refresh rate
    glfwSwapInterval(1);

    //initialize GLEW wrapper to allow access to all OpenGL functions!
    if (glewInit() != GLEW_OK)
        std::cout << "~(window.cpp) Glew_Init failed!" << std::endl;

    std::cout << "(Window.cpp) Current openGL version: " << glGetString(GL_VERSION) << std::endl;

}

void Window::LaunchGameLoop(WorldMemory worldMem) {
    std::cout << "(Window.cpp) Starting Game Loop" << std::endl;

    //create a local scope to make sure buffers are destructed before glfw terminate
    //this prevents an infinite loop that only occurs since we do everything in 1 window.
    //this glitch can be seen when the console stays active after closing GLFW window
    {
        //  Creates chunk meshes
        //layout of vertices in the VBO
        VertexBufferLayout cubeLayout;
        cubeLayout.Push<float>(1);


        Material blockMaterial("PerspectiveBinaryMem.shader");
        blockMaterial.AddTexture("u_Texture", "terracotta.png");
        
        /*
        CMesh mesh = ChunkMesher::GenerateMesh(worldMem.Get_Chunk(int3(0, 0, 0)));
        Model chunkModel;
        chunkModel.SetMesh(mesh);
        chunkModel.GenerateBuffers(cubeLayout);
        chunkModel.SetMaterial(&blockMaterial);*/
        
        
        std::vector<Model> chunkModels;
        for (int x = 0; x < worldMem.memSize; x++) {
            for (int y = 0; y < worldMem.memSize; y++) {
                for (int z = 0; z < worldMem.memSize; z++) {
                    CMesh mesh = ChunkMesher::GenerateMesh(&worldMem, worldMem.GetChunkLocal(int3(x, y, z)));
                    Model model(mesh);
                    model.GenerateBuffers(cubeLayout);
                    model.SetMaterial(&blockMaterial);
                    chunkModels.push_back(model);
                }
            }
        }

        //create a camera to render our scene and send matrices to the shader
        Camera cam(w_PixelWidth, w_PixelHeight, glm::vec3(0.0f, 0.0f, 5.0f));
        //create a singular renderer instance to handle drawcalls every frame
        Renderer renderer;


        //cache floats for tracking FPS
        double prevTime = 0.0;
        double crntTime = 0.0;
        double timeDiff;
        unsigned int counter = 0;


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            //update FPS
            crntTime = glfwGetTime();
            timeDiff = crntTime - prevTime;
            counter++;
            if (timeDiff >= 1.0 / 2.0) {
                std::string FPS = std::to_string((1.0 / timeDiff) * counter);
                std::string ms = std::to_string((timeDiff / counter) * 1000);
                std::string newTitle = "Draco Voyage - " + FPS + "FPS / " + ms + "ms";
                glfwSetWindowTitle(window, newTitle.c_str());
                prevTime = crntTime;
                counter = 0;
            }

            
            /* Render here */
            renderer.ClearColor(0.6, 0.7, 0.8, 1.0);
            
            //create matrices for rendering geometry + CAMERA
            cam.TakeInputs(window);

            
            blockMaterial.Bind();
            cam.SendMatrix(80.0f, 0.1f, 400.0f, blockMaterial.shader, "u_MVP");
            blockMaterial.shader.SetUniform4f("u_Albedo_Color",
                1.0f, //sin(glfwGetTime()) / 2 + 0.5f,
                1.0f, //sin(glfwGetTime() * 1.32) / 2 + 0.5f,
                1.0f, //sin(glfwGetTime() * 1.847) / 2 + 0.5f,
                1.0f);

            for (int i = 0; i < chunkModels.size(); i++) {
                Model model = chunkModels[i];
                int3 origin = model.mesh.world_origin;
                blockMaterial.shader.SetUniform3f("u_ChunkPos", origin.x, origin.y, origin.z);
                renderer.Draw(model);
            }

            /*
            chunkModel.material->Bind();
            cam.SendMatrix(80.0f, 0.1f, 400.0f, chunkModel.material->shader, "u_MVP");

            chunkModel.material->shader.SetUniform4f("u_Albedo_Color",
                sin(glfwGetTime()) / 2 + 0.5f,
                sin(glfwGetTime() * 1.32) / 2 + 0.5f,
                sin(glfwGetTime() * 1.847) / 2 + 0.5f,
                1.0f);

            renderer.Draw(chunkModel);
            */

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        for (Model m : chunkModels)
            m.glDelete();
        //chunkModel.glDelete();
        blockMaterial.glDelete();

    }
    //call the Window class's destroy function and end the game
    DestroyWindow();
}

void Window::DestroyWindow() {
    std::cout << "(Window.cpp) Destroying GLFW window" << std::endl;
    glfwTerminate();
}