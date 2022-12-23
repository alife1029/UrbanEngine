#pragma once

#include "D3D11Graphics.h"

#define GFX_EXCEPT_NOINFO(hr) UrbanEngine::D3D11Graphics::HrException(__LINE__, __FILEW__, (hr))
#define GFX_THROW_NOINFO(hrcall) if (FAILED(hr = (hrcall))) throw UrbanEngine::D3D11Graphics::HrException(__LINE__, __FILEW__, hr)

#if URBAN_IS_DEBUG
#define GFX_EXCEPT(hr) UrbanEngine::D3D11Graphics::HrException(__LINE__, __FILEW__, (hr), infoManager.GetMessages())
#define GFX_THROW_INFO(hrcall) infoManager.Set(); if(FAILED(hr = (hrcall))) throw GFX_EXCEPT(hr)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) UrbanEngine::D3D11Graphics::DeviceRemovedException(__LINE__, __FILEW__, (hr), infoManager.GetMessages())
#define GFX_THROW_INFO_ONLY(call) infoManager.Set(); (call); { auto v = infoManager.GetMessages(); if (!v.empty()) throw UrbanEngine::D3D11Graphics::InfoException(__LINE__, __FILEW__, v); }
#define INFO_MANAGER(gfx) HRESULT hr; UrbanEngine::DXGIInfoManager& infoManager = gfx->GetDXGIInfoManager()
#else
#define GFX_EXCEPT(hr) UrbanEngine::D3D11Graphics::HrException(__LINE__, __FILEW__, (hr))
#define GFX_THROW_INFO(hrcall) GFX_THROW_NOINFO(hrcall)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) UrbanEngine::D3D11Graphics::DeviceRemovedException(__LINE__, __FILEW__, hr)
#define GFX_THROW_INFO_ONLY(call) (call)
#define INFO_MANAGER(gfx) HRESULT hr
#endif // URBAN_IS_DEBUG

