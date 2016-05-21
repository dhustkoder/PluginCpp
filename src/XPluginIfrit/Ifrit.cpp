/*

PluginCpp - load dynamic libraries example
Copyright (C) 2016  Rafael Moura

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/gpl-3.0.html.

*/

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

