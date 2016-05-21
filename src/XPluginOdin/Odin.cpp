#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include "Odin.h"

Odin::Odin()
{
	std::cout << "Creating the XPlugin of Odin!" << std::endl;
}

Odin::~Odin()
{
	std::cout << "Destroying XPlugin of Odin!" << std::endl;
}

const char* Odin::GetName() const
{
	return "XPLUGIN - ODIN";
}
void Odin::PrintVersion() const
{
	std::cout << "XPLUGIN - ODIN VER 0.1" << std::endl;
}




#if defined(__linux__) || defined(__APPLE__)

extern "C" XPlugin* get_impl()
{
	return new(std::nothrow) Odin();
}

extern "C" void free_impl(const XPlugin* plugin)
{
	delete plugin;
}



#elif defined(_WIN32)


extern "C" __declspec(dllexport) XPlugin* get_impl()
{
	return new(std::nothrow) Odin();
}

extern "C" __declspec(dllexport) void free_impl(const XPlugin* plugin)
{
	delete plugin;
}


#endif
