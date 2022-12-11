#pragma once

#include <exception>
#include <string>

namespace UrbanEngine
{
	class UrbanException : public std::exception
	{
	public:
		UrbanException(int line, const char* file) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		int GetLine() const noexcept;
		const std::string& GetFile() const noexcept;
		std::string GetOriginString() const noexcept;
	private:
		int m_Line;
		std::string m_File;
	protected:
		mutable std::string m_WhatBuffer;
	};

	class UrbanExceptionUnicode : public std::exception
	{
	public:
		UrbanExceptionUnicode(int line, const wchar_t* file) noexcept;
		const char* what() const noexcept override;
		virtual const wchar_t* what_unicode() const noexcept;
		virtual const wchar_t* GetType() const noexcept;
		int GetLine() const noexcept;
		const std::wstring& GetFile() const noexcept;
		std::wstring GetOriginString() const noexcept;
	private:
		int m_Line;
		std::wstring m_File;
	protected:
		mutable std::wstring m_WhatBuffer;
	};
}
