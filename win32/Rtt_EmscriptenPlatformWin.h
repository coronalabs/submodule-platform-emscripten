// ----------------------------------------------------------------------------
// 
// Rtt_EmscriptenPlatform.h
// Copyright (c) 2013 Corona Labs Inc. All rights reserved.
// 
// Reviewers:
//
// ----------------------------------------------------------------------------

#pragma once

#include <SDL2/SDL.h>
#include "../Rtt_EmscriptenPlatform.h"



namespace Rtt
{

	// ----------------------------------------------------------------------------

	class EmscriptenPlatformWin : public EmscriptenPlatform
	{
		Rtt_CLASS_NO_COPIES(EmscriptenPlatformWin)

	public:
		typedef EmscriptenPlatform Super;
		typedef EmscriptenPlatformWin Self;

		EmscriptenPlatformWin(const char *resourceDir, const char *documentsDir, const char *temporaryDir,
			const char *cachesDir, const char *systemCachesDir);
		virtual ~EmscriptenPlatformWin();

		virtual PlatformFont* CreateFont(PlatformFont::SystemFont fontType, Rtt_Real size) const override;
		virtual PlatformFont* CreateFont(const char *fontName, Rtt_Real size) const override;
	};

	// ----------------------------------------------------------------------------

} // namespace Rtt

// ----------------------------------------------------------------------------
