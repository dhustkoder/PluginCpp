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

	LoadXPlugin get_impl = (LoadXPlugin) dlsym(hplugin, "get_impl");
	FreeXPlugin free_impl = (FreeXPlugin) dlsym(hplugin, "free_impl");

	const char* error = dlerror();	

	if( error )
	{
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











