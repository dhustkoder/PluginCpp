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


#if defined(__linux__) || defined(__APPLE__)
#include <dlfcn.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

#include <iostream>
#include "XPlugin.h"


int main(int argc, char** argv)
{
	using LoadXPlugin = XPlugin* (*)(void);
	using FreeXPlugin = void(*)(const XPlugin*);


	if( argc < 2 )
	{
		std::cout << "give it the path for the XPlugin to load" << std::endl;
		return 0;
	}

	const char* const pluginPath = argv[1];

#if defined(__linux__) || defined(__APPLE__)

	void* hplugin = dlopen(pluginPath, RTLD_LAZY);

	if(!hplugin)
	{
		std::cerr << "Could not load plugin " << pluginPath << std::endl;
		std::cerr << dlerror() <<  std::endl;
		return EXIT_FAILURE; 
	}

	LoadXPlugin get_impl = reinterpret_cast<LoadXPlugin>( dlsym(hplugin, "get_impl") );
	FreeXPlugin free_impl = reinterpret_cast<FreeXPlugin>( dlsym(hplugin, "free_impl") );

	if( !get_impl || !free_impl )
	{
		const char* error = dlerror();
		std::cerr << "Failed to load get_impl/free_impl functions from " << pluginPath << std::endl;
		std::cerr << error << std::endl;
		dlclose(hplugin);
		return EXIT_FAILURE;
	}

#elif defined(_WIN32)

	HMODULE hplugin = LoadLibrary(pluginPath);
	
	if(!hplugin)
	{
		const int errorCode = GetLastError();
		std::cerr << "Could not load " << pluginPath << std::endl;
		std::cerr << "Error Code: " << errorCode << std::endl;
		return EXIT_FAILURE;
	}


	LoadXPlugin get_impl = reinterpret_cast<LoadXPlugin>( GetProcAddress(hplugin, "get_impl") );
	FreeXPlugin free_impl = reinterpret_cast<FreeXPlugin>( GetProcAddress(hplugin, "free_impl") );

	if (!get_impl || !free_impl)
	{
		const int errorCode = GetLastError();
		std::cerr << "failed to get get_impl/free_impl functions from dll " << pluginPath << std::endl;
		std::cerr << "Error Code: " << errorCode << std::endl;
		FreeLibrary(hplugin);
		return EXIT_FAILURE;
	}

#endif

	// finally use the xplugin

	XPlugin* xplugin = get_impl();
	
	if(xplugin)
	{	
		std::cout << "- Plugin Info -" << std::endl;
		std::cout << "Name: " << xplugin->GetName() << std::endl;
		std::cout << "Version: " << xplugin->GetVersion() << std::endl;
		free_impl(xplugin);
	}
	else
	{
		std::cerr << "get_impl returned nullptr" << std::endl;
	}


#if defined(__linux__) || defined(__APPLE__)
	dlclose(hplugin);
#elif defined(_WIN32)
	FreeLibrary(hplugin);
#endif


	return EXIT_SUCCESS;
}











