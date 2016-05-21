#ifndef _XPLUGIN_ODIN_H_
#define _XPLUGIN_ODIN_H_
#include "../XPlugin.h"

class Odin : public XPlugin
{
public:
	Odin();
	~Odin();
	const char* GetName() const override;
	void PrintVersion() const override;
};






#endif
