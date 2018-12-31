// ----------------------------------------------------------------------------
// 
// Rtt_EmscriptenPlatform.h
// Copyright (c) 2013 Corona Labs Inc. All rights reserved.
// 
// Reviewers:
//
// ----------------------------------------------------------------------------

#pragma once

#include "Rtt_EmscriptenPlatform.h"

// ----------------------------------------------------------------------------

namespace Rtt
{

// ----------------------------------------------------------------------------

class EmscriptenPlatformMac : public EmscriptenPlatform
{
	Rtt_CLASS_NO_COPIES( EmscriptenPlatformMac )

	public:
		typedef EmscriptenPlatform Super;
		typedef EmscriptenPlatformMac Self;

	public:
		EmscriptenPlatformMac( int width, int height );
		virtual ~EmscriptenPlatformMac();
};

// ----------------------------------------------------------------------------

} // namespace Rtt

// ----------------------------------------------------------------------------
