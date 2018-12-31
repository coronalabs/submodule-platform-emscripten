// ----------------------------------------------------------------------------
// 
// Rtt_EmscriptenPlatformMac.mm
// Copyright (c) 2013 Corona Labs Inc. All rights reserved.
// 
// Reviewers:
//
// ----------------------------------------------------------------------------

#include "Core/Rtt_Build.h"

#include "Rtt_EmscriptenPlatformMac.h"

#import <Foundation/Foundation.h>

// ----------------------------------------------------------------------------

namespace Rtt
{

// ----------------------------------------------------------------------------

static const char*
GetDirectory( NSSearchPathDirectory directory )
{
	NSArray *paths = NSSearchPathForDirectoriesInDomains( directory, NSUserDomainMask, YES );
	NSString *str = [paths objectAtIndex:0];
	return [str UTF8String];
}

static const char*
CachesParentDir()
{
	return GetDirectory( NSCachesDirectory );
}

// ----------------------------------------------------------------------------

EmscriptenPlatformMac::EmscriptenPlatformMac( int width, int height )
:	Super(
		width, height,
		[[[NSBundle mainBundle] resourcePath] UTF8String],
		GetDirectory( NSDocumentDirectory ),
		[NSTemporaryDirectory() UTF8String],
		GetDirectory( NSCachesDirectory ),
		GetDirectory( NSCachesDirectory ) )
{
}

EmscriptenPlatformMac::~EmscriptenPlatformMac()
{
}

// ----------------------------------------------------------------------------

} // namespace Rtt

// ----------------------------------------------------------------------------
