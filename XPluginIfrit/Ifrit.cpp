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
	return "XPLUGIN - Ifrit";
}

void Ifrit::PrintVersion() const
{
	std::cout << "XPLUGIN - Ifrit VER 0.0.12" << std::endl;
}




extern "C" XPlugin* get_impl()
{
	return new Ifrit();
}

extern "C" void free_impl(const XPlugin* plugin)
{
	delete plugin;
}


