#pragma once

#include "MeshPresets.h"

namespace MeshPresets {
	
	//void Cube(CMesh& mesh, glm::vec3 pos) {

	//	//CMesh mesh;
	//	//x+

	//	mesh.PushVertices({
	//		pos.x + 1.0f, pos.y + 0.0f, pos.z + 1.0f,   0.0f, 0.0f,
	//		pos.x + 1.0f, pos.y + 0.0f, pos.z + 0.0f,   1.0f, 0.0f,
	//		pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f,   0.0f, 1.0f,
	//		pos.x + 1.0f, pos.y + 1.0f, pos.z + 0.0f,   1.0f, 1.0f
	//		});
	//	//x-
	//	mesh.PushVertices({
	//		pos.x + 0.0f, pos.y + 0.0f, pos.z + 0.0f, 0.0f, 0.0f,
	//		pos.x + 0.0f, pos.y + 0.0f, pos.z + 1.0f, 1.0f, 0.0f,
	//		pos.x + 0.0f, pos.y + 1.0f, pos.z + 0.0f, 0.0f, 1.0f,
	//		pos.x + 0.0f, pos.y + 1.0f, pos.z + 1.0f, 1.0f, 1.0f
	//	});
	//	//y+
	//	mesh.PushVertices({
	//		pos.x + 1.0f, pos.y + 1.0f, pos.z + 0.0f,   0.0f, 0.0f,
	//		pos.x + 0.0f, pos.y + 1.0f, pos.z + 0.0f,   1.0f, 0.0f,
	//		pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f,   0.0f, 1.0f,
	//		pos.x + 0.0f, pos.y + 1.0f, pos.z + 1.0f,   1.0f, 1.0f
	//		});
	//	//y-
	//	mesh.PushVertices({
	//		pos.x + 0.0f, pos.y + 0.0f, pos.z + 0.0f,   0.0f, 0.0f,
	//		pos.x + 1.0f, pos.y + 0.0f, pos.z + 0.0f,   1.0f, 0.0f,
	//		pos.x + 0.0f, pos.y + 0.0f, pos.z + 1.0f,   0.0f, 1.0f,
	//		pos.x + 1.0f, pos.y + 0.0f, pos.z + 1.0f,   1.0f, 1.0f
	//		});
	//	//z+
	//	mesh.PushVertices({
	//		pos.x + 0.0f, pos.y + 0.0f, pos.z + 1.0f,   0.0f, 0.0f,
	//		pos.x + 1.0f, pos.y + 0.0f, pos.z + 1.0f,   1.0f, 0.0f,
	//		pos.x + 0.0f, pos.y + 1.0f, pos.z + 1.0f,   0.0f, 1.0f,
	//		pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f,   1.0f, 1.0f
	//		});
	//	//z-
	//	mesh.PushVertices({
	//		pos.x + 1.0f, pos.y + 0.0f, pos.z + 0.0f,   0.0f, 0.0f,
	//		pos.x + 0.0f, pos.y + 0.0f, pos.z + 0.0f,   1.0f, 0.0f,
	//		pos.x + 1.0f, pos.y + 1.0f, pos.z + 0.0f,   0.0f, 1.0f,
	//		pos.x + 0.0f, pos.y + 1.0f, pos.z + 0.0f,   1.0f, 1.0f
	//		});

	//	int indexStart = (mesh.index_count * 4) / 6;
	//	for (unsigned int i = indexStart; i < indexStart + 6 * 4; i += 4) {
	//		mesh.PushIndices({
	//			i,
	//			i + 3,
	//			i + 1,
	//			i,
	//			i + 2,
	//			i + 3
	//			});
	//	}
	//	//std::cout << "(MeshPresets.cpp) " << indexStart << std::endl;
	//	//return mesh;
	//}



	//void Cube(CMesh& mesh) {
	//	return Cube(mesh, glm::vec3(0, 0, 0));
	//	//CMesh mesh;

	//	//y+
	//	mesh.PushVertices({
	//		0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
	//		1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	//		0.0f, 1.0f, 1.0f,   0.0f, 1.0f,
	//		1.0f, 1.0f, 1.0f,   1.0f, 1.0f
	//		});
	//	//y-
	//	mesh.PushVertices({
	//		1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
	//		0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
	//		1.0f, 0.0f, 1.0f,   0.0f, 1.0f,
	//		0.0f, 0.0f, 1.0f,   1.0f, 1.0f
	//		});
	//	//x+
	//	mesh.PushVertices({
	//		1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
	//		1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
	//		1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
	//		1.0f, 1.0f, 1.0f,   1.0f, 1.0f
	//		});
	//	//x-
	//	mesh.PushVertices({
	//		0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
	//		0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
	//		0.0f, 1.0f, 1.0f,   0.0f, 1.0f,
	//		0.0f, 1.0f, 0.0f,   1.0f, 1.0f
	//		});
	//	//z+
	//	mesh.PushVertices({
	//		0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
	//		1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
	//		0.0f, 1.0f, 1.0f,   0.0f, 1.0f,
	//		1.0f, 1.0f, 1.0f,   1.0f, 1.0f
	//		});
	//	//z-
	//	mesh.PushVertices({
	//		1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
	//		0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
	//		1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
	//		0.0f, 1.0f, 0.0f,   1.0f, 1.0f
	//		});

	//	int indexStart = (mesh.index_count * 4) / 6;
	//	for (unsigned int i = indexStart; i < indexStart + 6 * 4; i += 4) {
	//		mesh.PushIndices({
	//			i,
	//			i + 3,
	//			i + 1,
	//			i,
	//			i + 2,
	//			i + 3
	//			});
	//	}
	//	//return mesh;
	//}

};