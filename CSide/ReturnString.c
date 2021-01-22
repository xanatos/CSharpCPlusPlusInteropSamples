// ReturnString.c : 

#include "pch.h"

#include <combaseapi.h>
#include <OleAuto.h>
#include <stringapiset.h>
#include <tchar.h>

#include <stdlib.h>
#include <string.h>

__declspec(dllexport) char* __stdcall ReturnAnsiString(void)
{
#pragma warning(push)
#pragma warning(disable: 4566)
	const char* pstr = "Foo àèéìòù āēīōū";
#pragma warning(pop)

	// String returned is allocated with CoTaskMemAlloc
	// C# will free it
	size_t size = strlen(pstr) + 1;
	char* pstr2 = (char*)CoTaskMemAlloc(size);

	if (pstr2)
	{
		memcpy(pstr2, pstr, size);
	}

	return pstr2;
}

__declspec(dllexport) TCHAR* __stdcall ReturnAutoString(void)
{
	const TCHAR* pstr = _T("Foo àèéìòù āēīōū");

	// String returned is allocated with CoTaskMemAlloc
	// C# will free it
	size_t size = (_tcslen(pstr) + 1) * sizeof(TCHAR);
	TCHAR* pstr2 = (TCHAR*)CoTaskMemAlloc(size);

	if (pstr2)
	{
		memcpy(pstr2, pstr, size);
	}

	return pstr2;
}

__declspec(dllexport) wchar_t* __stdcall ReturnUnicodeString(void)
{
	const wchar_t* pwstr = L"Foo àèéìòù āēīōū";

	// String returned is allocated with CoTaskMemAlloc
	// C# will free it
	size_t len = wcslen(pwstr);
	size_t size = (len + 1) * sizeof(wchar_t);
	wchar_t* pwstr2 = (wchar_t*)CoTaskMemAlloc(size);

	if (pwstr2)
	{
		memcpy(pwstr2, pwstr, size);
	}

	return pwstr2;
}

__declspec(dllexport) char* __stdcall ReturnUtf8String(void)
{
	const char* pstr = u8"Foo àèéìòù āēīōū";

	// String returned is allocated with CoTaskMemAlloc
	// C# will free it
	size_t size = strlen(pstr) + 1;
	char* pstr2 = (char*)CoTaskMemAlloc(size);

	if (pstr2)
	{
		memcpy(pstr2, pstr, size);
	}

	return pstr2;
}

BSTR ConvertStringToBSTR(UINT codepage, const char* pstr)
{
	if (!pstr)
	{
		return NULL;
	}

	BSTR bstr = NULL;

	DWORD count = MultiByteToWideChar(codepage, 0, pstr, -1, NULL, 0);

	if (count)
	{
		// MultiByteToWideChar return length INCLUDING \0, 
		// SysAllocStringLen wants length EXCLUDING \0
		bstr = SysAllocStringLen(NULL, count - 1);

		if (bstr)
		{
			if (!MultiByteToWideChar(codepage, 0, pstr, -1, bstr, count))
			{
				//must clean up
				SysFreeString(bstr);
				bstr = NULL;
			}
		}
	}

	return bstr;
}

__declspec(dllexport) BSTR __stdcall ReturnBStrFromChar1(void)
{
#pragma warning(push)
#pragma warning(disable: 4566)
	const char* pstr = "Foo àèéìòù āēīōū";
#pragma warning(pop)

	BSTR bstr = ConvertStringToBSTR(CP_ACP, pstr);
	return bstr;
}

__declspec(dllexport) BSTR __stdcall ReturnBStrFromUtf8Char(void)
{
	const char* pstr = u8"Foo àèéìòù āēīōū";
	BSTR bstr = ConvertStringToBSTR(CP_UTF8, pstr);
	return bstr;
}

__declspec(dllexport) BSTR __stdcall ReturnBStrFromWChar1(void)
{
	const wchar_t* pwstr = L"Foo àèéìòù āēīōū";
	BSTR bstr = SysAllocString(pwstr);
	return bstr;
}

__declspec(dllexport) char* __stdcall ReturnAnsiStringPtrMalloc(void)
{
#pragma warning(push)
#pragma warning(disable: 4566)
	const char* pstr = "Foo àèéìòù āēīōū";
#pragma warning(pop)

	// Free with free()/Utils.c: MallocFree()

	// size_t len = strlen(pstr);
	// char* pstr2 = (char*)malloc(len + 1);
	// memcpy(pstr2, pstr, len + 1);
	// Equivalent (still use free()):
	char* pstr2 = _strdup(pstr);

	return pstr2;
}

__declspec(dllexport) wchar_t* __stdcall ReturnUnicodeStringPtrMalloc(void)
{
	const wchar_t* pwstr = L"Foo àèéìòù āēīōū";
	// Free with free()/Utils.c: MallocFree()
	wchar_t* pwstr2 = _wcsdup(pwstr);
	return pwstr2;
}

__declspec(dllexport) char* __stdcall ReturnUtf8StringPtrMalloc(void)
{
	const char* pstr = u8"Foo àèéìòù āēīōū";
	// Free with free()/Utils.c: MallocFree()
	char* pstr2 = _strdup(pstr);
	return pstr2;
}

__declspec(dllexport) const char* __stdcall ReturnAnsiStringPtrNoFree(void)
{
#pragma warning(push)
#pragma warning(disable: 4566)
	const char* pstr = "Foo àèéìòù āēīōū";
#pragma warning(pop)

	// Don't free()!
	return pstr;
}

__declspec(dllexport) const wchar_t* __stdcall ReturnUnicodeStringPtrNoFree(void)
{
	const wchar_t* pwstr = L"Foo àèéìòù āēīōū";
	// Don't free()!
	return pwstr;
}

__declspec(dllexport) const char* __stdcall ReturnUtf8StringPtrNoFree(void)
{
	const char* pstr = u8"Foo àèéìòù āēīōū";
	// Don't free()!
	return pstr;
}