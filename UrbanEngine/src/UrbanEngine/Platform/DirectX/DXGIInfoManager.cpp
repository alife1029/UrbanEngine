#include "urbanpch.h"
#include "DXGIInfoManager.h"
#include "../Win32/Win32Window.h"
#include "D3D11Graphics.h"
#include "D3D11GraphicsThrowMacros.h"

#pragma comment(lib, "dxguid.lib")

namespace UrbanEngine
{
	DXGIInfoManager::DXGIInfoManager()
	{
		// Define function signature of DXGIGetDebugInterface
		typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);

		// Load the DLL that contains the function DXGIGetDebugInterface
		const auto hModDxgiDebug = LoadLibraryEx(L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
		if (hModDxgiDebug == nullptr) throw Win32Window::HrException(__LINE__, __FILEW__, GetLastError());

		// Get address of DXGIGetDebugInterface in the DLL
		const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface")));
		if (DxgiGetDebugInterface == nullptr) throw Win32Window::HrException(__LINE__, __FILEW__, GetLastError());

		HRESULT hr;
		GFX_THROW_NOINFO(DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &m_DxgiInfoQueue));
	}

	void DXGIInfoManager::Set() noexcept
	{
		m_Next = m_DxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	}

	std::vector<std::wstring> DXGIInfoManager::GetMessages() const
	{
		std::vector<std::wstring> messages;

		const auto end = m_DxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
		for (auto i = m_Next; i < end; i++)
		{
			HRESULT hr;
			SIZE_T messageLength;

			// Get the size of the message in bytes
			GFX_THROW_NOINFO(m_DxgiInfoQueue->GetMessageW(DXGI_DEBUG_ALL, i, nullptr, &messageLength));

			// Allocate memory for the message
			auto bytes = std::make_unique<byte[]>(messageLength);
			auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());

			// Get the message and push its description into the vector
			GFX_THROW_NOINFO(m_DxgiInfoQueue->GetMessageW(DXGI_DEBUG_ALL, i, pMessage, &messageLength));
			messages.push_back(reinterpret_cast<const wchar_t*>(pMessage->pDescription));
		}

		return messages;
	}
}
