#include <dlfcn.h>

#include <iostream>
#include "XPlugin.h"


int main(int argc, char** argv)
{
	using LoadXPlugin = XPlugin* (*)(void);
	using FreeXPlugin = void (*)(XPlugin*);

	if( argc < 2 )
	{
		std::cout << "give it the path for the XPlugin to load" << std::endl;
		return 0;
	}

	const char* const pluginName = argv[1];

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

	XPlugin* xplugin = get_impl();


	std::cout << "Loaded XPlugin: " << xplugin->GetName() << std::endl;
	xplugin->PrintVersion();


	free_impl(xplugin);

#elif WIN32

#endif


	return 0;

}











