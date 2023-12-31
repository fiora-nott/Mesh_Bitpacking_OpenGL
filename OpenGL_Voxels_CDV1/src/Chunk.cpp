#include "Chunk.h"


Chunk::Chunk() {
    std::cout << "using default chunk constructor!!! nonono" << std::endl;
    worldIndex = int3(0, 0, 0);
    chunkSize = 0;
    blockCount = 0;
}

Chunk::Chunk(int3 _worldIndex, short _chunkSize) {
    worldIndex = _worldIndex;
    chunkSize = _chunkSize;
    blockCount = (int)powf(chunkSize, 3);

    blocks.reserve(blockCount);
    int3 worldPos = worldIndex * chunkSize;

    FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("BwA=");

    std::vector<float> noiseOutput(blockCount);
    fnGenerator->GenUniformGrid3D(noiseOutput.data(), 
        worldPos.x, worldPos.y, worldPos.z, 
        chunkSize, chunkSize, chunkSize, 
        0.08f, 1337);
    int i = 0;

    for (int z = 0; z < chunkSize; z++) {
        for (int y = 0; y < chunkSize; y++) {
            for (int x = 0; x < chunkSize; x++) {
                float noiseValue = noiseOutput[i++];
                if (noiseValue < 0.1)
                    blocks.push_back(Block::DIAMOND);
                else
                    blocks.push_back(Block::AIR);
            }
        }
    }
    
    //for (int i = 0; i < blockCount; i++) {

        /*
        if (i % 2 == 0)
            blocks.push_back(Block::DIAMOND);
        else
            blocks.push_back(Block::AIR);*/
        
        /*
        if (rand() % 5 == 0) {
            if (rand() % 2 == 0)
                blocks.push_back(Block::DIAMOND);
            else
                blocks.push_back(Block::DIRT);
        }
        else
            blocks.push_back(Block::AIR);*/
    //}
}

Block Chunk::Get_Block(int3 localIndex) {
    return blocks[b_index(localIndex)];
}

void Chunk::Set_Block(int3 localIndex, Block block) {
    blocks[b_index(localIndex)] = block;
}

bool Chunk::InBounds(int3 pos) {
    if (pos.x < 0 || pos.y < 0 || pos.z < 0 ||
        pos.x >= chunkSize || pos.y >= chunkSize || pos.z >= chunkSize)
        return false;
    return true;
}

