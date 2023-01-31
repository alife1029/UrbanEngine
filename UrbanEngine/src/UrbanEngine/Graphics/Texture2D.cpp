#include "urbanpch.h"
#include "Texture2D.h"

namespace UrbanEngine
{
	Texture2D::Texture2D()
		:
		m_Path(std::string()),
		m_ForceRGBA(false),
		m_Width(0),
		m_Height(0),
		m_ChannelCount(0),
		m_PixelPerUnit(0),
		m_FilterMode(FilterMode::Bilinear),
		m_WrapMode(WrapMode::Clamp)
	{
	}
	
	Texture2D::Texture2D(unsigned char* pixels, int width, int height, int channelCount, unsigned int pixelPerUnit, FilterMode filter, WrapMode wrap)
		:
		m_Path(std::string()),
		m_ForceRGBA(false),
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
		m_Path(imageFile),
		m_ForceRGBA(forceRGBA),
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
	
	const std::string& Texture2D::GetPath() const noexcept
	{
		return m_Path;
	}
	
	bool Texture2D::IsForcedToRGBA() const noexcept
	{
		return m_ForceRGBA;
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
	
	void Texture2D::SetFilterMode(FilterMode mode) noexcept
	{
		if (mode != m_FilterMode)
		{
			m_FilterMode = mode;
			ChangeFilterMode(mode);
		}
	}
	
	void Texture2D::SetWrapMode(WrapMode mode) noexcept
	{
		if (mode != m_WrapMode)
		{
			m_WrapMode = mode;
			ChangeWrapMode(mode);
		}
	}
	
	void Texture2D::GenerateTextureFromBytes(unsigned char* pixels, int w, int h, int ch, FilterMode f, WrapMode wrp)
	{
	}
	
	void Texture2D::LoadImageFromFile(const std::string& file, bool forceRGBA, FilterMode f, WrapMode w)
	{
	}
	
	void Texture2D::ChangeFilterMode(FilterMode f)
	{
	}
	
	void Texture2D::ChangeWrapMode(WrapMode w)
	{
	}
}