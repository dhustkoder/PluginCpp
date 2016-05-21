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





extern "C" XPlugin* get_impl()
{
	return new Odin();
}

extern "C" void free_impl(const XPlugin* plugin)
{
	delete plugin;
}


