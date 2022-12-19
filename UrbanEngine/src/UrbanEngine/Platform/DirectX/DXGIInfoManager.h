#pragma once

#include <Windows.h>

#include <string>
#include <vector>
#include <dxgidebug.h>
#include <wrl.h>

namespace UrbanEngine
{
	class DXGIInfoManager
	{
	public:
		DXGIInfoManager();
		~DXGIInfoManager() = default;
		DXGIInfoManager(const DXGIInfoManager&) = delete;
		DXGIInfoManager& operator=(DXGIInfoManager&) = delete;

		void Set() noexcept;
		std::vector<std::wstring> GetMessages() const;

	private:
		unsigned long long m_Next = 0u;
		Microsoft::WRL::ComPtr<IDXGIInfoQueue> m_DxgiInfoQueue;
	};
}
