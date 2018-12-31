// ----------------------------------------------------------------------------
// 
// Rtt_EmscriptenPlatformWin.cpp
// Copyright (c) 2017 Corona Labs Inc. All rights reserved.
// 
// Reviewers:
//
// ----------------------------------------------------------------------------

#include "Core/Rtt_Build.h"
#include "Rtt_EmscriptenPlatformWin.h"
#include "../Rtt_EmscriptenFont.h"

// ----------------------------------------------------------------------------

namespace Rtt
{

EmscriptenPlatformWin::EmscriptenPlatformWin(const char *resourceDir, const char *documentsDir, const char *temporaryDir,	const char *cachesDir, const char *systemCachesDir)
	:	Super(resourceDir, documentsDir, temporaryDir, cachesDir, systemCachesDir)
{
}

EmscriptenPlatformWin::~EmscriptenPlatformWin()
{
}

PlatformFont * EmscriptenPlatformWin::CreateFont( PlatformFont::SystemFont fontType, Rtt_Real size ) const
{
	return Rtt_NEW(fAllocator, EmscriptenFont(*fAllocator, fontType, size));
}

PlatformFont * EmscriptenPlatformWin::CreateFont( const char *fontName, Rtt_Real size ) const
{
	bool isBold = false;
	return Rtt_NEW( fAllocator, EmscriptenFont( *fAllocator, fontName, size, isBold ) );
}

} // namespace Rtt
