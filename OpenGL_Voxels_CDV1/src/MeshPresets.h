#pragma once

#include <vector>
#include "CMesh.h"
#include "glm/glm.hpp"
#include <iostream>

namespace MeshPresets {
	void Cube(CMesh& mesh, glm::vec3 pos);
	void Cube(CMesh& mesh);
};