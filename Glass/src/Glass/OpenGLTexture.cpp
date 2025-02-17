#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Glass
{
	OpenGLTexture::OpenGLTexture(const std::string& filename)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		stbi_set_flip_vertically_on_load(true);

		int numComponents;
		unsigned char* data = stbi_load(filename.c_str(), (int*)&m_Width, (int*)&m_Height, &numComponents, 0);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}

	OpenGLTexture::OpenGLTexture(const std::string& filename, int numRows)
	{
		m_NumberOfRows = numRows;

		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		stbi_set_flip_vertically_on_load(true);

		int numComponents;
		unsigned char* data = stbi_load(filename.c_str(), (int*)&m_Width, (int*)&m_Height, &numComponents, 0);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}

	void OpenGLTexture::Bind(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}
}

