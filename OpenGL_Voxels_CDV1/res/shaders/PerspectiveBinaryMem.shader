#shader vertex
#version 410 core

layout(location = 0) in uint binVertex;

out vec2 v_TexCoord;
out float v_lightValue;

uniform vec3 u_ChunkPos;
uniform mat4 u_MVP; //model-view-projection matrix

vec2 texCoords[4] = vec2[4](
    vec2(0.0f, 0.0f),
    vec2(1.0f, 0.0f),
    vec2(0.0f, 1.0f),
    vec2(1.0f, 1.0f)
    );


void main() {
    // Determine 3d coordinate of this vertex with first 15 bits
    // 5 bits per axis allows 2^5 = 32 possible values. Each chunk is size 31x31x31 to fit within this range.
    // This downsizing is necessary since edge vertices will project their vertex coordinates 1 above the max bound (32 here)
    float x = float((binVertex & 0x1Fu) >> 0u);
    float y = float((binVertex & 0x3E0u) >> 5u);
    float z = float((binVertex & 0x7C00u) >> 10u);

    // Convert the vertex coordinate from model/chunk/local space to world space
    x += u_ChunkPos.x;
    y += u_ChunkPos.y;
    z += u_ChunkPos.z;

    // Collate a coordinate value and multiply by Model-View-Project matrix to generate screen position
    // This is passed to the fragment shader for scanline rendering
    vec4 worldPos = vec4(x, y, z, 1.0);
    gl_Position = u_MVP * worldPos;

    // Parse additional bit flags from the following layout:
    // 3-10-2-5-5-5
    // LightValue-TextureID-BlockID-z-y-x
    uint uvID = (binVertex >> 15u) & 3;
    uint textureID = (binVertex >> 17u) & 1023;
    uint lightValue = ((binVertex >> 27u) & 7);
    float lightValueF = float(lightValue) / 7;

    // Pass final calculations into the fragment shader
    v_TexCoord = texCoords[uvID];
    v_lightValue = lightValueF;
}


#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_lightValue;
//in vec4 v_WorldPosition;

uniform vec4 u_Albedo_Color;
uniform sampler2D u_Texture;

void main() {
    vec4 texColor = texture(u_Texture, v_TexCoord);
    if (texColor.a == 0)
        discard;

    color = (texColor * u_Albedo_Color) * v_lightValue;
}
