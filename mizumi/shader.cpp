#include "shader.h"
#include <fstream>
#include <iostream>

namespace miz
{
	shader::shader(const std::filesystem::path& vertex, const std::filesystem::path& fragment, const std::filesystem::path& geometry)
	{
		bool use_geometry = geometry != std::filesystem::path();

		GLuint vertex_shader = create_shader(vertex, GL_VERTEX_SHADER);
		GLuint fragment_shader = create_shader(fragment, GL_FRAGMENT_SHADER);
		GLuint geometry_shader = use_geometry ? create_shader(geometry, GL_GEOMETRY_SHADER) : 0;
		
		m_handle = glCreateProgram();
		glAttachShader(m_handle, vertex_shader);
		glAttachShader(m_handle, fragment_shader);
		if (use_geometry)
		{
			glAttachShader(m_handle, geometry_shader);
		}
		glLinkProgram(m_handle);

		char infolog[512];
		GLint success;
		glGetProgramiv(m_handle, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_handle, sizeof(infolog), nullptr, infolog);
			std::cerr << "Error linking program\n" << infolog << "\n";
		}

		glUseProgram(0);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		if (use_geometry)
		{
			glDeleteShader(geometry_shader);
		}
	}
	shader::~shader()
	{
		glDeleteProgram(m_handle);
	}

	[[nodiscard]] GLuint shader::handle() const
	{
		return m_handle;
	}
	[[nodiscard]] shader::operator GLuint() const
	{
		return m_handle;
	}

	[[nodiscard]] GLuint shader::create_shader(const std::filesystem::path& path, GLenum type)
	{
		std::string source;
		if (std::ifstream file(path); file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
			{
				source.append(line + '\n');
			}
			file.close();
		}
		else
		{
			std::cerr << "Failed to open shader file \"" << path << "\"\n";
		}

		GLuint shader = glCreateShader(type);
		const GLchar* gl_src = source.c_str();
		glShaderSource(shader, 1, &gl_src, nullptr);
		glCompileShader(shader);

		char infolog[512];
		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, sizeof(infolog), nullptr, infolog);
			std::cerr << "Error compiling shader\n" << infolog << "\n";
		}

		return shader;
	}
}