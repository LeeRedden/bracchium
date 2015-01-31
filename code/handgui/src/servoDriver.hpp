#ifndef SERVODRIVER_HPP
#define SERVODRIVER_HPP


#include "phidgetUtilities.hpp"
#include <stdio.h>
#include <phidget21.h>



class ServoDriver
{
public:
    ServoDriver(float scaleMaxAndMin = 2);
    void SetServo(int servoNumber_, int position_ );
    void EngageAll( bool state_ = 1 );
    void EngageIndividual( int servoNumber_, bool state );
    double GetCurrent( int servoNumber_ );
    void SetServoRange( int servoNumber_, double min_, double max_ );


private:
    int _numberOfServos;
    CPhidgetAdvancedServoHandle _servo;
    std::vector<int> vals;
};

ServoDriver::ServoDriver(float scaleMaxAndMin)
    : _servo (0)
    , _numberOfServos(8)
{
    int result;
    double curr_pos;
    const char *err;
    double minAccel, maxVel;

    //Declare an advanced servo handle
    //_servo = 0;

    //create the advanced servo object
    CPhidgetAdvancedServo_create(&_servo);

    //Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
    CPhidget_set_OnAttach_Handler((CPhidgetHandle)_servo, HAND::SERVO::AttachHandler, NULL);
    CPhidget_set_OnDetach_Handler((CPhidgetHandle)_servo, HAND::SERVO::DetachHandler, NULL);
    CPhidget_set_OnError_Handler((CPhidgetHandle)_servo, HAND::SERVO::ErrorHandler, NULL);

    //Registers a callback that will run when the motor position is changed.
    //Requires the handle for the Phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
    CPhidgetAdvancedServo_set_OnPositionChange_Handler(_servo, HAND::SERVO::PositionChangeHandler, NULL);

    //open the device for connections
    CPhidget_open((CPhidgetHandle)_servo, -1);

    //get the program to wait for an advanced servo device to be attached
    printf("Waiting for Phidget to be attached....");
    if((result = CPhidget_waitForAttachment((CPhidgetHandle)_servo, 10000)))
    {
        CPhidget_getErrorDescription(result, &err);
        printf("Problem waiting for attachment: %s\n", err);
    }

    //Display the properties of the attached device
    HAND::SERVO::display_properties(_servo);

    //read event data
    printf("Reading.....\n");

    //This example assumes servo motor is attached to index 0

    //Set up some initial acceleration and velocity values
    CPhidgetAdvancedServo_getAccelerationMin(_servo, 0, &minAccel);
    CPhidgetAdvancedServo_setAcceleration(_servo, 0, minAccel*2);
    CPhidgetAdvancedServo_getVelocityMax(_servo, 0, &maxVel);
    CPhidgetAdvancedServo_setVelocityLimit(_servo, 0, maxVel/2);

    //display current motor position
    if(CPhidgetAdvancedServo_getPosition(_servo, 0, &curr_pos) == EPHIDGET_OK)
        printf("Motor: 0 > Current Position: %f\n", curr_pos);

    //keep displaying servo event data until user input is read
    printf("Press any key to continue\n");
    getchar();
}

void ServoDriver::EngageAll( bool state_ )
{
    for( int servoNumber = 0; servoNumber < _numberOfServos; ++servoNumber ){
        CPhidgetAdvancedServo_setEngaged(_servo, servoNumber, state_ );
    }
}

void ServoDriver::EngageIndividual( int servoNumber_, bool state )
{
    CPhidgetAdvancedServo_setEngaged(_servo, servoNumber_, state);
}

void ServoDriver::SetServo( int servoNumber_, int position_ )
{
    CPhidgetAdvancedServo_setEngaged( _servo, servoNumber_, position_ );
}
double ServoDriver::GetCurrent( int servoNumber_ )
{
    double current = 0;
    CPhidgetAdvancedServo_getCurrent( _servo, servoNumber_, &current );
    return current;

}
void ServoDriver::SetServoRange( int servoNumber_, double min_, double max_ )
{
    CPhidgetAdvancedServo_setPositionMin( _servo, servoNumber_, min_);
    CPhidgetAdvancedServo_setPositionMax( _servo, servoNumber_, max_);
}


#endif // SERVODRIVER_HPP
