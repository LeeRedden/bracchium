
#include "phidgetUtilities.hpp"


int CCONV AttachHandler(CPhidgetHandle ADVSERVO, void *userptr)
{
    int serialNo;
    const char *name;

    CPhidget_getDeviceName (ADVSERVO, &name);
    CPhidget_getSerialNumber(ADVSERVO, &serialNo);
    printf("%s %10d attached!\n", name, serialNo);

    return 0;
}

int CCONV DetachHandler(CPhidgetHandle ADVSERVO, void *userptr)
{
    int serialNo;
    const char *name;

    CPhidget_getDeviceName (ADVSERVO, &name);
    CPhidget_getSerialNumber(ADVSERVO, &serialNo);
    printf("%s %10d detached!\n", name, serialNo);

    return 0;
}

int CCONV ErrorHandler(CPhidgetHandle ADVSERVO, void *userptr, int ErrorCode, const char *Description)
{
    printf("Error handled. %d - %s\n", ErrorCode, Description);
    return 0;
}

int CCONV PositionChangeHandler(CPhidgetAdvancedServoHandle ADVSERVO, void *usrptr, int Index, double Value)
{
    printf("Motor: %d > Current Position: %f\n", Index, Value);
    return 0;
}

//Display the properties of the attached phidget to the screen.  We will be displaying the name, serial number and version of the attached device.
int display_properties(CPhidgetAdvancedServoHandle phid)
{
    int serialNo, version, numMotors;
    const char* ptr;

    CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
    CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
    CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);

    CPhidgetAdvancedServo_getMotorCount (phid, &numMotors);

    printf("%s\n", ptr);
    printf("Serial Number: %10d\nVersion: %8d\n# Motors: %d\n", serialNo, version, numMotors);

    return 0;
}
