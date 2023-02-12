#pragma once

#include <string>
#include "Graphics.h"

namespace UrbanEngine
{
	class Texture2D
	{
	public:
		enum class FilterMode
		{
			Point = 0,
			Bilinear = 1,
			Trilinear = 2
		};

		enum class WrapMode
		{
			Repeat = 0,
			Clamp = 1
		};

	public:
		static Texture2D* LoadWhiteTexture(Graphics* gfx);
		static Texture2D* LoadTexture(Graphics* gfx, const std::string& imageFile, unsigned int pixelPerUnit = 100u, bool forceRGBA = false, FilterMode filter = FilterMode::Bilinear, WrapMode wrap = WrapMode::Clamp);
		static Texture2D* LoadTexture(Graphics* gfx, unsigned char* pixels, int width, int height, int channelCount, unsigned int pixelPerUnit = 100u, FilterMode filter = FilterMode::Bilinear, WrapMode wrap = WrapMode::Clamp);

	protected:
		Texture2D(unsigned char* pixels, int width, int height, int channelCount, unsigned int pixelPerUnit, FilterMode filter, WrapMode wrap);
		Texture2D(const std::string& imageFile, unsigned int pixelPerUnit, bool forceRGBA, FilterMode filter, WrapMode wrap);

	public:
		Texture2D(const Texture2D&) = delete;
		virtual ~Texture2D();

		virtual void Bind();

		virtual bool IsValid() const noexcept;
		int Width() const noexcept;
		int Height() const noexcept;
		int ChannelCount() const noexcept;
		unsigned int PixelPerUnit() const noexcept;
		FilterMode GetFilterMode() const noexcept;
		WrapMode GetWrapMode() const noexcept;

		void SetPixelPerUnit(int ppu) noexcept;
		virtual void ChangeFilterMode(FilterMode f);
		virtual void ChangeWrapMode(WrapMode w);

	private:
		virtual void GenerateTextureFromBytes(unsigned char* pixels, int w, int h, int ch, FilterMode f, WrapMode wrp);
	protected:
		void LoadImageFromFile(const std::string& file, bool forceRGBA, FilterMode f, WrapMode w);

	protected:
		int m_Width;
		int m_Height;
		int m_ChannelCount;
		int m_PixelPerUnit;
		FilterMode m_FilterMode;
		WrapMode m_WrapMode;
	};
}
