//-*- c++ -*-------------------------------------------------------------------
#ifndef PHIDGETUTILITIES_HPP
#define PHIDGETUTILITIES_HPP

#ifdef __GNUC__
#pragma interface
#endif
//
// Class: PhidgetUtilities
// Author: Lee Redden
// Email: leeredden@gmail.com
// Created: 31 Jan 2015
// Modifications:
// 20150131 LeeR Initial Version
//
//-----------------------------------------------------------------------------

/**
 * Low level functions called by ServoDriver for Phidget Event Handling
 */

#include <stdio.h>
#include <phidget21.h>

namespace PhidgetUtilities {

int CCONV AttachHandler(CPhidgetHandle ADVSERVO, void *userptr);
int CCONV DetachHandler(CPhidgetHandle ADVSERVO, void *userptr);
int CCONV ErrorHandler(CPhidgetHandle ADVSERVO, void *userptr, int ErrorCode, const char *Description);
int CCONV PositionChangeHandler(CPhidgetAdvancedServoHandle ADVSERVO, void *usrptr, int Index, double Value);

//Display the properties of the attached phidget to the screen.  We will be displaying the name, serial number and version of the attached device.
int display_properties(CPhidgetAdvancedServoHandle phid);

}
#endif // PHIDGETUTILITIES_HPP
