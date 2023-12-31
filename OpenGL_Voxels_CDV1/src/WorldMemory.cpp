#include "WorldMemory.h"

WorldMemory::WorldMemory(int3 _origin, int _memSize, int _chunkSize) {
	origin = _origin;
	memSize = _memSize;
	chunkSize = _chunkSize;
	chunkCount = (int)powf(memSize, 3);

	chunks.reserve(chunkCount);
	for (int x = 0; x < memSize; x++)
	for (int y = 0; y < memSize; y++)
	for (int z = 0; z < memSize; z++)
		chunks.push_back(Chunk(
				origin + int3(x, y, z),
				chunkSize
			));
}

int WorldMemory::CIndex(int3 ind) {
	return ((ind.x * memSize + ind.y) * memSize + ind.z);
}

int WorldMemory::CIndex(int x, int y, int z) {
	return ((x * memSize + y) * memSize + z);
}

bool WorldMemory::InMemoryBounds(int3 localIndex) {
	if (localIndex.x < 0 || localIndex.y < 0 || localIndex.z < 0 ||
		localIndex.x >= memSize || localIndex.y >= memSize || localIndex.z >= memSize)
		return false;
	return true;
}


Chunk* WorldMemory::GetChunkLocal(int3 localIndex) {
	if (InMemoryBounds(localIndex))
		//std::cout << "found chunk at index " << localIndex.x << localIndex.y << localIndex.z << std::endl;
		return &chunks[CIndex(localIndex)];
	else
		std::cout << "cannot find chunk at index " << localIndex.x << localIndex.y << localIndex.z << std::endl;
	return NULL;
}

Chunk* WorldMemory::GetChunkWorld(int3 worldIndex) {
	int3 localIndex = worldIndex - origin;
	return GetChunkLocal(localIndex);
}

void WorldMemory::SetChunk(int3 worldIndex, Chunk chunk) {
	int3 localIndex = worldIndex - origin;
	if (InMemoryBounds(localIndex))
		chunks[CIndex(localIndex)] = chunk;
	else
		std::cout << "cannot find chunk at index " << localIndex.x << localIndex.y << localIndex.z << std::endl;
}

Block WorldMemory::GetBlock(int3 worldIndex, int3 blockIndex) {
	int3 localIndex = worldIndex - origin;
	if (InMemoryBounds(localIndex)) {
		Chunk* chunk = &chunks[CIndex(localIndex)];
		return chunk->Get_Block(blockIndex);
	}
	return Block::ERROR;
}

void WorldMemory::SetBlock(int3 worldIndex, int3 blockIndex, Block newBlock) {
	int3 localIndex = worldIndex - origin;
	if (InMemoryBounds(localIndex)) {
		Chunk* chunk = &chunks[CIndex(localIndex)];
		chunk->Set_Block(blockIndex, newBlock);
	}
}