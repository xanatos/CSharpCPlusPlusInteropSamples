// ReturnArrayString.c : 

#include "pch.h"

#include <combaseapi.h>
#include <OleAuto.h>

#include <string.h>

__declspec(dllexport) char** __stdcall ReturnArrayStringAnsi(int* pcount)
{
#pragma warning(push)
#pragma warning(disable: 4566)
	const char* ppstr[] = { "Foo àèéìòù āēīōū", "Bar àèéìòù āēīōū", "Baz àèéìòù āēīōū" };
#pragma warning(pop)

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	// Or malloc, and C# will need to call FreeMalloc
	char** ppstr2 = (char**)CoTaskMemAlloc(count * sizeof(char*));

	if (!ppstr2)
	{
		*pcount = 0;
		return NULL;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		size_t len = strlen(ppstr[i]);
		size_t size = len + 1;

		// Or malloc, and C# will need to call FreeMalloc
		ppstr2[i] = (char*)CoTaskMemAlloc(size);

		if (ppstr2[i])
		{
			memcpy(ppstr2[i], ppstr[i], size);
		}
	}

	return ppstr2;
}

__declspec(dllexport) wchar_t** __stdcall ReturnArrayStringUnicode(int* pcount)
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	// Or malloc, and C# will need to call FreeMalloc
	wchar_t** ppwstr2 = (wchar_t**)CoTaskMemAlloc(count * sizeof(wchar_t*));

	if (!ppwstr2)
	{
		*pcount = 0;
		return NULL;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		size_t len = wcslen(ppwstr[i]);
		size_t size = (len + 1) * sizeof(wchar_t);

		// Or malloc, and C# will need to call FreeMalloc
		ppwstr2[i] = (wchar_t*)CoTaskMemAlloc(size);

		if (ppwstr2[i])
		{
			memcpy(ppwstr2[i], ppwstr[i], size);
		}
	}

	return ppwstr2;
}

__declspec(dllexport) char** __stdcall ReturnArrayStringUtf8(int* pcount)
{
	const char* ppstr[] = { u8"Foo àèéìòù āēīōū", u8"Bar àèéìòù āēīōū", u8"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	// Or malloc, and C# will need to call FreeMalloc
	char** ppstr2 = (char**)CoTaskMemAlloc(count * sizeof(char*));

	if (!ppstr2)
	{
		*pcount = 0;
		return NULL;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		size_t len = strlen(ppstr[i]);
		size_t size = len + 1;

		// Or malloc, and C# will need to call FreeMalloc
		ppstr2[i] = (char*)CoTaskMemAlloc(size);

		if (ppstr2[i])
		{
			memcpy(ppstr2[i], ppstr[i], size);
		}
	}

	return ppstr2;
}

__declspec(dllexport) BSTR* __stdcall ReturnArrayBStr(int* pcount)
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	// Or malloc, and C# will need to call FreeMalloc
	BSTR* pbstr = (BSTR*)CoTaskMemAlloc(count * sizeof(BSTR));

	if (!pbstr)
	{
		*pcount = 0;
		return NULL;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		pbstr[i] = SysAllocString(ppwstr[i]);
	}

	return pbstr;
}

//

__declspec(dllexport) char** __stdcall ReturnArrayStringAnsiNullTerminated(void)
{
#pragma warning(push)
#pragma warning(disable: 4566)
	const char* ppstr[] = { "Foo àèéìòù āēīōū", "Bar àèéìòù āēīōū", "Baz àèéìòù āēīōū" };
#pragma warning(pop)

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	// Or malloc, and C# will need to call FreeMalloc
	char** ppstr2 = (char**)CoTaskMemAlloc((count + 1) * sizeof(char*));

	if (!ppstr2)
	{
		return NULL;
	}

	for (size_t i = 0; i < count; i++)
	{
		size_t len = strlen(ppstr[i]);
		size_t size = len + 1;

		// Or malloc, and C# will need to call FreeMalloc
		ppstr2[i] = (char*)CoTaskMemAlloc(size);

		if (ppstr2[i])
		{
			memcpy(ppstr2[i], ppstr[i], size);
		}
	}

	// Final NULL terminator
	ppstr2[count] = NULL;

	return ppstr2;
}

__declspec(dllexport) wchar_t** __stdcall ReturnArrayStringUnicodeNullTerminated(void)
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	// Or malloc, and C# will need to call FreeMalloc
	wchar_t** ppwstr2 = (wchar_t**)CoTaskMemAlloc((count + 1) * sizeof(wchar_t*));

	if (!ppwstr2)
	{
		return NULL;
	}

	for (size_t i = 0; i < count; i++)
	{
		size_t len = wcslen(ppwstr[i]);
		size_t size = (len + 1) * sizeof(wchar_t);

		// Or malloc, and C# will need to call FreeMalloc
		ppwstr2[i] = (wchar_t*)CoTaskMemAlloc(size);

		if (ppwstr2[i])
		{
			memcpy(ppwstr2[i], ppwstr[i], size);
		}
	}

	// Final NULL terminator
	ppwstr2[count] = NULL;

	return ppwstr2;
}

__declspec(dllexport) char** __stdcall ReturnArrayStringUtf8NullTerminated(void)
{
	const char* ppstr[] = { u8"Foo àèéìòù āēīōū", u8"Bar àèéìòù āēīōū", u8"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	// Or malloc, and C# will need to call FreeMalloc
	char** ppstr2 = (char**)CoTaskMemAlloc((count + 1) * sizeof(char*));

	if (!ppstr2)
	{
		return NULL;
	}

	for (size_t i = 0; i < count; i++)
	{
		size_t len = strlen(ppstr[i]);
		size_t size = len + 1;

		// Or malloc, and C# will need to call FreeMalloc
		ppstr2[i] = (char*)CoTaskMemAlloc(size);

		if (ppstr2[i])
		{
			memcpy(ppstr2[i], ppstr[i], size);
		}
	}

	// Final NULL terminator
	ppstr2[count] = NULL;

	return ppstr2;
}

__declspec(dllexport) wchar_t** __stdcall ReturnArrayBStrNullTerminated(void)
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	// Or malloc, and C# will need to call FreeMalloc
	wchar_t** ppwstr2 = (wchar_t**)CoTaskMemAlloc((count + 1) * sizeof(wchar_t*));

	if (!ppwstr2)
	{
		return NULL;
	}

	for (size_t i = 0; i < count; i++)
	{
		ppwstr2[i] = SysAllocString(ppwstr[i]);
	}

	// Final NULL terminator
	ppwstr2[count] = NULL;

	return ppwstr2;
}

//

__declspec(dllexport) void __stdcall PassOutArrayStringAnsi(char*** pppstr, int* pcount)
{
#pragma warning(push)
#pragma warning(disable: 4566)
	const char* ppstr[] = { "Foo àèéìòù āēīōū", "Bar àèéìòù āēīōū", "Baz àèéìòù āēīōū" };
#pragma warning(pop)

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	*pppstr = (char**)CoTaskMemAlloc(count * sizeof(char*));

	if (!*pppstr)
	{
		*pcount = 0;
		return;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		size_t len = strlen(ppstr[i]);
		size_t size = len + 1;

		(*pppstr)[i] = (char*)CoTaskMemAlloc(size);

		if ((*pppstr)[i])
		{
			memcpy((*pppstr)[i], ppstr[i], size);
		}
	}
}

__declspec(dllexport) void __stdcall PassOutArrayStringUnicode(wchar_t*** pppwstr, int* pcount)
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	*pppwstr = (wchar_t**)CoTaskMemAlloc(count * sizeof(wchar_t*));

	if (!*pppwstr)
	{
		*pcount = 0;
		return;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		size_t len = wcslen(ppwstr[i]);
		size_t size = (len + 1) * sizeof(wchar_t);

		(*pppwstr)[i] = (wchar_t*)CoTaskMemAlloc(size);

		if ((*pppwstr)[i])
		{
			memcpy((*pppwstr)[i], ppwstr[i], size);
		}
	}
}

__declspec(dllexport) void __stdcall PassOutArrayStringUtf8(char*** pppstr, int* pcount)
{
	const char* ppstr[] = { u8"Foo àèéìòù āēīōū", u8"Bar àèéìòù āēīōū", u8"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	*pppstr = (char**)CoTaskMemAlloc(count * sizeof(char*));

	if (!*pppstr)
	{
		*pcount = 0;
		return;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		size_t len = strlen(ppstr[i]);
		size_t size = len + 1;

		(*pppstr)[i] = (char*)CoTaskMemAlloc(size);

		if ((*pppstr)[i])
		{
			memcpy((*pppstr)[i], ppstr[i], size);
		}
	}
}

__declspec(dllexport) void __stdcall PassOutArrayBStr(BSTR** ppbstr, int* pcount)
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	*ppbstr = (BSTR*)CoTaskMemAlloc(count * sizeof(BSTR));

	if (!*ppbstr)
	{
		*pcount = 0;
		return;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		(*ppbstr)[i] = SysAllocString(ppwstr[i]);
	}
}

//

__declspec(dllexport) void __stdcall PassOutThroughDelegateArrayStringAnsi(void(__stdcall add)(const char* pstr))
{
#pragma warning(push)
#pragma warning(disable: 4566)
	const char* ppstr[] = { "Foo àèéìòù āēīōū", "Bar àèéìòù āēīōū", "Baz àèéìòù āēīōū" };
#pragma warning(pop)

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	for (size_t i = 0; i < count; i++)
	{
		add(ppstr[i]);
	}
}

__declspec(dllexport) void __stdcall PassOutThroughDelegateArrayStringUnicode(void(__stdcall add)(const wchar_t* pwstr))
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	for (size_t i = 0; i < count; i++)
	{
		add(ppwstr[i]);
	}
}

__declspec(dllexport) void __stdcall PassOutThroughDelegateArrayStringUtf8(void(__stdcall add)(const char* pstr))
{
	const char* ppstr[] = { u8"Foo àèéìòù āēīōū", u8"Bar àèéìòù āēīōū", u8"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	for (size_t i = 0; i < count; i++)
	{
		add(ppstr[i]);
	}
}

__declspec(dllexport) void __stdcall PassOutThroughDelegateArrayBStr1(void(__stdcall add)(const BSTR bstr))
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	for (size_t i = 0; i < count; i++)
	{
		BSTR bstr = SysAllocString(ppwstr[i]);
		add(bstr);
		SysFreeString(bstr);
	}
}
