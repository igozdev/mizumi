#include "mesh.h"

namespace miz
{
	mesh::mesh(const std::vector<vertex>& vertices, const std::vector<GLuint>& indices)
		: m_vertices(vertices), m_indices(indices)
	{
		glCreateVertexArrays(1, &m_vao_handle);
		glBindVertexArray(m_vao_handle);

		glGenBuffers(1, &m_vbo_handle);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_handle);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &m_ebo_handle);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_handle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

		// position
		constexpr int pos_attribLoc = 0;
		glVertexAttribPointer(pos_attribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<const void*>(offsetof(vertex, position)));
		glEnableVertexAttribArray(pos_attribLoc);

		// color
		constexpr int col_attribLoc = 1;
		glVertexAttribPointer(col_attribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<const void*>(offsetof(vertex, color)));
		glEnableVertexAttribArray(col_attribLoc);

		// texcoord
		constexpr int tex_attribLoc = 2;
		glVertexAttribPointer(tex_attribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<const void*>(offsetof(vertex, texcoord)));
		glEnableVertexAttribArray(tex_attribLoc);

		// normal
		constexpr int nor_attribLoc = 3;
		glVertexAttribPointer(nor_attribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<const void*>(offsetof(vertex, normal)));
		glEnableVertexAttribArray(nor_attribLoc);

		glBindVertexArray(0);
	}
	mesh::~mesh()
	{
		glDeleteVertexArrays(1, &m_vao_handle);
		glDeleteBuffers(1, &m_vbo_handle);
		glDeleteBuffers(1, &m_ebo_handle);
	}

	void mesh::draw()
	{
		if (m_indices.empty())
		{
			glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
		}
		else
		{
			glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
		}
	}

	[[nodiscard]] GLuint mesh::handle() const
	{
		return m_vao_handle;
	}
	[[nodiscard]] mesh::operator GLuint() const
	{
		return m_vao_handle;
	}
}