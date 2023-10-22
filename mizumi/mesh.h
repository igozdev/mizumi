#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "vertex.h"

namespace miz
{
	class mesh
	{
	public:
		mesh(const std::vector<vertex>& vertices, const std::vector<GLuint>& indices);
		~mesh();

		[[nodiscard]] GLuint handle() const;
		[[nodiscard]] operator GLuint() const;

		void draw();

	private:
		GLuint m_vao_handle;
		GLuint m_vbo_handle;
		GLuint m_ebo_handle;
		std::vector<vertex> m_vertices;
		std::vector<GLuint> m_indices;
	};
}