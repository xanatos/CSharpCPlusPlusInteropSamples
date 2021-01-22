// SafeArray.cpp : 

#include "pch.h"

#include <comutil.h>
#include <OleAuto.h>

#pragma warning(push, 3)
#import "mscorlib.tlb" auto_rename
#pragma warning(pop)

extern "C"
{
	__declspec(dllexport) LPSAFEARRAY __stdcall ReturnSafeArrayStrings()
	{
		ULONG numElements = 3;
		LONG index = 0;
		LPSAFEARRAY psa = SafeArrayCreateVector(VT_BSTR, 0, numElements);

#pragma warning(push)
#pragma warning(disable: 4566)
		_bstr_t bstr1("Foo àèéìòù āēīōū"); // We can use char* strings
#pragma warning(pop)

		_bstr_t bstr2(L"Bar àèéìòù āēīōū");
		_bstr_t bstr3(L"Baz àèéìòù āēīōū");

		// Notet that SafeArrayPutElement copies the bstr.

		SafeArrayPutElement(psa, &index, bstr1.GetBSTR());
		index++;

		SafeArrayPutElement(psa, &index, bstr2.GetBSTR());
		index++;

		SafeArrayPutElement(psa, &index, bstr3.GetBSTR());
		index++;

		return psa;
	}

	__declspec(dllexport) LPSAFEARRAY __stdcall ReturnSafeArrayGuids()
	{
		// in the obj folder there should be a mscorlib.tlh with all the objects
		// We are getting the IRecordInfo of .NET 4.0 here (2.4 version, don't ask
		// me why)
		IRecordInfo* pri = nullptr;
		GetRecordInfoFromGuids(__uuidof(mscorlib::__mscorlib), 2, 4, 0, __uuidof(mscorlib::Guid), &pri);

		ULONG numElements = 3;
		LONG index = 0;
		LPSAFEARRAY psa = SafeArrayCreateVectorEx(VT_RECORD, 0, numElements, pri);

		mscorlib::Guid guid1 = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B };

		SafeArrayPutElement(psa, &index, &guid1);
		index++;

		mscorlib::Guid guid2 = { 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B };

		SafeArrayPutElement(psa, &index, &guid2);
		index++;

		mscorlib::Guid guid3 = { 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B };

		SafeArrayPutElement(psa, &index, &guid3);
		index++;

		return psa;
	}
}