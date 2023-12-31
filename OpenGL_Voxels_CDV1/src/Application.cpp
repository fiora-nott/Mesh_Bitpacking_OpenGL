		#include <iostream>
#include <string>

#include "WorldMemory.h"
#include "Chunk.h"
#include "int3.h"
#include "Window.h"

#define LOG(x) std::cout << x << std::endl;


int main(void)
{
	std::cout << "(application.cpp) game launching..." << std::endl;

	int3 worldOrigin(0, 0, 0);
	int renderDistance = 4;
	//must be 31 since vertices can only reach 31 as a max (binary). 32 is out of range
	int chunk_size = 31;
	WorldMemory mem = WorldMemory(worldOrigin, renderDistance, chunk_size);

	Window window;
	window.CreateWindow(1280, 720);
	window.LaunchGameLoop(mem);

    return 0;
}

/*
int main() {
	std::cout << "main function running!" << std::endl;

	int3 chunk_pos(6, 3, 7);
	int3 block_pos(6, 5, 4);

	World_Memory mem = World_Memory(int3(0, 0, 0), 8, 20);
	Chunk* chunk = mem.Get_Chunk(chunk_pos);
	Block block = chunk->Get_Block(block_pos);

	LOG((short)block);
	
	mem.Set_Block(chunk_pos, block_pos, Block::DIAMOND);

	block = mem.Get_Block(chunk_pos, block_pos);
	LOG((short)block);

	return 0;
}*/