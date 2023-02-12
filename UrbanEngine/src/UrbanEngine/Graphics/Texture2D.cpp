#include "urbanpch.h"
#include "Texture2D.h"

#ifdef URBAN_PLATFORM_WINDOWS
#include "UrbanEngine/Platform/DirectX/D3D11Texture2D.h"
#endif

#include "UrbanEngine/Platform/OpenGL/OpenGLTexture2D.h"

#include <stb/stb_image.h>

namespace UrbanEngine
{
	Texture2D* Texture2D::LoadWhiteTexture(Graphics* gfx)
	{
		// Constuct a 1x1 white texture
		unsigned char pixelData[] = { 255, 255, 255 };
		return LoadTexture(gfx, pixelData, 1, 1, 3, 1, FilterMode::Point, WrapMode::Clamp);
	}

	Texture2D* Texture2D::LoadTexture(Graphics* gfx, const std::string& imageFile, unsigned int pixelPerUnit, bool forceRGBA, FilterMode filter, WrapMode wrap)
	{
		switch (gfx->GetRendererAPI())
		{
		case Graphics::API::D3D11:
			// TODO: Return D3D11 Texture
			//return new D3D11Texture2D(imageFile, pixelPerUnit, forceRGBA, filter, wrap);
		case Graphics::API::GL460:
			return new OpenGLTexture2D(imageFile, pixelPerUnit, forceRGBA, filter, wrap);
		case Graphics::API::GLES30:
			// TODO: Return OpenGL ES Texture
			return nullptr;
		default:
			return nullptr;
		}
	}

	Texture2D* Texture2D::LoadTexture(Graphics* gfx, unsigned char* pixels, int width, int height, int channelCount, unsigned int pixelPerUnit, FilterMode filter, WrapMode wrap)
	{
		switch (gfx->GetRendererAPI())
		{
		case Graphics::API::D3D11:
		// TODO: Return D3D11 Texture	
		//return new D3D11Texture2D(pixels, width, height, channelCount, pixelPerUnit, filter, wrap);
		case Graphics::API::GL460:
			return new OpenGLTexture2D(pixels, width, height, channelCount, pixelPerUnit, filter, wrap);
		case Graphics::API::GLES30:
			// TODO: Return OpenGL ES Texture
			return nullptr;
		default:
			return nullptr;
		}
	}
	
	Texture2D::Texture2D(unsigned char* pixels, int width, int height, int channelCount, unsigned int pixelPerUnit, FilterMode filter, WrapMode wrap)
		:
		m_Width(width),
		m_Height(height),
		m_ChannelCount(channelCount),
		m_PixelPerUnit(pixelPerUnit),
		m_FilterMode(filter),
		m_WrapMode(wrap)
	{
	}

	Texture2D::Texture2D(const std::string & imageFile, unsigned int pixelPerUnit, bool forceRGBA, FilterMode filter, WrapMode wrap)
		:
		m_PixelPerUnit(pixelPerUnit),
		m_FilterMode(filter),
		m_WrapMode(wrap),
		m_Width(0),
		m_Height(0),
		m_ChannelCount(0)
	{
	}
	
	Texture2D::~Texture2D()
	{
	}
	
	void Texture2D::Bind()
	{
	}
	
	bool Texture2D::IsValid() const noexcept
	{
		return false;
	}
	
	int Texture2D::Width() const noexcept
	{
		return m_Width;
	}
	
	int Texture2D::Height() const noexcept
	{
		return m_Height;
	}
	
	int Texture2D::ChannelCount() const noexcept
	{
		return m_ChannelCount;
	}
	
	unsigned int Texture2D::PixelPerUnit() const noexcept
	{
		return m_PixelPerUnit;
	}
	
	Texture2D::FilterMode Texture2D::GetFilterMode() const noexcept
	{
		return m_FilterMode;
	}
	
	Texture2D::WrapMode Texture2D::GetWrapMode() const noexcept
	{
		return m_WrapMode;
	}
	
	void Texture2D::SetPixelPerUnit(int ppu) noexcept
	{
		m_PixelPerUnit = ppu;
	}
	
	void Texture2D::GenerateTextureFromBytes(unsigned char* pixels, int w, int h, int ch, FilterMode f, WrapMode wrp)
	{
	}
	
	void Texture2D::LoadImageFromFile(const std::string& file, bool forceRGBA, FilterMode f, WrapMode w)
	{
		int width, height, channelCount;
		unsigned char* pixels;

		int desiredChannelCount = forceRGBA ? STBI_rgb_alpha : STBI_default;

		stbi_set_flip_vertically_on_load(true);
		pixels = stbi_load(file.c_str(), &width, &height, &channelCount, desiredChannelCount);

		GenerateTextureFromBytes(pixels, width, height, desiredChannelCount == 0 ? channelCount : desiredChannelCount, f, w);

		stbi_image_free(pixels);
	}
	
	void Texture2D::ChangeFilterMode(FilterMode f)
	{
	}
	
	void Texture2D::ChangeWrapMode(WrapMode w)
	{
	}
}
