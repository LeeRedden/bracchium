#ifndef PHIDGETUTILITIES_HPP
#define PHIDGETUTILITIES_HPP

#include <stdio.h>
#include <phidget21.h>

namespace HAND{
namespace SERVO{

int CCONV AttachHandler(CPhidgetHandle ADVSERVO, void *userptr);
int CCONV DetachHandler(CPhidgetHandle ADVSERVO, void *userptr);
int CCONV ErrorHandler(CPhidgetHandle ADVSERVO, void *userptr, int ErrorCode, const char *Description);
int CCONV PositionChangeHandler(CPhidgetAdvancedServoHandle ADVSERVO, void *usrptr, int Index, double Value);

//Display the properties of the attached phidget to the screen.  We will be displaying the name, serial number and version of the attached device.
int display_properties(CPhidgetAdvancedServoHandle phid);

} // end SERVO
} // end HAND


#endif // PHIDGETUTILITIES_HPP
