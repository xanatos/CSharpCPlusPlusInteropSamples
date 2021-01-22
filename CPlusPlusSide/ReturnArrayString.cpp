// ReturnArrayString.cpp : 

#include "pch.h"

#include <comutil.h>

extern "C"
{
	__declspec(dllexport) void __stdcall PassOutThroughDelegateArrayBStr2(void(__stdcall add)(BSTR bstr))
	{
		const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

		size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

		for (size_t i = 0; i < count; i++)
		{
			_bstr_t bstr(ppwstr[i]);
			add(bstr.GetBSTR());
		}
	}
}