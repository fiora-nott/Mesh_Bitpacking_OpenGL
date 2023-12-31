#include "ChunkMesher.h"

namespace ChunkMesher {


	Block GetBlockFreeform(WorldMemory* mem, int3 pos, Chunk* chunk) {
		int chunkSize = mem->chunkSize;
		if (chunk->InBounds(pos)) {
			return chunk->Get_Block(pos);
		}
		else {
			int3 checkIndex = chunk->worldIndex;
			if (pos.x < 0) {
				checkIndex.x--;
				pos.x += chunkSize;
			}
			if (pos.y < 0) {
				checkIndex.y--;
				pos.y += chunkSize;
			}
			if (pos.z < 0) {
				checkIndex.z--;
				pos.z += chunkSize;
			}
			if (pos.x >= chunkSize) {
				checkIndex.x++;
				pos.x -= chunkSize;
			}
			if (pos.y >= chunkSize) {
				checkIndex.y++;
				pos.y -= chunkSize;
			}
			if (pos.z >= chunkSize) {
				checkIndex.z++;
				pos.z -= chunkSize;
			}
			int3 localIndex = checkIndex - mem->origin;
			if (mem->InMemoryBounds(localIndex)) {
				return mem->GetChunkLocal(localIndex)->Get_Block(pos);
			}
		}
		return Block::AIR;
	}

	CMesh GenerateMesh(WorldMemory* mem, Chunk* chunk) {
		
		int3 worldPos = chunk->worldIndex * chunk->chunkSize;
		int indexStart = 0;
		int3 blockPos;
		int3 checkPos;
		int chunkSize = chunk->chunkSize;

		CMesh mesh(worldPos);

		int3 sideNormals[6] = {
			int3(1, 0, 0),
			int3(-1, 0, 0),
			int3(0, 1, 0),
			int3(0, -1, 0),
			int3(0, 0, 1),
			int3(0, 0, -1)
		};

		int sideLightValues[6]{
			6,
			3,
			7,
			2,
			5,
			4
		};

		float sideVertices[6][12] = {
			{ // x+
			1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 0.0f},
			{ //x-
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 1.0f},
			{ //y+
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f},
			{ //y-
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f},
			{ //z+
			0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f},
			{ //z-
			1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f}
		};

		int3 aoDirections[6][4][3]{
			{ //x+
				{int3(0, -1,  1), int3(0, 0,  1), int3(0, -1, 0)},
				{int3(0, -1, -1), int3(0, 0, -1), int3(0, -1, 0)},
				{int3(0,  1,  1), int3(0, 0,  1), int3(0,  1, 0)},
				{int3(0,  1, -1), int3(0, 0, -1), int3(0,  1, 0)}},
			{ //x-
				{int3(0, -1, -1), int3(0, 0, -1), int3(0, -1, 0)},
				{int3(0, -1,  1), int3(0, 0,  1), int3(0, -1, 0)},
				{int3(0,  1, -1), int3(0, 0, -1), int3(0,  1, 0)},
				{int3(0,  1,  1), int3(0, 0,  1), int3(0,  1, 0)}},
			{ //y+
				{int3( 1, 0, -1), int3( 1, 0, 0), int3(0, 0, -1)},
				{int3(-1, 0, -1), int3(-1, 0, 0), int3(0, 0, -1)},
				{int3( 1, 0,  1), int3( 1, 0, 0), int3(0, 0,  1)},
				{int3(-1, 0,  1), int3(-1, 0, 0), int3(0, 0,  1)}},
			{ //y-
				{int3(-1, 0, -1), int3(-1, 0, 0), int3(0, 0, -1)},
				{int3( 1, 0, -1), int3( 1, 0, 0), int3(0, 0, -1)},
				{int3(-1, 0,  1), int3(-1, 0, 0), int3(0, 0,  1)},
				{int3( 1, 0,  1), int3( 1, 0, 0), int3(0, 0,  1)}},
			{ //z+
				{int3(-1, -1, 0), int3(-1, 0, 0), int3(0, -1, 0)},
				{int3( 1, -1, 0), int3( 1, 0, 0), int3(0, -1, 0)},
				{int3(-1,  1, 0), int3(-1, 0, 0), int3(0,  1, 0)},
				{int3( 1,  1, 0), int3( 1, 0, 0), int3(0,  1, 0)}},
			{ //z-
				{int3( 1, -1, 0), int3( 1, 0, 0), int3(0, -1, 0)},
				{int3(-1, -1, 0), int3(-1, 0, 0), int3(0, -1, 0)},
				{int3( 1,  1, 0), int3( 1, 0, 0), int3(0,  1, 0)},
				{int3(-1,  1, 0), int3(-1, 0, 0), int3(0,  1, 0)}}
		};

		for (int x = 0; x < chunkSize; x++) {
			for (int y = 0; y < chunkSize; y++) {
				for (int z = 0; z < chunkSize; z++) {
					blockPos = int3(x, y, z);
					Block blockType = chunk->Get_Block(blockPos);
					if (blockType == Block::AIR)
						continue;

					// Iterate over each face of this voxel
					for (int side = 0; side < 6; side++) {
						// Project out with a normal vector and check if the neighbor voxel is solid or air
						checkPos = blockPos + sideNormals[side];

						// If the neighbor is opaque/non-air, do not draw a face. This face is occluded.
						if (GetBlockFreeform(mem, checkPos, chunk) != Block::AIR)
							continue;

						// All conditions are met so draw the side
						float* localVerts = sideVertices[side];

						// i represents vertex number
						for (int i = 0; i < 4; i++) {
							// Grab the vertex displacement based on which vertex we are assigning
							int3 vertLocalPos = int3(localVerts[i * 3], localVerts[i * 3 + 1], localVerts[i * 3 + 2]);
							int3 vertObjectPos = blockPos + vertLocalPos;

							// Ambient occlusion actually has a bias since quads are triangles, and will work differently
							// at different diagonals for every plane.
							unsigned int aoLevel = 0; //must be 0-2 since light is 2-7
							int3 aoOffset = ((vertLocalPos * 2) - 1);
							int3 aoCheckPos1 = checkPos + aoDirections[side][i][0];
							int3 aoCheckPos2 = checkPos + aoDirections[side][i][1];
							int3 aoCheckPos3 = checkPos + aoDirections[side][i][2];

							// Check aoCheckPos1 last since its the corner block, which has the weakest shadow
							// Having an effect of 1 for every case creates shadows of equal intensity for edges and corners
							if (GetBlockFreeform(mem, aoCheckPos3, chunk) != Block::AIR)
								aoLevel = 1;
							else if (GetBlockFreeform(mem, aoCheckPos2, chunk) != Block::AIR)
								aoLevel = 1;
							else if (GetBlockFreeform(mem, aoCheckPos1, chunk) != Block::AIR)
								aoLevel = 1; //could be 1 for lighter corners

							// Determine block values that will need to be packed into this vertex
							int uvID = i;
							int blockID = (int)(blockType); // must be less than 1024
							int lightValue = sideLightValues[side] - aoLevel; //must be between 0-7. AO is 0-2

							// Bitpack all the information calculated so far. This will be parsed by the bitwise shader.
							// Packing this information reduces memory footprint from 32 * 7 = 224 bits down to 32 bits.
							// That is a video memory reduction of SEVEN times!
							//each position is 0-31   (32)   so we use 15 bits, 5 for each pos
							//the uv        is 0-3    (4)    so we use 2 bits
							//the blockID   is 0-1023 (1024) so we use 10 bits
							//the lightVal  is 0-7    (8)    so we use 3 bits
							//the total bitcount is 30	 bits
							GLuint compressedVertex = vertObjectPos.x | vertObjectPos.y << 5 | vertObjectPos.z << 10 | uvID << 15 | blockID << 17 | lightValue << 27;
							mesh.PushVertex(compressedVertex);

							// Debugging tool: print out binary data of any vertices of block 0, 0, 0
							//if (blockPos.x == 0 && blockPos.y == 0 && blockPos.z == 0) {
							//	std::cout << std::bitset<32>(compressedVertex) << std::endl;
						}

						// Push indices in an order that designates 2 clockwise triangles, composing a quad with 4 vertices
						unsigned int indexStart = (mesh.index_count / 6) * 4;
						mesh.PushIndices({
							indexStart,
							indexStart + 3,
							indexStart + 1,
							indexStart,
							indexStart + 2,
							indexStart + 3 });

						/* Bit-Compression demonstration
						if (blockPos.x == 1 && blockPos.y == 1 && blockPos.z == 1) {
							//each position is 0-31   (32)   so we use 15 bits, 5 for each pos
							//the uv        is 0-3    (4)    so we use 2 bits
							//the blockID   is 0-1023 (1024) so we use 10 bits
							//the lightVal  is 0-7    (8)    so we use 3 bits
							//the total bitcount is 30	 bits
							int uvID = 2;
							int blockID = 542;
							int lightValue = 3;
							int compressedVertex = x | y << 5 | z << 10 | uvID << 15 | blockID << 17 | lightValue << 27;
							std::cout << std::bitset<30>(compressedVertex) << std::endl;

							int test;
							test = (compressedVertex)       & 0b00000000000000000000000000011111;
							std::cout << std::bitset<30>(test) << std::endl;

							test = (compressedVertex >> 5)  & 0b000000000000000000000011111;
							std::cout << std::bitset<25>(test) << std::endl;

							test = (compressedVertex >> 10) & 0b0000000000000000011111;
							std::cout << std::bitset<20>(test) << std::endl;

							test = (compressedVertex >> 15) & 0b00000000000000011;
							std::cout << std::bitset<15>(test) << std::endl;

							test = (compressedVertex >> 17) & 0b000001111111111;
							std::cout << std::bitset<13>(test) << std::endl;

							test = (compressedVertex >> 27) & 0b00111;
							std::cout << std::bitset<3>(test) << std::endl;
						}*/
					}
				}
			}
		}
		return mesh;
	}
}
