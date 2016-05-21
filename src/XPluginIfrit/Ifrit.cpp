#include <iostream>
#include "Ifrit.h"

Ifrit::Ifrit()
{
	std::cout << "Creating Ifrit XPlugin." << std::endl;
	std::cout << "The XPlugin of Fire!" << std::endl;
}

Ifrit::~Ifrit()
{
	std::cout << "Destroying Ifrit..." << std::endl;
}

const char* Ifrit::GetName() const
{
	return _pluginName;
}

const char* Ifrit::GetVersion() const
{
	return _pluginVersion;
}



#if defined(__linux__) || defined(__APPLE__)

extern "C" XPlugin* get_impl()
{
	return new(std::nothrow) Ifrit();
}

extern "C" void free_impl(const XPlugin* plugin)
{
	delete plugin;
}

#elif defined(_WIN32)

extern "C" __declspec(dllexport) XPlugin* get_impl()
{
	return new(std::nothrow) Ifrit();
}

extern "C" __declspec(dllexport) void free_impl(const XPlugin* plugin)
{
	delete plugin;
}


#endif

