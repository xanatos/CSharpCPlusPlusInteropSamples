// ReturnArrayStruct.c : 

#include "pch.h"

#include <combaseapi.h>
#include <OleAuto.h>

#include <string.h>

typedef struct StructStringAnsiInt
{
	char* pstr;
	int num;
} StructStringAnsiInt;

typedef struct StructStringUnicodeInt
{
	wchar_t* pwstr;
	int num;
} StructStringUnicodeInt;

typedef struct StructStringUtf8Int
{
	char* pstr;
	int num;
} StructStringUtf8Int;

typedef struct StructBStrInt
{
	BSTR bstr;
	int num;
} StructBStrInt;

//

__declspec(dllexport) StructStringAnsiInt* __stdcall ReturnArrayStructStringAnsiInt(int* pcount)
{
#pragma warning(push)
#pragma warning(disable: 4566)
	const char* ppstr[] = { "Foo àèéìòù āēīōū", "Bar àèéìòù āēīōū", "Baz àèéìòù āēīōū" };
#pragma warning(pop)

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	StructStringAnsiInt* pstruct = (StructStringAnsiInt*)CoTaskMemAlloc(count * sizeof(StructStringAnsiInt));

	if (!pstruct)
	{
		*pcount = 0;
		return NULL;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		size_t len = strlen(ppstr[i]);
		size_t size = len + 1;

		pstruct[i].pstr = (char*)CoTaskMemAlloc(size);

		if (pstruct[i].pstr)
		{
			memcpy(pstruct[i].pstr, ppstr[i], size);
		}

		pstruct[i].num = ((int)i + 1) * 2;
	}

	return pstruct;
}

__declspec(dllexport) StructStringUnicodeInt* __stdcall ReturnArrayStructStringUnicodeInt(int* pcount)
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	StructStringUnicodeInt* pstruct = (StructStringUnicodeInt*)CoTaskMemAlloc(count * sizeof(StructStringUnicodeInt));

	if (!pstruct)
	{
		*pcount = 0;
		return NULL;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		size_t len = wcslen(ppwstr[i]);
		size_t size = (len + 1) * sizeof(wchar_t);

		pstruct[i].pwstr = (wchar_t*)CoTaskMemAlloc(size);

		if (pstruct[i].pwstr)
		{
			memcpy(pstruct[i].pwstr, ppwstr[i], size);
		}

		pstruct[i].num = ((int)i + 1) * 2;
	}

	return pstruct;
}

__declspec(dllexport) StructStringUtf8Int* __stdcall ReturnArrayStructStringUtf8Int(int* pcount)
{
	const char* ppstr[] = { u8"Foo àèéìòù āēīōū", u8"Bar àèéìòù āēīōū", u8"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	StructStringUtf8Int* pstruct = (StructStringUtf8Int*)CoTaskMemAlloc(count * sizeof(StructStringUtf8Int));

	if (!pstruct)
	{
		*pcount = 0;
		return NULL;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		size_t len = strlen(ppstr[i]);
		size_t size = len + 1;

		pstruct[i].pstr = (char*)CoTaskMemAlloc(size);

		if (pstruct[i].pstr)
		{
			memcpy(pstruct[i].pstr, ppstr[i], size);
		}

		pstruct[i].num = ((int)i + 1) * 2;
	}

	return pstruct;
}

__declspec(dllexport) StructBStrInt* __stdcall ReturnArrayStructBStrInt(int* pcount)
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	StructBStrInt* pstruct = (StructBStrInt*)CoTaskMemAlloc(count * sizeof(StructBStrInt));

	if (!pstruct)
	{
		*pcount = 0;
		return NULL;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		pstruct[i].bstr = SysAllocString(ppwstr[i]);
		pstruct[i].num = ((int)i + 1) * 2;
	}

	return pstruct;
}

//

__declspec(dllexport) StructStringAnsiInt** __stdcall ReturnArrayPtrStructStringAnsiInt(int* pcount)
{
#pragma warning(push)
#pragma warning(disable: 4566)
	const char* ppstr[] = { "Foo àèéìòù āēīōū", "Bar àèéìòù āēīōū", "Baz àèéìòù āēīōū" };
#pragma warning(pop)

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	StructStringAnsiInt** ppstruct = (StructStringAnsiInt**)CoTaskMemAlloc(count * sizeof(StructStringAnsiInt*));

	if (!ppstruct)
	{
		*pcount = 0;
		return NULL;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		StructStringAnsiInt* pstruct = (StructStringAnsiInt*)CoTaskMemAlloc(sizeof(StructStringAnsiInt));
		ppstruct[i] = pstruct;

		if (pstruct)
		{
			size_t len = strlen(ppstr[i]);
			size_t size = len + 1;

			pstruct->pstr = (char*)CoTaskMemAlloc(size);

			if (pstruct->pstr)
			{
				memcpy(pstruct->pstr, ppstr[i], size);
			}

			pstruct->num = ((int)i + 1) * 2;
		}
	}

	return ppstruct;
}

__declspec(dllexport) StructStringUnicodeInt** __stdcall ReturnArrayPtrStructStringUnicodeInt(int* pcount)
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	StructStringUnicodeInt** ppstruct = (StructStringUnicodeInt**)CoTaskMemAlloc(count * sizeof(StructStringUnicodeInt*));

	if (!ppstruct)
	{
		*pcount = 0;
		return NULL;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		StructStringUnicodeInt* pstruct = (StructStringUnicodeInt*)CoTaskMemAlloc(sizeof(StructStringUnicodeInt));
		ppstruct[i] = pstruct;

		if (pstruct)
		{
			size_t len = wcslen(ppwstr[i]);
			size_t size = (len + 1) * sizeof(wchar_t);

			pstruct->pwstr = (wchar_t*)CoTaskMemAlloc(size);

			if (pstruct->pwstr)
			{
				memcpy(pstruct->pwstr, ppwstr[i], size);
			}

			pstruct->num = ((int)i + 1) * 2;
		}
	}

	return ppstruct;
}

__declspec(dllexport) StructStringUtf8Int** __stdcall ReturnArrayPtrStructStringUtf8Int(int* pcount)
{
	const char* ppstr[] = { u8"Foo àèéìòù āēīōū", u8"Bar àèéìòù āēīōū", u8"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	StructStringUtf8Int** ppstruct = (StructStringUtf8Int**)CoTaskMemAlloc(count * sizeof(StructStringUtf8Int*));

	if (!ppstruct)
	{
		*pcount = 0;
		return NULL;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		StructStringUtf8Int* pstruct = (StructStringUtf8Int*)CoTaskMemAlloc(sizeof(StructStringUtf8Int));
		ppstruct[i] = pstruct;

		if (pstruct)
		{
			size_t len = strlen(ppstr[i]);
			size_t size = len + 1;

			pstruct->pstr = (char*)CoTaskMemAlloc(size);

			if (pstruct->pstr)
			{
				memcpy(pstruct->pstr, ppstr[i], size);
			}

			pstruct->num = ((int)i + 1) * 2;
		}
	}

	return ppstruct;
}

__declspec(dllexport) StructBStrInt** __stdcall ReturnArrayPtrStructBStrInt(int* pcount)
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	StructBStrInt** ppstruct = (StructBStrInt**)CoTaskMemAlloc(count * sizeof(StructBStrInt*));

	if (!ppstruct)
	{
		*pcount = 0;
		return NULL;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		StructBStrInt* pstruct = (StructBStrInt*)CoTaskMemAlloc(sizeof(StructBStrInt));
		ppstruct[i] = pstruct;

		if (pstruct)
		{
			pstruct->bstr = SysAllocString(ppwstr[i]);
			pstruct->num = ((int)i + 1) * 2;
		}
	}

	return ppstruct;
}

//

__declspec(dllexport) StructStringAnsiInt** __stdcall ReturnArrayPtrStructStringAnsiIntNullTerminated(void)
{
#pragma warning(push)
#pragma warning(disable: 4566)
	const char* ppstr[] = { "Foo àèéìòù āēīōū", "Bar àèéìòù āēīōū", "Baz àèéìòù āēīōū" };
#pragma warning(pop)

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	StructStringAnsiInt** ppstruct = (StructStringAnsiInt**)CoTaskMemAlloc((count + 1) * sizeof(StructStringAnsiInt*));

	if (!ppstruct)
	{
		return NULL;
	}

	for (size_t i = 0; i < count; i++)
	{
		StructStringAnsiInt* pstruct = (StructStringAnsiInt*)CoTaskMemAlloc(sizeof(StructStringAnsiInt));
		ppstruct[i] = pstruct;

		if (pstruct)
		{
			size_t len = strlen(ppstr[i]);
			size_t size = len + 1;

			pstruct->pstr = (char*)CoTaskMemAlloc(size);

			if (pstruct->pstr)
			{
				memcpy(pstruct->pstr, ppstr[i], size);
			}

			pstruct->num = ((int)i + 1) * 2;
		}
	}

	// Final NULL terminator
	ppstruct[count] = NULL;

	return ppstruct;
}

__declspec(dllexport) StructStringUnicodeInt** __stdcall ReturnArrayPtrStructStringUnicodeIntNullTerminated(void)
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	StructStringUnicodeInt** ppstruct = (StructStringUnicodeInt**)CoTaskMemAlloc((count + 1) * sizeof(StructStringUnicodeInt*));

	if (!ppstruct)
	{
		return NULL;
	}

	for (size_t i = 0; i < count; i++)
	{
		StructStringUnicodeInt* pstruct = (StructStringUnicodeInt*)CoTaskMemAlloc(sizeof(StructStringUnicodeInt));
		ppstruct[i] = pstruct;

		if (pstruct)
		{
			size_t len = wcslen(ppwstr[i]);
			size_t size = (len + 1) * sizeof(wchar_t);

			pstruct->pwstr = (wchar_t*)CoTaskMemAlloc(size);

			if (pstruct->pwstr)
			{
				memcpy(pstruct->pwstr, ppwstr[i], size);
			}

			pstruct->num = ((int)i + 1) * 2;
		}
	}

	// Final NULL terminator
	ppstruct[count] = NULL;

	return ppstruct;
}

__declspec(dllexport) StructStringUtf8Int** __stdcall ReturnArrayPtrStructStringUtf8IntNullTerminated(void)
{
	const char* ppstr[] = { u8"Foo àèéìòù āēīōū", u8"Bar àèéìòù āēīōū", u8"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	StructStringUtf8Int** ppstruct = (StructStringUtf8Int**)CoTaskMemAlloc((count + 1) * sizeof(StructStringUtf8Int*));

	if (!ppstruct)
	{
		return NULL;
	}

	for (size_t i = 0; i < count; i++)
	{
		StructStringUtf8Int* pstruct = (StructStringUtf8Int*)CoTaskMemAlloc(sizeof(StructStringUtf8Int));
		ppstruct[i] = pstruct;

		if (pstruct)
		{
			size_t len = strlen(ppstr[i]);
			size_t size = len + 1;

			pstruct->pstr = (char*)CoTaskMemAlloc(size);

			if (pstruct->pstr)
			{
				memcpy(pstruct->pstr, ppstr[i], size);
			}

			pstruct->num = ((int)i + 1) * 2;
		}
	}

	// Final NULL terminator
	ppstruct[count] = NULL;

	return ppstruct;
}

__declspec(dllexport) StructBStrInt** __stdcall ReturnArrayPtrStructBStrIntNullTerminated(void)
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	StructBStrInt** ppstruct = (StructBStrInt**)CoTaskMemAlloc((count + 1) * sizeof(StructBStrInt*));

	if (!ppstruct)
	{
		return NULL;
	}

	for (size_t i = 0; i < count; i++)
	{
		StructBStrInt* pstruct = (StructBStrInt*)CoTaskMemAlloc(sizeof(StructBStrInt));
		ppstruct[i] = pstruct;

		if (pstruct)
		{
			pstruct->bstr = SysAllocString(ppwstr[i]);
			pstruct->num = ((int)i + 1) * 2;
		}
	}

	// Final NULL terminator
	ppstruct[count] = NULL;

	return ppstruct;
}

//

__declspec(dllexport) void __stdcall PassOutArrayStructStringAnsiInt(StructStringAnsiInt** ppstruct, int* pcount)
{
#pragma warning(push)
#pragma warning(disable: 4566)
	const char* ppstr[] = { "Foo àèéìòù āēīōū", "Bar àèéìòù āēīōū", "Baz àèéìòù āēīōū" };
#pragma warning(pop)

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	*ppstruct = (StructStringAnsiInt*)CoTaskMemAlloc(count * sizeof(StructStringAnsiInt));

	if (!*ppstruct)
	{
		*pcount = 0;
		return;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		size_t len = strlen(ppstr[i]);
		size_t size = len + 1;

		(*ppstruct)[i].pstr = (char*)CoTaskMemAlloc(size);

		if ((*ppstruct)[i].pstr)
		{
			memcpy((*ppstruct)[i].pstr, ppstr[i], size);
		}

		(*ppstruct)[i].num = ((int)i + 1) * 2;
	}
}

__declspec(dllexport) void __stdcall PassOutArrayStructStringUnicodeInt(StructStringUnicodeInt** ppstruct, int* pcount)
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	*ppstruct = (StructStringUnicodeInt*)CoTaskMemAlloc(count * sizeof(StructStringUnicodeInt));

	if (!*ppstruct)
	{
		*pcount = 0;
		return;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		size_t len = wcslen(ppwstr[i]);
		size_t size = (len + 1) * sizeof(wchar_t);

		(*ppstruct)[i].pwstr = (wchar_t*)CoTaskMemAlloc(size);

		if ((*ppstruct)[i].pwstr)
		{
			memcpy((*ppstruct)[i].pwstr, ppwstr[i], size);
		}

		(*ppstruct)[i].num = ((int)i + 1) * 2;
	}
}

__declspec(dllexport) void __stdcall PassOutArrayStructStringUtf8Int(StructStringUtf8Int** ppstruct, int* pcount)
{
	const char* ppstr[] = { u8"Foo àèéìòù āēīōū", u8"Bar àèéìòù āēīōū", u8"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	*ppstruct = (StructStringUtf8Int*)CoTaskMemAlloc(count * sizeof(StructStringUtf8Int));

	if (!*ppstruct)
	{
		*pcount = 0;
		return;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		size_t len = strlen(ppstr[i]);
		size_t size = len + 1;

		(*ppstruct)[i].pstr = (char*)CoTaskMemAlloc(size);

		if ((*ppstruct)[i].pstr)
		{
			memcpy((*ppstruct)[i].pstr, ppstr[i], size);
		}

		(*ppstruct)[i].num = ((int)i + 1) * 2;
	}
}

__declspec(dllexport) void __stdcall PassOutArrayStructBStrInt(StructBStrInt** ppstruct, int* pcount)
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	*ppstruct = (StructBStrInt*)CoTaskMemAlloc(count * sizeof(StructBStrInt));

	if (!*ppstruct)
	{
		*pcount = 0;
		return;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		(*ppstruct)[i].bstr = SysAllocString(ppwstr[i]);
		(*ppstruct)[i].num = ((int)i + 1) * 2;
	}
}

__declspec(dllexport) void __stdcall PassOutThroughDelegateArrayStructStringAnsiInt(void(__stdcall add)(const char* pstr, int num))
{
#pragma warning(push)
#pragma warning(disable: 4566)
	const char* ppstr[] = { "Foo àèéìòù āēīōū", "Bar àèéìòù āēīōū", "Baz àèéìòù āēīōū" };
#pragma warning(pop)

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	for (size_t i = 0; i < count; i++)
	{
		add(ppstr[i], ((int)i + 1) * 2);
	}
}

__declspec(dllexport) void __stdcall PassOutThroughDelegateArrayStructStringUnicodeInt(void(__stdcall add)(const wchar_t* pwstr, int num))
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	for (size_t i = 0; i < count; i++)
	{
		add(ppwstr[i], ((int)i + 1) * 2);
	}
}

__declspec(dllexport) void __stdcall PassOutThroughDelegateArrayStructStringUtf8Int(void(__stdcall add)(const char* pstr, int num))
{
	const char* ppstr[] = { u8"Foo àèéìòù āēīōū", u8"Bar àèéìòù āēīōū", u8"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppstr) / sizeof(ppstr[0]);

	for (size_t i = 0; i < count; i++)
	{
		add(ppstr[i], ((int)i + 1) * 2);
	}
}

__declspec(dllexport) void __stdcall PassOutThroughDelegateArrayStructBStrInt1(void(__stdcall add)(const BSTR bstr, int num))
{
	const wchar_t* ppwstr[] = { L"Foo àèéìòù āēīōū", L"Bar àèéìòù āēīōū", L"Baz àèéìòù āēīōū" };

	size_t count = sizeof(ppwstr) / sizeof(ppwstr[0]);

	for (size_t i = 0; i < count; i++)
	{
		BSTR bstr = SysAllocString(ppwstr[i]);
		add(bstr, ((int)i + 1) * 2);
		SysFreeString(bstr);
	}
}
