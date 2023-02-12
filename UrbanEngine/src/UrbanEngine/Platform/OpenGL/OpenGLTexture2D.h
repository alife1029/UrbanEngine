#pragma once

#include "UrbanEngine/Graphics/Texture2D.h"
 
#include <glad/glad.h>

namespace UrbanEngine
{
	class OpenGLTexture2D : public Texture2D
	{
		friend class Texture2D;

	private:
		OpenGLTexture2D(unsigned char* pixels, int width, int height, int channelCount, unsigned int pixelPerUnit, FilterMode filter, WrapMode wrap);
		OpenGLTexture2D(const std::string& imageFile, unsigned int pixelPerUnit, bool forceRGBA, FilterMode filter, WrapMode wrap);

	public:
		OpenGLTexture2D(const OpenGLTexture2D&) = delete;
		virtual ~OpenGLTexture2D() override;
		virtual void Bind() override;

		virtual bool IsValid() const noexcept override;

		GLuint GetID() const noexcept;

		virtual void ChangeFilterMode(FilterMode f) override;
		virtual void ChangeWrapMode(WrapMode w) override;

	private:
		virtual void GenerateTextureFromBytes(unsigned char* pixels, int w, int h, int ch, FilterMode f, WrapMode wrp) override;

	private:
		GLuint m_TextureID = 0;
	};
}
