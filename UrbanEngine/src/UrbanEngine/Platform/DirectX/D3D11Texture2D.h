#pragma once

#include "UrbanEngine/Graphics/Texture2D.h"

#include <d3d11.h>

namespace UrbanEngine
{
	class D3D11Texture2D : public Texture2D
	{
		D3D11Texture2D();
		D3D11Texture2D(const D3D11Texture2D&) = default;
		D3D11Texture2D(unsigned char* pixels, int width, int height, int channelCount, unsigned int pixelPerUnit = 100u, FilterMode filter = FilterMode::Bilinear, WrapMode wrap = WrapMode::Clamp);
		D3D11Texture2D(const std::string& imgFile, unsigned int pixelPerUnit = 100u, bool forceRGBA = true, FilterMode filter = FilterMode::Bilinear, WrapMode wrap = WrapMode::Clamp);
		~D3D11Texture2D();

		virtual void Bind() override;
		virtual bool IsValid() const noexcept override;
		
	private:
		virtual void GenerateTextureFromBytes(unsigned char* pixels, int w, int h, int ch, FilterMode f, WrapMode wrp) override;
		virtual void LoadImageFromFile(const std::string& imgFile, bool forceRGBA, FilterMode f, WrapMode w) override;
		virtual void ChangeFilterMode(FilterMode f) override;
		virtual void ChangeWrapMode(WrapMode w) override;

	private:
		ID3D11ShaderResourceView* pTextureView;
	};
}

