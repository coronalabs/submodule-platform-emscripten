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
#include "Rtt_EmscriptenDevice.h"

// ----------------------------------------------------------------------------

namespace Rtt
{

// ----------------------------------------------------------------------------

#pragma region Constructors/Destructors
EmscriptenDevice::EmscriptenDevice( Rtt_Allocator& allocator )
:	fAllocator( allocator ),
	fInputDeviceManager( &allocator ),
	fOrientation( DeviceOrientation::kUnknown )
{
}

EmscriptenDevice::~EmscriptenDevice()
{
}

#pragma endregion


#pragma region Public Member Functions
void EmscriptenDevice::SetOrientation( DeviceOrientation::Type orientation )
{
	fOrientation = orientation;
}

void EmscriptenDevice::Vibrate() const
{
}

void EmscriptenDevice::SetAccelerometerInterval( U32 frequency ) const
{
}

void EmscriptenDevice::SetGyroscopeInterval( U32 frequency ) const
{
}

bool EmscriptenDevice::HasEventSource( EventType type ) const
{
	bool hasEventSource = false;
	
	switch (type)
	{
		case MPlatformDevice::kAccelerometerEvent:
			break;
		case MPlatformDevice::kGyroscopeEvent:
			break;
		case MPlatformDevice::kOrientationEvent:
		case MPlatformDevice::kLocationEvent:
		case MPlatformDevice::kHeadingEvent:
		case MPlatformDevice::kMultitouchEvent:
		case MPlatformDevice::kKeyEvent:
			hasEventSource = true;
			break;
		default:
			Rtt_ASSERT_NOT_REACHED();
			break;
	}
	return hasEventSource;
}

void EmscriptenDevice::BeginNotifications( EventType type ) const
{
	fTracker.BeginNotifications( type );

	switch( type )
	{
		case MPlatformDevice::kOrientationEvent:
		case MPlatformDevice::kLocationEvent:
		case MPlatformDevice::kAccelerometerEvent:
		case MPlatformDevice::kGyroscopeEvent:
		case MPlatformDevice::kHeadingEvent:
		case MPlatformDevice::kMultitouchEvent:
			break;
		default:
			Rtt_ASSERT_NOT_REACHED();
			break;
	}
}

void EmscriptenDevice::EndNotifications( EventType type ) const
{
	fTracker.EndNotifications( type );

	switch( type )
	{
		case MPlatformDevice::kOrientationEvent:
		case MPlatformDevice::kLocationEvent:
		case MPlatformDevice::kAccelerometerEvent:
		case MPlatformDevice::kGyroscopeEvent:
		case MPlatformDevice::kHeadingEvent:
		case MPlatformDevice::kMultitouchEvent:
			break;
		default:
			Rtt_ASSERT_NOT_REACHED();
			break;
	}
}

bool EmscriptenDevice::DoesNotify( EventType type ) const
{
	return fTracker.DoesNotify( type );
}

const char* EmscriptenDevice::GetModel() const
{
#ifdef EMSCRIPTEN
	return "emscripten";
#else
	return "win32";
#endif
}

const char* EmscriptenDevice::GetName() const
{
	return "";
}

const char* EmscriptenDevice::GetUniqueIdentifier( IdentifierType t ) const
{
	const char *result = "";

	switch ( t )
	{
		case MPlatformDevice::kDeviceIdentifier:
			break;
		case MPlatformDevice::kHardwareIdentifier:
			break;
		case MPlatformDevice::kOSIdentifier:
			break;
		case MPlatformDevice::kUdidIdentifier:
			break;
		default:
			break;
	}
	return result;
}

MPlatformDevice::EnvironmentType EmscriptenDevice::GetEnvironment() const
{
	return kBrowserEnvironment;
}

const char* EmscriptenDevice::GetPlatformName() const
{
	return "HTML5";
}
	
const char* EmscriptenDevice::GetPlatformVersion() const
{
	return "1.0";
}

const char* EmscriptenDevice::GetProductName() const
{
	return "";
}

const char* EmscriptenDevice::GetArchitectureInfo() const
{
	return "javascript";
}

PlatformInputDeviceManager& EmscriptenDevice::GetInputDeviceManager()
{
	return fInputDeviceManager;
}

void EmscriptenDevice::SetLocationAccuracy( Real meters ) const
{
}

void EmscriptenDevice::SetLocationThreshold( Real meters ) const
{
}

DeviceOrientation::Type EmscriptenDevice::GetOrientation() const
{
	return fOrientation;
}

	const char* EmscriptenDevice::GetPlatform() const
{
	return "html5";
}
	
	const char* EmscriptenDevice::GetManufacturer() const
{
	return "Corona Labs";
}
	
#pragma endregion

// ----------------------------------------------------------------------------

} // namespace Rtt

// ----------------------------------------------------------------------------
