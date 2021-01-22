// ReturnArray.c : 

#include "pch.h"

#include <combaseapi.h>

__declspec(dllexport) double* __stdcall ReturnArrayDouble(int* pcount)
{
	size_t count = 5;

	double* pdouble = (double*)CoTaskMemAlloc(count * sizeof(double));

	if (!pdouble)
	{
		*pcount = 0;
		return NULL;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		pdouble[i] = ((int)i + 1.0) * 2.0;
	}

	return pdouble;
}

__declspec(dllexport) void __stdcall PassOutArrayDouble(double** ppdouble, int* pcount)
{
	size_t count = 5;

	*ppdouble = (double*)CoTaskMemAlloc(count * sizeof(double));

	if (!*ppdouble)
	{
		*pcount = 0;
		return;
	}

	*pcount = (int)count;

	for (size_t i = 0; i < count; i++)
	{
		(*ppdouble)[i] = ((int)i + 1.0) * 2.0;
	}
}

__declspec(dllexport) void __stdcall PassOutThroughDelegateArrayDouble(void(__stdcall add)(double dbl))
{
	size_t count = 5;

	for (size_t i = 0; i < count; i++)
	{
		add(((int)i + 1.0) * 2.0);
	}
}

