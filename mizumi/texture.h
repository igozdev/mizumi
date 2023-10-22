#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <filesystem>

namespace miz
{
	class texture
	{
	public:
		texture(const std::filesystem::path& texture);
		~texture();

		[[nodiscard]] GLuint handle() const;
		[[nodiscard]] operator GLuint() const;

	private:
		GLuint m_handle;
		int m_width;
		int m_height;
	};
}