#ifndef _XPLUGIN_ODIN_H_
#define _XPLUGIN_ODIN_H_
#include "../XPlugin.h"

class Odin : public XPlugin
{
public:
	Odin();
	~Odin();
	const char* GetName() const override;
	const char* GetVersion() const override;
private:
	static constexpr const char* const _pluginName = "XPlugin - Odin. by whoever";
	static constexpr const char* const _pluginVersion = "Odin 3.56";
};






#endif
