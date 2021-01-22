// PassString.c : 

#include "pch.h"

#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <tchar.h>
#include <wtypes.h>

__declspec(dllexport) void __stdcall PrintAnsiString(const char* pch)
{
	printf("C Side, PrintAnsiString: %s, length: %zu, bytes: %zu\n", pch, strlen(pch), strlen(pch) * sizeof(char));
}

__declspec(dllexport) void __stdcall PrintUtf8String(const char* pch)
{
	printf("C Side, PrintUtf8String: %s, length: %zu, bytes: %zu\n", pch, strlen(pch), strlen(pch) * sizeof(char));
}

__declspec(dllexport) void __stdcall PrintUnicodeString(const wchar_t* pwch)
{
	int oldmode = _setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(L"C Side, PrintUnicodeString: %s, length: %zu, bytes: %zu\n", pwch, wcslen(pwch), wcslen(pwch) * sizeof(wchar_t));
	(void)_setmode(_fileno(stdout), oldmode);
}

// Used to auto-choose between Ansi and Unicode on older Windows
__declspec(dllexport) void __stdcall PrintAutoString(const TCHAR* pch)
{
	int oldmode = _setmode(_fileno(stdout), sizeof(TCHAR) == sizeof(char) ? _O_TEXT : _O_U16TEXT);
	_tprintf(_T("C Side, PrintAutoString: %s, length: %zu, bytes: %zu\n"), pch, _tcslen(pch), _tcslen(pch) * sizeof(TCHAR));
	(void)_setmode(_fileno(stdout), oldmode);
}

// In input it is equivalent to wchar_t*
__declspec(dllexport) void __stdcall PrintBStr(const BSTR bstr)
{
	int oldmode = _setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(_T("C Side, PrintBStr: %s, length: %u, bytes: %u\n"), bstr, SysStringLen(bstr), SysStringByteLen(bstr));
	(void)_setmode(_fileno(stdout), oldmode);
}

typedef struct StringRef
{
	// Not zero-terminated string!
	char* PBytes;
	int Length;
} StringRef;

__declspec(dllexport) void __stdcall PrintArrayStringRef(const StringRef* pstrref, int count)
{
	printf("C Side, PrintArrayStringRef: ");

	for (int i = 0; i < count; i++)
	{
		if (i != 0)
		{
			printf(", ");
		}

		printf("%.*s", pstrref[i].Length, pstrref[i].PBytes);
	}

	printf("\n");
}

__declspec(dllexport) void __stdcall PrintArray(const char** ppstr, int count)
{
	printf("C Side, PrintArray: ");

	for (int i = 0; i < count; i++)
	{
		if (i != 0)
		{
			printf(", ");
		}

		const char* pch = ppstr[i];

		printf("%s", pch);
	}

	printf("\n");
}

// Null-terminated array (the last element MUST be null)
__declspec(dllexport) void __stdcall PrintArrayNullTerminated(const char** ppstr)
{
	printf("C Side, PrintArrayNullTerminated: ");

	for (size_t i = 0; ; i++)
	{
		const char* pch = ppstr[i];

		if (!pch)
		{
			break;
		}

		if (i != 0)
		{
			printf(", ");
		}

		printf("%s", pch);
	}

	printf("\n");
}
