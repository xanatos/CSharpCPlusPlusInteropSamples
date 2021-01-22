// Utils.c : 

#include "pch.h"

#include <stdlib.h>

__declspec(dllexport) void __stdcall FreeMalloc(void* ptr)
{
	free(ptr);
}
