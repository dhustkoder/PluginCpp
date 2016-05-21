class XPlugin;

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

	void* handle = dlopen(pluginName, RTLD_LAZY);

	if(!handle)
	{
		std::cerr << "Could not load plugin " << pluginName << std::endl;
		std::cerr << dlerror() <<  std::endl;
		return EXIT_FAILURE; 
	}

	dlerror();

	LoadXPlugin get_impl = (LoadXPlugin) dlsym(handle, "get_impl");
	FreeXPlugin free_impl = (FreeXPlugin) dlsym(handle, "free_impl");

	const char* error = dlerror();	
	if( error != nullptr)
	{
		std::cerr << "Failed to load get_impl/free_impl functions from " << pluginName << std::endl;
		std::cerr << error << std::endl;
		return EXIT_FAILURE;
	}

#elif defined(_WIN32)

	HMODULE hplugin = LoadLibrary(pluginPath);
	
	if(!hplugin)
	{
		const int errorCode = GetLastError();
		std::cerr << "Could not load " << pluginPath << std::endl;
		std::cerr << "Error Code: " << errorCode << std::endl;
		FreeLibrary(hplugin);
		return EXIT_FAILURE;
	}


	LoadXPlugin get_impl = (LoadXPlugin) GetProcAddress(hplugin, "get_impl");
	FreeXPlugin free_impl = (FreeXPlugin) GetProcAddress(hplugin, "free_impl");

	if (!get_impl || !free_impl)
	{
		const int errorCode = GetLastError();
		std::cerr << "Could not get impl functions from dll " << pluginPath << std::endl;
		std::cerr << "Error Code: " << errorCode << std::endl;
		FreeLibrary(hplugin);
		return EXIT_FAILURE;
	}

#endif



	XPlugin* xplugin = get_impl();
	
	if (!xplugin)
	{
		std::cerr << "XPlugin " << pluginPath << " get_impl returned nullptr" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Loaded XPlugin: " << xplugin->GetName() << std::endl;
	xplugin->PrintVersion();

	free_impl(xplugin);

	FreeLibrary(hplugin);

	return EXIT_SUCCESS;

}











