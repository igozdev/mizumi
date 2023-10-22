#include "texture.h"
#include <SOIL2/SOIL2.h>
#include <iostream>

namespace miz
{
	texture::texture(const std::filesystem::path& texture)
	{
		unsigned char* image_data = SOIL_load_image(texture.string().c_str(), &m_width, &m_height, nullptr, SOIL_LOAD_RGBA);

		glGenTextures(1, &m_handle);
		glBindTexture(GL_TEXTURE_2D, m_handle);

		// TODO: ?
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if (image_data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cerr << "Failed to load texture\n";
		}

		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		SOIL_free_image_data(image_data);
	}
	texture::~texture()
	{
		glDeleteTextures(1, &m_handle);
	}

	[[nodiscard]] GLuint texture::handle() const
	{
		return m_handle;
	}
	[[nodiscard]] texture::operator GLuint() const
	{
		return m_handle;
	}
}