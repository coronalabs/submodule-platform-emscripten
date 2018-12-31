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

#include <SDL2/SDL.h>
#include "Core/Rtt_Build.h"
#include "Rtt_EmscriptenScreenSurface.h"

// ----------------------------------------------------------------------------

namespace Rtt
{

#pragma region EmscriptenScreenSurface Class

#pragma region Constructors/Destructors
EmscriptenScreenSurface::EmscriptenScreenSurface()
	: fWindow(NULL)
	, fOrientation(DeviceOrientation::kUpright)
{
}

EmscriptenScreenSurface::~EmscriptenScreenSurface()
{
}

#pragma endregion


#pragma region Public Member Functions
void EmscriptenScreenSurface::SetCurrent() const
{
}

void EmscriptenScreenSurface::Flush() const
{
	SDL_GL_SwapWindow(fWindow);
}

S32 EmscriptenScreenSurface::Width() const
{
	if (fWindow)
	{
		int w, h;
		SDL_GetWindowSize(fWindow, &w, &h);
		return w;
	}
	Rtt_ASSERT_NOT_REACHED();
	return 0;
}

S32 EmscriptenScreenSurface::Height() const
{
	if (fWindow)
	{
		int w, h;
		SDL_GetWindowSize(fWindow, &w, &h);
		return h;
	}
	Rtt_ASSERT_NOT_REACHED();
	return 0;
}

S32 EmscriptenScreenSurface::DeviceWidth() const
{
	// Return the surface's pixel width relative to a portrait orientation.
	if (fWindow)
	{
		int w, h;
		SDL_GetWindowSize(fWindow, &w, &h);
		return (fOrientation == DeviceOrientation::kUpright  || fOrientation == DeviceOrientation::kUpsideDown) ? w : h;
	}
	Rtt_ASSERT_NOT_REACHED();
	return 0;	
}

S32 EmscriptenScreenSurface::DeviceHeight() const
{
	// Return the surface's pixel height relative to a portrait orientation.
	if (fWindow)
	{
		int w, h;
		SDL_GetWindowSize(fWindow, &w, &h);
		return (fOrientation == DeviceOrientation::kUpright  || fOrientation == DeviceOrientation::kUpsideDown) ? h : w;
	}
	Rtt_ASSERT_NOT_REACHED();
	return 0;	
}

void EmscriptenScreenSurface::getWindowSize(int* w, int* h)
{
	SDL_GetWindowSize(fWindow, w, h);
}

DeviceOrientation::Type EmscriptenScreenSurface::GetOrientation() const
{
	return fOrientation;
}


#pragma endregion

#pragma endregion


#pragma region EmscriptenOffscreenSurface Class

#pragma region Constructors/Destructors
EmscriptenOffscreenSurface::EmscriptenOffscreenSurface(const PlatformSurface& parent)
:	fWidth(parent.Width()),
	fHeight(parent.Height())
{
}

EmscriptenOffscreenSurface::~EmscriptenOffscreenSurface()
{
}

#pragma endregion


#pragma region Public Member Functions
void EmscriptenOffscreenSurface::SetCurrent() const
{
}

void EmscriptenOffscreenSurface::Flush() const
{
}

S32 EmscriptenOffscreenSurface::Width() const
{
	return fWidth;
}

S32 EmscriptenOffscreenSurface::Height() const
{
	return fHeight;
}

#pragma endregion

#pragma endregion

// ----------------------------------------------------------------------------

} // namespace Rtt

// ----------------------------------------------------------------------------
