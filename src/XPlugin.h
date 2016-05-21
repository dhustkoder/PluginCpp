#ifndef _XPLUGIN_H_
#define _XPLUGIN_H_

class XPlugin
{
public:
	virtual ~XPlugin() = default;
	virtual const char* GetName() const = 0;
	virtual const char* GetVersion() const = 0;

};






#endif
