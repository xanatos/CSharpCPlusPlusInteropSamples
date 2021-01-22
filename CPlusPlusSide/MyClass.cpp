// SafeArray.cpp : 

#include "pch.h"

#include <comutil.h>

#include <cstdio>

class MyClass
{
protected:
	int m_value;

	// To check if the class is destroyed correctly
	// (we check for the memory leak of the BSTR)
	_bstr_t m_bstr1;

public:
	MyClass(int value) : m_value(value), m_bstr1(L"")
	{
		printf("C++, MyClass::MyClass(%d) called\n", value);
	}

	virtual ~MyClass()
	{
		printf("C++, MyClass::~MyClass called\n");
	}

	// By default it would be __cdecl, we set it to __stdcall
	__declspec(dllexport) static MyClass* __stdcall NewMyClass(int value)
	{
		printf("C++, MyClass::NewMyClass(%d) called\n", value);
		return new MyClass(value);
	}

	// Uses __thiscall
	__declspec(dllexport) virtual int GetAndIncrement(int inc)
	{
		printf("C++, MyClass::GetAndIncrement(%d) called\n", inc);
		int value = m_value;
		m_value += inc;
		return value;
	}
};

class DerivedMyClass : public MyClass
{
protected:
	// To check if the class is destroyed correctly
	// (we check for the memory leak of the BSTR)
	_bstr_t m_bstr2;

public:
	DerivedMyClass(int value) : MyClass(value), m_bstr2(L"")
	{
		printf("C++, DerivedMyClass::DerivedMyClass(%d) called\n", value);
	}

	virtual ~DerivedMyClass() override
	{
		printf("C++, DerivedMyClass::~DerivedMyClass called\n");
	}

	// Uses __thiscall
	__declspec(dllexport) virtual int GetAndIncrement(int inc) override
	{
		printf("C++, DerivedMyClass::GetAndIncrement(%d) called\n", inc);
		int value = m_value;
		m_value += inc * 2;
		return value;
	}
};

extern "C"
{
	__declspec(dllexport) MyClass* __stdcall NewMyClass(int value)
	{
		MyClass* cl = new MyClass(value);
		return cl;
	}

	__declspec(dllexport) DerivedMyClass* __stdcall NewDerivedMyClass(int value)
	{
		DerivedMyClass* cl = new DerivedMyClass(value);
		return cl;
	}

	__declspec(dllexport) void __stdcall DeleteMyClass(MyClass* cl)
	{
		delete cl;
	}
}