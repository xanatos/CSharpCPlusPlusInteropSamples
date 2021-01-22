// ReturnString.cpp : 

#include "pch.h"

#include <comutil.h>

extern "C"
{
	__declspec(dllexport) BSTR __stdcall ReturnBStrFromChar2()
	{
#pragma warning(push)
#pragma warning(disable: 4566)
		const char* pstr = "Foo àèéìòù āēīōū";
#pragma warning(pop)

		_bstr_t bstr(pstr);

		// Important to Detach() here!
		// otherwise the _bstr_t destructor will free the string!
		return bstr.Detach();
	}

	__declspec(dllexport) BSTR __stdcall ReturnBStrFromChar3()
	{
#pragma warning(push)
#pragma warning(disable: 4566)
		const char* pstr = "Foo àèéìòù āēīōū";
#pragma warning(pop)

		BSTR bstr = _com_util::ConvertStringToBSTR(pstr);
		return bstr;
	}

	__declspec(dllexport) BSTR __stdcall ReturnBStrFromWChar2()
	{
		const wchar_t* pwstr = L"Foo àèéìòù āēīōū";
		_bstr_t bstr(pwstr);

		// Important to Detach() here!
		// otherwise the _bstr_t destructor will free the string!
		return bstr.Detach();
	}
}