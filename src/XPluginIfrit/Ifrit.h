#ifndef _XPLUGIN_ODIN_H_
#define _XPLUGIN_ODIN_H_
#include "../XPlugin.h"


class Ifrit : public XPlugin
{
public:
	Ifrit();
	~Ifrit();
	const char* GetName() const override;
	const char* GetVersion() const override;

private:
	static constexpr const char* const _pluginName = "XPlugin - Ifrit";
	static constexpr const char* const _pluginVersion = "0.1.5.12";
};





#endif
