#include "OpenGLTexture2D.h"

#include <stb/stb_image.h>

namespace UrbanEngine
{
	OpenGLTexture2D::OpenGLTexture2D()
	{
		// Constuct a 1x1 white texture
		uint32_t pixelData = 0xffffffff;
		GenerateTextureFromBytes((unsigned char*)(&pixelData), 1, 1, 4, FilterMode::Point, WrapMode::Clamp);
		m_PixelPerUnit = 1;
	}

	OpenGLTexture2D::OpenGLTexture2D(unsigned char* pixels, int width, int height, int channelCount, unsigned int pixelPerUnit, FilterMode filter, WrapMode wrap)
	{
		GenerateTextureFromBytes(pixels, width, height, channelCount, filter, wrap);
		m_PixelPerUnit = pixelPerUnit;
	}
	
	OpenGLTexture2D::OpenGLTexture2D(const std::string& imageFile, unsigned int pixelPerUnit, bool forceRGBA, FilterMode filter, WrapMode wrap)
	{
		LoadImageFromFile(imageFile, forceRGBA, filter, wrap);
		m_PixelPerUnit = pixelPerUnit;
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
	
	void OpenGLTexture2D::LoadImageFromFile(const std::string& file, bool forceRGBA, FilterMode f, WrapMode w)
	{
		int width, height, channelCount;
		unsigned char* pixels;

		int desiredChannelCount = forceRGBA ? STBI_rgb_alpha : STBI_default;

		stbi_set_flip_vertically_on_load(true);
		pixels = stbi_load(file.c_str(), &width, &height, &channelCount, desiredChannelCount);

		GenerateTextureFromBytes(pixels, width, height, desiredChannelCount == 0 ? channelCount : desiredChannelCount, f, w);

		stbi_image_free(pixels);

		m_Path = file;
	}
	
	void OpenGLTexture2D::ChangeFilterMode(FilterMode f)
	{
		constexpr GLint filterIDs[] = { GL_NEAREST, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR };

		Bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterIDs[static_cast<int>(f)]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterIDs[static_cast<int>(f)]);

		m_FilterMode = f;
	}
	
	void OpenGLTexture2D::ChangeWrapMode(WrapMode w)
	{
		constexpr GLint wrapIDs[] = { GL_REPEAT, GL_CLAMP_TO_EDGE };

		Bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapIDs[static_cast<int>(w)]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapIDs[static_cast<int>(w)]);

		m_WrapMode = w;
	}
}
