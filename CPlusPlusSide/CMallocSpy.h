// Based on https://comcorba.tripod.com/comleaks.htm#IMallocSpy

#ifndef _CMallocSpy_h
#define _CMallocSpy_h

class CMallocSpy : public IMallocSpy
{
public:
	CMallocSpy();
	~CMallocSpy();

	//
	// IUnknown methods
	//
	STDMETHOD(QueryInterface) (REFIID riid, LPVOID* ppUnk);
	STDMETHOD_(ULONG, AddRef) ();
	STDMETHOD_(ULONG, Release) ();

	//
	// IMallocSpy methods
	//
	STDMETHOD_(SIZE_T, PreAlloc) (SIZE_T cbRequest);
	STDMETHOD_(void*, PostAlloc) (void* pActual);

	STDMETHOD_(void*, PreFree) (void* pRequest, BOOL fSpyed);
	STDMETHOD_(void, PostFree) (BOOL fSpyed);

	STDMETHOD_(SIZE_T, PreRealloc) (void* pRequest, SIZE_T cbRequest, void** ppNewRequest, BOOL fSpyed);
	STDMETHOD_(void*, PostRealloc) (void* pActual, BOOL fSpyed);

	STDMETHOD_(void*, PreGetSize) (void* pRequest, BOOL fSpyed);
	STDMETHOD_(SIZE_T, PostGetSize) (SIZE_T cbActual, BOOL fSpyed);

	STDMETHOD_(void*, PreDidAlloc) (void* pRequest, BOOL fSpyed);
	STDMETHOD_(BOOL, PostDidAlloc) (void* pRequest, BOOL fSpyed, BOOL fActual);

	STDMETHOD_(void, PreHeapMinimize) ();
	STDMETHOD_(void, PostHeapMinimize) ();

	//
	// Utilities ...
	//
	void Clear();
	void Dump(void (print)(const wchar_t* pwstr));
	void SetBreakAlloc(size_t allocNum);
	void SetLogEverything(bool logEverything);

protected:
	enum
	{
		HEADERSIZE = 2 * sizeof(void*), // Calculated experimentally
		INITIAL_ALLOCATIONS = 1000
	};

	volatile ULONG m_cRef;

	std::vector<SIZE_T> m_map;
	size_t  m_breakAlloc;
	bool    m_logEverything;

	SIZE_T  m_cbRequest;
};

#endif   // _CMallocSpy_h