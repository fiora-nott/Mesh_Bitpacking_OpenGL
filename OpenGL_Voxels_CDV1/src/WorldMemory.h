#pragma once
#include "Chunk.h"
#include "int3.h"

class WorldMemory
{
private:
	std::vector<Chunk> chunks;
public:
    int chunkCount;
    int chunkSize;
    int3 origin;
    int memSize;

	WorldMemory(int3 _origin, int _memSize, int _chunkSize);

    int CIndex(int3 ind);
    int CIndex(int x, int y, int z);

    bool InMemoryBounds(int3 worldIndex);

	Chunk* GetChunkLocal(int3 localIndex);
	Chunk* GetChunkWorld(int3 worldIndex);
	void SetChunk(int3 worldIndex, Chunk chunk);

    Block GetBlock(int3 worldIndex, int3 blockIndex);
    void SetBlock(int3 worldIndex, int3 blockIndex, Block newBlock);

};
