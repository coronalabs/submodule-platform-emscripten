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

#pragma once

#include "Corona/CoronaLua.h"
#include "Rtt_EmscriptenDisplayObject.h"
#include "Display/Rtt_TextObject.h"

// ----------------------------------------------------------------------------

namespace Rtt
{

// ----------------------------------------------------------------------------

class EmscriptenTextBoxObject : public EmscriptenDisplayObject
{
	public:
		typedef EmscriptenTextBoxObject Self;
		typedef EmscriptenDisplayObject Super;

		struct listener : public ref_counted
		{
			listener(const ResourceHandle<lua_State> & handle, const char* eventName, int listenerIndex);
			virtual ~listener();
			void dispatch(int elementID, int eventID, LuaProxy* proxy);

			CoronaLuaRef fLuaReference;
			tu_string fEventName;
			ResourceHandle<lua_State> fLuaState;
		};

		EmscriptenTextBoxObject(const Rect& bounds, bool isSingleLine);
		virtual ~EmscriptenTextBoxObject();

		virtual bool Initialize();
		virtual const LuaProxyVTable& ProxyVTable() const;
		virtual int ValueForKey(lua_State *L, const char key[]) const;
		virtual bool SetValueForKey(lua_State *L, const char key[], int valueIndex);
		static int addEventListener(lua_State *L);

		void dispatch(int eventID);

	protected:
		static int SetTextColor(lua_State *L);
		static int SetReturnKey(lua_State *L);

	private:
		/// Set TRUE if this is a single line text field. Set FALSE for a multiline text box.
		/// This value is not expected to change after initialization.
		bool fIsSingleLine;
		smart_ptr<listener> fListener;
};

// ----------------------------------------------------------------------------

} // namespace Rtt

// ----------------------------------------------------------------------------
