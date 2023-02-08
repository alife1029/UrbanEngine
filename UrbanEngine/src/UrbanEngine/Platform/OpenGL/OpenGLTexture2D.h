#pragma once

#include "UrbanEngine/Graphics/Texture2D.h"

#include <glad/glad.h>

namespace UrbanEngine
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		// Creates a 1x1 white texture
		OpenGLTexture2D();
		OpenGLTexture2D(const OpenGLTexture2D&) = delete;
		OpenGLTexture2D(unsigned char* pixels, int width, int height, int channelCount, unsigned int pixelPerUnit, FilterMode filter, WrapMode wrap);
		OpenGLTexture2D(const std::string& imageFile, unsigned int pixelPerUnit, bool forceRGBA, FilterMode filter, WrapMode wrap);
		virtual ~OpenGLTexture2D() override;
		virtual void Bind() override;

		virtual bool IsValid() const noexcept override;

		GLuint GetID() const noexcept;

	private:
		virtual void GenerateTextureFromBytes(unsigned char* pixels, int w, int h, int ch, FilterMode f, WrapMode wrp) override;
		virtual void LoadImageFromFile(const std::string& file, bool forceRGBA, FilterMode f, WrapMode w) override;
		virtual void ChangeFilterMode(FilterMode f) override;
		virtual void ChangeWrapMode(WrapMode w) override;

	private:
		GLuint m_TextureID = 0;
	};
}
