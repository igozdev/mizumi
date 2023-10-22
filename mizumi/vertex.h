#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace miz
{
	struct vertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 texcoord;
		glm::vec3 normal;
	};
}