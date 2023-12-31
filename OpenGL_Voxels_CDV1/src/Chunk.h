#pragma once
#include <vector>
#include <iostream>
#include "Block.h"
#include "int3.h"

#include <FastNoise/FastNoise.h>

class Chunk {
private:
    std::vector<Block> blocks;

    int b_index(int3 ind) {return ((ind.z * chunkSize + ind.y) * chunkSize + ind.x);}
    int b_index(int x, int y, int z) {return ((z * chunkSize + y) * chunkSize + x);}
public:
    int3 worldIndex;
    int chunkSize;
    int blockCount;

    Chunk();
    Chunk(int3 _worldIndex, short _chunkSize);
    
    Block Get_Block(int3 localIndex);
    void Set_Block(int3 localIndex, Block block);

    bool InBounds(int3 pos);
};