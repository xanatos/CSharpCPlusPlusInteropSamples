// Based on https://comcorba.tripod.com/comleaks.htm#IMallocSpy

#include "pch.h"

#include <Objidl.h>

#include <cstdio>
#include <cstring>
#include <vector>

#include "CMallocSpy.h"

// ******************************************************************
// ******************************************************************
// Constructor/Destructor
// ******************************************************************
// ******************************************************************

CMallocSpy::CMallocSpy() :
	m_cRef(1),
	m_map(),
	m_breakAlloc((size_t)-1),
	m_logEverything(false),
	m_cbRequest((SIZE_T)-1)
{
	// Perhaps it isn't the brightest idea to use dynamic memory 
	// allocations in a memory allocator spy... It is unclear what
	// allocator the C++ new operator uses, but it probably isn't
	// CoTaskMemAlloc. It should be HeapAlloc.
	m_map.reserve(INITIAL_ALLOCATIONS);
}

CMallocSpy::~CMallocSpy()
{
}

// ******************************************************************
// ******************************************************************
// IUnknown support ...
// ******************************************************************
// ******************************************************************

HRESULT CMallocSpy::QueryInterface(REFIID riid, LPVOID* ppUnk)
{
	HRESULT hr = S_OK;

	if (IsEqualIID(riid, IID_IUnknown))
	{
		*ppUnk = (IUnknown*)this;
		AddRef();
	}
	else if (IsEqualIID(riid, IID_IMallocSpy))
	{
		*ppUnk = (IMalloc*)this;
		AddRef();
	}
	else
	{
		*ppUnk = NULL;
		hr = E_NOINTERFACE;
	}

	return hr;
}

ULONG CMallocSpy::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

ULONG CMallocSpy::Release()
{
	ULONG cRef = InterlockedDecrement(&m_cRef);

	if (cRef == 0)
	{
		delete this;
	}

	return cRef;
}

// ******************************************************************
// ******************************************************************
// Utilities ...
// ******************************************************************
// ******************************************************************

void CMallocSpy::SetBreakAlloc(size_t allocNum)
{
	m_breakAlloc = allocNum;
}

void CMallocSpy::SetLogEverything(bool logEverything)
{
	m_logEverything = logEverything;
}

void CMallocSpy::Clear()
{
	m_map.clear();
	m_map.shrink_to_fit();
	m_map.reserve(INITIAL_ALLOCATIONS);
}

void CMallocSpy::Dump(void (print)(const wchar_t* pwstr))
{
	wchar_t buff[256];

	print(L"CoMallocSpy dump ->\n");

	bool leakDetected = false;

	for (size_t i = 0; i < m_map.size(); i++)
	{
		if (m_map[i] != (SIZE_T)-1)
		{
			leakDetected = true;
			swprintf_s(buff, sizeof(buff) / sizeof(wchar_t), L" IMalloc memory leak at [%zd] (%zu bytes)\n", i, m_map[i]);
			print(buff);
		}
	}

	if (!leakDetected)
	{
		print(L" No leaks detected :-)\n");
	}

	print(L"CoMallocSpy dump complete.\n");
}

// ******************************************************************
// ******************************************************************
// IMallocSpy methods ...
// ******************************************************************
// ******************************************************************

SIZE_T CMallocSpy::PreAlloc(SIZE_T cbRequest)
{
	if (m_logEverything)
	{
		wchar_t buff[256];
		swprintf_s(buff, sizeof(buff) / sizeof(wchar_t), L"PreAlloc(cbRequest = %zu)\n", cbRequest);
		::OutputDebugStringW(buff);
	}

	m_cbRequest = cbRequest;

	return cbRequest + HEADERSIZE;
}

void* CMallocSpy::PostAlloc(void* pActual)
{
	if (m_logEverything)
	{
		wchar_t buff[256];
		swprintf_s(buff, sizeof(buff) / sizeof(wchar_t), L"PostAlloc(pActual = %p)\n", pActual);
		::OutputDebugStringW(buff);
	}

	if (m_breakAlloc == m_map.size())
	{
		::DebugBreak();
	}

	//
	// Store the allocation counter and note that this allocation
	// is active in the map.
	//
	int counter = (int)m_map.size();
	memcpy(pActual, &counter, sizeof(int));

	if (m_map.size() == m_map.capacity())
	{
		wchar_t buff[256];
		swprintf_s(buff, sizeof(buff) / sizeof(wchar_t), L"Enlarging CMallocSpy::m_map, currently was %zu\n", m_map.capacity());
		::OutputDebugStringW(buff);
	}

	m_map.push_back(m_cbRequest);
	m_cbRequest = 0;

	return (void*)((char*)pActual + HEADERSIZE);
}

void* CMallocSpy::PreFree(void* pRequest, BOOL fSpyed)
{
	if (m_logEverything)
	{
		wchar_t buff[256];
		swprintf_s(buff, sizeof(buff) / sizeof(wchar_t), L"PreFree(pRequest = %p, fSpyed = %d)\n", pRequest, fSpyed);
		::OutputDebugStringW(buff);
	}

	if (!pRequest)
	{
		return NULL;
	}

	if (fSpyed)
	{
		//
		// Mark the allocation as inactive in the map.
		//
		int counter;
		pRequest = (void*)(((char*)pRequest) - HEADERSIZE);
		memcpy(&counter, pRequest, sizeof(int));
		m_map[counter] = (SIZE_T)-1;

		return pRequest;
	}
	else
	{
		return pRequest;
	}
}

void CMallocSpy::PostFree(BOOL fSpyed)
{
	if (m_logEverything)
	{
		wchar_t buff[256];
		swprintf_s(buff, sizeof(buff) / sizeof(wchar_t), L"PostFree(fSpyed = %d)\n", fSpyed);
		::OutputDebugStringW(buff);
	}
}

SIZE_T CMallocSpy::PreRealloc(void* pRequest,
	SIZE_T cbRequest,
	void** ppNewRequest,
	BOOL fSpyed)
{
	if (m_logEverything)
	{
		wchar_t buff[256];
		swprintf_s(buff, sizeof(buff) / sizeof(wchar_t), L"PreRealloc(pRequest = %p, cbRequest = %zu, fSpyed = %d)\n", pRequest, cbRequest, fSpyed);
		::OutputDebugStringW(buff);
	}

	m_cbRequest = cbRequest;

	if (fSpyed && pRequest != NULL)
	{
		//
		// Mark the allocation as inactive in the map since IMalloc::Realloc()
		// frees the originally allocated block.
		//
		int counter;
		char* actual = (char*)pRequest - HEADERSIZE;
		memcpy(&counter, actual, sizeof(int));
		m_map[counter] = (SIZE_T)-1;

		*ppNewRequest = (void*)(((char*)pRequest) - HEADERSIZE);
		return cbRequest + HEADERSIZE;
	}
	else
	{
		*ppNewRequest = pRequest;
		return cbRequest;
	}
}

void* CMallocSpy::PostRealloc(void* pActual, BOOL fSpyed)
{
	if (m_logEverything)
	{
		wchar_t buff[256];
		swprintf_s(buff, sizeof(buff) / sizeof(wchar_t), L"PostRealloc(pActual = %p, fSpyed = %d)\n", pActual, fSpyed);
		::OutputDebugStringW(buff);
	}

	if (fSpyed)
	{
		if (m_breakAlloc == m_map.size())
		{
			::DebugBreak();
		}

		//
		// Store the allocation counter and note that this allocation
		// is active in the map.
		//
		int counter = (int)m_map.size();
		memcpy(pActual, &counter, sizeof(int));

		if (m_map.size() == m_map.capacity())
		{
			wchar_t buff[256];
			swprintf_s(buff, sizeof(buff) / sizeof(wchar_t), L"Enlarging CMallocSpy::m_map, currently was %zu\n", m_map.capacity());
			::OutputDebugStringW(buff);
		}

		m_map.push_back(m_cbRequest);
		m_cbRequest = 0;

		return (void*)((char*)pActual + HEADERSIZE);
	}
	else
	{
		return pActual;
	}
}

void* CMallocSpy::PreGetSize(void* pRequest, BOOL fSpyed)
{
	if (m_logEverything)
	{
		wchar_t buff[256];
		swprintf_s(buff, sizeof(buff) / sizeof(wchar_t), L"PreGetSize(pRequest = %p, fSpyed = %d)\n", pRequest, fSpyed);
		::OutputDebugStringW(buff);
	}

	if (fSpyed)
	{
		return (void*)(((char*)pRequest) - HEADERSIZE);
	}
	else
	{
		return pRequest;
	}
}

SIZE_T CMallocSpy::PostGetSize(SIZE_T cbActual, BOOL fSpyed)
{
	if (m_logEverything)
	{
		wchar_t buff[256];
		swprintf_s(buff, sizeof(buff) / sizeof(wchar_t), L"PostGetSize(cbActual = %zu, fSpyed = %d)\n", cbActual, fSpyed);
		::OutputDebugStringW(buff);
	}

	if (fSpyed)
	{
		return cbActual - HEADERSIZE;
	}
	else
	{
		return cbActual;
	}
}

void* CMallocSpy::PreDidAlloc(void* pRequest, BOOL fSpyed)
{
	if (m_logEverything)
	{
		wchar_t buff[256];
		swprintf_s(buff, sizeof(buff) / sizeof(wchar_t), L"PreDidAlloc(pRequest = %p, fSpyed = %d)\n", pRequest, fSpyed);
		::OutputDebugStringW(buff);
	}

	if (fSpyed)
	{
		return (void*)(((char*)pRequest) - HEADERSIZE);
	}
	else
	{
		return pRequest;
	}
}

BOOL CMallocSpy::PostDidAlloc(void* pRequest, BOOL fSpyed, BOOL fActual)
{
	if (m_logEverything)
	{
		wchar_t buff[256];
		swprintf_s(buff, sizeof(buff) / sizeof(wchar_t), L"PostDidAlloc(pRequest = %p, fSpyed = %d, fActual = %d)\n", pRequest, fSpyed, fActual);
		::OutputDebugStringW(buff);
	}

	return fActual;
}

void CMallocSpy::PreHeapMinimize()
{
	if (m_logEverything)
	{
		wchar_t buff[256];
		swprintf_s(buff, sizeof(buff) / sizeof(wchar_t), L"PreHeapMinimize()");
		::OutputDebugStringW(buff);
	}
}

void CMallocSpy::PostHeapMinimize()
{
	if (m_logEverything)
	{
		wchar_t buff[256];
		swprintf_s(buff, sizeof(buff) / sizeof(wchar_t), L"PostHeapMinimize()");
		::OutputDebugStringW(buff);
	}
}

extern "C"
{
	__declspec(dllexport) void* __stdcall StartMallocSpy(void)
	{
		CMallocSpy* pMallocSpy = new CMallocSpy();

		if (FAILED(::CoRegisterMallocSpy(pMallocSpy)))
		{
			delete pMallocSpy;
			pMallocSpy = nullptr;
		}

		return pMallocSpy;
	}

	__declspec(dllexport) void __stdcall SetBreakAlloc(CMallocSpy* pMallocSpy, unsigned int allocNum)
	{
		pMallocSpy->SetBreakAlloc((size_t)allocNum);
	}

	__declspec(dllexport) void __stdcall DumpMallocSpy(CMallocSpy* pMallocSpy, void (print)(const wchar_t* pwstr))
	{
		pMallocSpy->Dump(print);
	}

	__declspec(dllexport) bool __stdcall StopMallocSpy()
	{
		return SUCCEEDED(::CoRevokeMallocSpy());
	}
}