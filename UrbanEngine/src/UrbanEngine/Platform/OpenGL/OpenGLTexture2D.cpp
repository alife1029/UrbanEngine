#include "urbanpch.h"
#include "OpenGLTexture2D.h"

namespace UrbanEngine
{
	OpenGLTexture2D::OpenGLTexture2D(unsigned char* pixels, int width, int height, int channelCount, unsigned int pixelPerUnit, FilterMode filter, WrapMode wrap)
		:
		Texture2D(pixels, width, height, channelCount, pixelPerUnit, filter, wrap)
	{
		GenerateTextureFromBytes(pixels, width, height, channelCount, filter, wrap);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& imageFile, unsigned int pixelPerUnit, bool forceRGBA, FilterMode filter, WrapMode wrap)
		:
		Texture2D(imageFile, pixelPerUnit, forceRGBA, filter, wrap)
	{
		LoadImageFromFile(imageFile, forceRGBA, filter, wrap);
	}
	
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}
	
	void OpenGLTexture2D::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}
	
	bool OpenGLTexture2D::IsValid() const noexcept
	{
		return m_TextureID != 0;
	}

	GLuint OpenGLTexture2D::GetID() const noexcept
	{
		return m_TextureID;
	}
	
	void OpenGLTexture2D::GenerateTextureFromBytes(unsigned char* pixels, int w, int h, int ch, FilterMode f, WrapMode wrp)
	{
		// Detect image format
		constexpr GLint imgFormats[] = { GL_RED, GL_RG, GL_RGB, GL_RGBA };
		GLint imgFormat = NULL;

		if (ch >= 1 && ch <= 4) 
		{
			imgFormat = imgFormats[ch - 1];
		} 
		else 
		{
			// TODO: Throw an exception
			std::cout << "Unsupported Image Format! (" << ch << " channels)" << std::endl;
		}

		glGenTextures(1, &m_TextureID);
		Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, imgFormat, w, h, NULL, imgFormat, GL_UNSIGNED_BYTE, pixels);
		ChangeFilterMode(f);
		ChangeWrapMode(wrp);
		glGenerateMipmap(GL_TEXTURE_2D);

		m_Width = w;
		m_Height = h;
		m_ChannelCount = ch;
	}
	
	void OpenGLTexture2D::ChangeFilterMode(FilterMode f)
	{
		if (m_FilterMode != f)
		{
			constexpr GLint filterIDs[] = { GL_NEAREST, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR };

			Bind();

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterIDs[static_cast<int>(f)]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterIDs[static_cast<int>(f)]);

			m_FilterMode = f;
		}
	}
	
	void OpenGLTexture2D::ChangeWrapMode(WrapMode w)
	{
		if (m_WrapMode != w)
		{
			constexpr GLint wrapIDs[] = { GL_REPEAT, GL_CLAMP_TO_EDGE };

			Bind();

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapIDs[static_cast<int>(w)]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapIDs[static_cast<int>(w)]);

			m_WrapMode = w;
		}
	}
}
