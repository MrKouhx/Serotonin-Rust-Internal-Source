#include "Core.hpp"
#include "CRT/crt.hpp"
#include "Il2Cpp/CIl2Cpp.hpp"
#include "SDK/AssemblyCSharp/AssemblyCSharp.hpp"
#include "Hooking/Hooks.hpp"
#include "Net/net.h"

template<typename t>
t read(uintptr_t addr) {
	if (addr < 0xffffff)
		return t();
	if (addr > 0x7fffffff0000)
		return t();

	return *reinterpret_cast<t*>(addr);
}
#include <windows.h>
#include <urlmon.h>
#include <iostream>
#pragma comment(lib, "urlmon.lib")


#define safe_read(Addr, Type) read<Type>((DWORD64)Addr)
void Core::Init()
{
	_cinit();
#ifndef DEBUG_MODE
	LI_FN(Sleep)(30000);
#endif

	LOG(XS("[DEBUG] DLL Initialized!"));

	m_game_assembly = GetImage(XS(L"GameAssembly.dll"));
	if (!CIl2Cpp::CreateIL2CPP())
		return;



	Hooks().Instance()->BeginHooks();
}