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
