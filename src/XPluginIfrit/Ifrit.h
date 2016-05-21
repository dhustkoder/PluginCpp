#ifndef _XPLUGIN_ODIN_H_
#define _XPLUGIN_ODIN_H_
#include "../XPlugin.h"


class Ifrit : public XPlugin
{
public:
	Ifrit();
	~Ifrit();
	const char* GetName() const override;
	void PrintVersion() const override;

};





#endif
