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
#include "Rtt_EmscriptenEventSound.h"
#include "Rtt_LuaContext.h"

// ----------------------------------------------------------------------------

namespace Rtt
{

// ----------------------------------------------------------------------------

#pragma region Constructors/Destructors
EmscriptenEventSound::EmscriptenEventSound(const ResourceHandle<lua_State> & handle, Rtt_Allocator & allocator)
:	PlatformEventSound(handle)
{
}

EmscriptenEventSound::~EmscriptenEventSound()
{
}

#pragma endregion


#pragma region Public Member Functions
bool EmscriptenEventSound::Load(const char * filePath)
{
	return false;
}

void EmscriptenEventSound::Play()
{
}

void EmscriptenEventSound::ReleaseOnComplete()
{
}

void EmscriptenEventSound::Stop()
{
}

void EmscriptenEventSound::Pause()
{
}

void EmscriptenEventSound::Resume()
{
}

void EmscriptenEventSound::SetVolume(Rtt_Real volume)
{
}

Rtt_Real EmscriptenEventSound::GetVolume() const
{
	return 1.0f;
}

#pragma endregion

// ----------------------------------------------------------------------------

} // namespace Rtt

// ----------------------------------------------------------------------------
