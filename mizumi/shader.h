#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <filesystem>

namespace miz
{
	class shader
	{
	public:
		shader(const std::filesystem::path& vertex, const std::filesystem::path& fragment, const std::filesystem::path& geometry = std::filesystem::path());
		~shader();

		[[nodiscard]] GLuint handle() const;
		[[nodiscard]] operator GLuint() const;

	private:
		[[nodiscard]] static GLuint create_shader(const std::filesystem::path& path, GLenum type);

		GLuint m_handle;
	};
}