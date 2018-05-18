#pragma once

#include <crtdbg.h>
#include <windows.h>

class MemoryLeakDetector
{
public:
	MemoryLeakDetector() 
		{ ::OutputDebugString( (LPCSTR)">>> Memory leak detection enabled <<<\n" ); }
	~MemoryLeakDetector()
		{ if (!_CrtDumpMemoryLeaks()) ::OutputDebugString( (LPCSTR)">>> No memory leak detected <<<\n" ); }
};

MemoryLeakDetector md;
