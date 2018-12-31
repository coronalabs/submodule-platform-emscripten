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

#include "Core/Rtt_Build.h"
#include "Core/Rtt_String.h"
#include "Rtt_EmscriptenStoreProvider.h"
#include "Rtt_LuaContext.h"
#include "Rtt_Runtime.h"

// ----------------------------------------------------------------------------

namespace Rtt
{

// ----------------------------------------------------------------------------

#pragma region Constants
/// Unique name assigned to Microsoft's Windows store.
static const char* kWindowsStoreName = "";
 
#pragma endregion


#pragma region Constructors/Destructors
/// Creates a new object used to provide an appropriate store accessing object for the current platform.
/// @param handle The Lua state wrapper needed to create objects in the runtime and raise event in Lua.
EmscriptenStoreProvider::EmscriptenStoreProvider(const ResourceHandle<lua_State>& handle)
	: PlatformStoreProvider(handle),
	fActiveStore(NULL)
{
	Runtime *runtime = LuaContext::GetRuntime(GetLuaHandle().Dereference());
	if (runtime)
	{
		GetAvailableStores().Append(Rtt_NEW(runtime->Allocator(), String(runtime->Allocator(), kWindowsStoreName)));
	}
}

/// Destructor. Cleans up allocated resources.
EmscriptenStoreProvider::~EmscriptenStoreProvider()
{
	Rtt_DELETE(fActiveStore);
}

#pragma endregion


#pragma region Public Member Functions
/// Assign a store to the provider to be returned by the GetActiveStore() function.
/// @param storeName The unique name of the store to provide access to.
///                  Set to NULL or empty string to have the platform automatically select a default store, if possible.
void EmscriptenStoreProvider::SetActiveStore(const char *storeName)
{
	// Do not allow the store to be changed once one has been activated.
	if (fActiveStore)
	{
		return;
	}

	// Automatically select the Apple store if a name was not provided.
	if (!storeName || (strlen(storeName) < 1))
	{
		storeName = kWindowsStoreName;
	}

	// Delete access to the last store, if assigned.
	Rtt_DELETE(fActiveStore);
	fActiveStore = NULL;

	// Create the specified store accessing object if available on this system/device.
	if (IsStoreAvailable(storeName))
	{
		Runtime *runtime = LuaContext::GetRuntime(GetLuaHandle().Dereference());
		if (runtime)
		{
			fActiveStore = Rtt_NEW(runtime->Allocator(), EmscriptenStore(GetLuaHandle()));
		}
	}
}

/// Gets the store accessing object that was assigned to this provider via the SetActiveStore() function.
/// @return Returns a pointer to a store accessing object.
///         Returns NULL if a store was not assigned to this provider or if a store is not available on this platform.
PlatformStore* EmscriptenStoreProvider::GetActiveStore()
{
	return fActiveStore;
}

/// Gets the unique name of the store this application is targeting.
/// @return Returns the unique name of the targetd store such as "apple", "google", "amazon", etc.
///         Returns NULL if this application is not targeting a store.
const char* EmscriptenStoreProvider::GetTargetedStoreName()
{
	return kWindowsStoreName;
}

#pragma endregion

// ----------------------------------------------------------------------------

} // namespace Rtt

// ----------------------------------------------------------------------------
