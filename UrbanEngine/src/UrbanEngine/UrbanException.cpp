#include "urbanpch.h"
#include "UrbanException.h"

namespace UrbanEngine
{
	UrbanException::UrbanException(int line, const char* file) noexcept
		:
		m_Line(line),
		m_File(file)
	{ }

	const char* UrbanException::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< GetOriginString();
		m_WhatBuffer = oss.str();
		return m_WhatBuffer.c_str();
	}
	
	const char* UrbanException::GetType() const noexcept
	{
		return "Urban Engine Exception";
	}
	
	int UrbanException::GetLine() const noexcept
	{
		return m_Line;
	}
	
	const std::string& UrbanException::GetFile() const noexcept
	{
		return m_File;
	}
	
	std::string UrbanException::GetOriginString() const noexcept
	{
		std::ostringstream oss;
		oss << "[File] " << m_File << std::endl
			<< "[Line] " << m_Line;
		return oss.str();
	}




	UrbanExceptionUnicode::UrbanExceptionUnicode(int line, const wchar_t* file) noexcept
		:
		m_Line(line),
		m_File(file)
	{ }

	const char* UrbanExceptionUnicode::what() const noexcept
	{
		const wchar_t* unicode_what = what_unicode();
		size_t outputSize = m_WhatBuffer.size() + 1;
		char* output = new char[outputSize];
		wcstombs_s(nullptr, output, outputSize, unicode_what, _TRUNCATE);
		return output;
	}

	const wchar_t* UrbanExceptionUnicode::what_unicode() const noexcept
	{
		std::wostringstream wos;
		wos << GetType() << std::endl
			<< GetOriginString();
		m_WhatBuffer = wos.str();
		return m_WhatBuffer.c_str();
	}

	const wchar_t* UrbanExceptionUnicode::GetType() const noexcept
	{
		return L"Urban Engine Exception";
	}
	
	int UrbanExceptionUnicode::GetLine() const noexcept
	{
		return m_Line;
	}
	
	const std::wstring& UrbanExceptionUnicode::GetFile() const noexcept
	{
		return m_File;
	}
	
	std::wstring UrbanExceptionUnicode::GetOriginString() const noexcept
	{
		std::wostringstream wos;
		wos << L"[File] " << m_File << std::endl
			<< L"[Line] " << m_Line;
		return wos.str();
	}
}
