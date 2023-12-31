#pragma once

#include <bitset>

#include "CMesh.h"
#include "Chunk.h"
#include "MeshPresets.h"
#include "WorldMemory.h"

namespace ChunkMesher
{
	Block GetBlockFreeform(WorldMemory* mem, int3 pos, Chunk* chunk);
	CMesh GenerateMesh(WorldMemory* mem, Chunk* chunk);
};

