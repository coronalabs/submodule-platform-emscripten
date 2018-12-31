//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Corona Labs Inc.
// Contact: support@coronalabs.com
//
// This file is part of the Corona game engine.
//
// Commercial License Usage
// Licensees holding valid commercial Corona licenses may use this file in
// accordance with the commercial license agreement between you and 
// Corona Labs Inc. For licensing terms and conditions please contact
// support@coronalabs.com or visit https://coronalabs.com/com-license
//
// GNU General Public License Usage
// Alternatively, this file may be used under the terms of the GNU General
// Public license version 3. The license is as published by the Free Software
// Foundation and appearing in the file LICENSE.GPL3 included in the packaging
// of this file. Please review the following information to ensure the GNU 
// General Public License requirements will
// be met: https://www.gnu.org/licenses/gpl-3.0.html
//
// For overview and more information on licensing please refer to README.md
//
//////////////////////////////////////////////////////////////////////////////

#include "Rtt_EmscriptenCPluginLoader.h"
#include "Corona/CoronaLua.h"
#include "Core/Rtt_String.h"

#if defined(EMSCRIPTEN)

#include "emscripten/emscripten.h"

int Rtt::EmscriptenCPluginLoader::LualoadCInvoker(lua_State *L)
{
	const char* packageName = luaL_checkstring(L, 1);
	packageName = luaL_gsub( L, packageName, ".", "_" );
	lua_remove(L, 1);

	return EM_ASM_INT({
		return Module.ccall('luaopen_'+UTF8ToString($0), 'number', ['number'],[$1])
	}, packageName, L );
}

int Rtt::EmscriptenCPluginLoader::Loader(lua_State *L)
{
	// Fetch the package name that the Lua require() function is trying to load.
	const char* packageName = luaL_checkstring(L, 1);
	packageName = luaL_gsub( L, packageName, ".", "_" );
	lua_remove(L, 1);

	bool hasSymbol = EM_ASM_INT({
		return Module.hasOwnProperty('_luaopen_'+UTF8ToString($0));
	}, packageName);

	if(hasSymbol)
	{
		lua_pushcfunction(L, &EmscriptenCPluginLoader::LualoadCInvoker);
		return 1;
	}
	lua_pushnil(L);
	return 1;
}

#else
int Rtt::EmscriptenCPluginLoader::Loader(lua_State *L) { return 0; }
int Rtt::EmscriptenCPluginLoader::LualoadCInvoker(lua_State *L) { return 0; }
#endif
