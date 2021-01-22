// ReturnString.cpp : 

#include "pch.h"

#include <comutil.h>

#include <cstdio>

class IBase1
{
public:
	virtual int IBase1Method1(int par) = 0;
	virtual int IBase1Method2(int par) = 0;
	virtual int IBase1Method3(int par) = 0;
};

class IBase2 : public IBase1
{
public:
	virtual int IBase2Method1(int par) = 0;
	virtual int IBase2Method2(int par) = 0;
};

class IBase3 : public IBase1
{
public:
	virtual int IBase3Method1(int par) = 0;
	virtual int IBase3Method2(int par) = 0;
};

class IBase4
{
public:
	virtual int IBase4Method1(int par) = 0;
	virtual int IBase4Method2(int par) = 0;
};

class IBase5
{
public:
	virtual int IBase5Method1(int par) = 0;
	virtual int IBase5Method2(int par) = 0;
};

class VTable : public IBase2, public IBase3, public IBase4
{
protected:
	int m_value1;

	// To check if the class is destroyed correctly
	// (we check for the memory leak of the BSTR)
	_bstr_t m_bstr1;

public:
	VTable(int value1) : m_value1(value1), m_bstr1(L"")
	{
		printf("C++, VTable::VTable(%d) called\n", value1);
	}

	virtual ~VTable()
	{
		printf("C++, VTable::~VTable\n");
	}

	// Inherited via IBase2
	virtual int IBase1Method1(int par) override
	{
		printf("C++, VTable::IBase1Method1(%d) called\n", par);
		return m_value1 + par + 11;
	}
	
	virtual int IBase1Method2(int par) override
	{
		printf("C++, VTable::IBase1Method2(%d) called\n", par);
		return m_value1 + par + 12;
	}
	
	virtual int IBase1Method3(int par) override
	{
		printf("C++, VTable::IBase1Method3(%d) called\n", par);
		return m_value1 + par + 13;
	}

	virtual int IBase2Method1(int par) override
	{
		printf("C++, VTable::IBase2Method1(%d) called\n", par);
		return m_value1 + par + 21;
	}
	
	virtual int IBase2Method2(int par) override
	{
		printf("C++, VTable::IBase2Method2(%d) called\n", par);
		return m_value1 + par + 22;
	}

	// Inherited via IBase3
	virtual int IBase3Method1(int par) override
	{
		printf("C++, VTable::IBase3Method1(%d) called\n", par);
		return m_value1 + par + 31;
	}

	virtual int IBase3Method2(int par) override
	{
		printf("C++, VTable::IBase3Method2(%d) called\n", par);
		return m_value1 + par + 32;
	}

	// Inherited via IBase4
	virtual int IBase4Method1(int par) override
	{
		printf("C++, VTable::IBase4Method1(%d) called\n", par);
		return m_value1 + par + 41;
	}
	
	virtual int IBase4Method2(int par) override
	{
		printf("C++, VTable::IBase4Method2(%d) called\n", par);
		return m_value1 + par + 42;
	}
};

class DerivedVTable : public VTable, public IBase5
{
protected:
	int m_value2;

	// To check if the class is destroyed correctly
	// (we check for the memory leak of the BSTR)
	_bstr_t m_bstr2;

public:
	DerivedVTable(int value1, int value2) : VTable(value1), m_value2(value2), m_bstr2(L"")
	{
		printf("C++, DerivedVTable::DerivedVTable(%d, %d) called\n", value1, value2);
	}

	virtual ~DerivedVTable() override
	{
		printf("C++, DerivedVTable::~DerivedVTablecalled\n");
	}

	// Inherited via IBase2
	virtual int IBase1Method1(int par) override
	{
		printf("C++, DerivedVTable::IBase1Method1(%d) called\n", par);
		return m_value1 + m_value2 + par + 11;
	}

	virtual int IBase1Method2(int par) override
	{
		printf("C++, DerivedVTable::IBase1Method2(%d) called\n", par);
		return m_value1 + m_value2 + par + 12;
	}

	// Inherited via IBase5
	virtual int IBase5Method1(int par) override
	{
		printf("C++, DerivedVTable::IBase5Method1(%d) called\n", par);
		return m_value1 + m_value2 + par + 51;
	}

	virtual int IBase5Method2(int par) override
	{
		printf("C++, DerivedVTable::IBase5Method2(%d) called\n", par);
		return m_value1 + m_value2 + par + 52;
	}
};

extern "C"
{
	__declspec(dllexport) VTable* __stdcall NewVTable(int value1)
	{
		VTable* cl = new VTable(value1);
		return cl;
	}

	__declspec(dllexport) DerivedVTable* __stdcall NewDerivedVTable(int value1, int value2)
	{
		DerivedVTable* cl = new DerivedVTable(value1, value2);
		return cl;
	}

	__declspec(dllexport) void __stdcall DeleteVTable(VTable* vt)
	{
		delete vt;
	}

	// Doing the casts C#-side is nearly impossible... But C++-side it is as easy as writing static_cast<...> :-)
	__declspec(dllexport) IBase1* __stdcall VTablePtrToIBase1Ptr(VTable* vt)
	{
		// casting to IBase1* is ambiguous (through IBase2* or through IBase3*?)
		return static_cast<IBase2*>(vt);
	}

	__declspec(dllexport) IBase2* __stdcall VTablePtrToIBase2Ptr(VTable* vt)
	{
		return vt;
	}

	__declspec(dllexport) IBase3* __stdcall VTablePtrToIBase3Ptr(VTable* vt)
	{
		return vt;
	}

	__declspec(dllexport) IBase4* __stdcall VTablePtrToIBase4Ptr(VTable* vt)
	{
		return vt;
	}

	__declspec(dllexport) VTable* __stdcall DerivedVTablePtrToVTablePtr(DerivedVTable* vt)
	{
		return vt;
	}

	__declspec(dllexport) IBase5* __stdcall DerivedVTablePtrToIBase5Ptr(DerivedVTable* vt)
	{
		return vt;
	}
}