
#include <iostream>
#include "servoDriver.hpp"
#include "phidgetUtilities.hpp"

ServoDriver::ServoDriver()
    : _servo (0)
    , _numberOfServos(8)
{
    int result;
    double curr_pos;
    const char *err;

    //Declare an advanced servo handle
    //_servo = 0;

    //create the advanced servo object
    CPhidgetAdvancedServo_create(&_servo);

    //Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
    CPhidget_set_OnAttach_Handler((CPhidgetHandle)_servo, AttachHandler, NULL);
    CPhidget_set_OnDetach_Handler((CPhidgetHandle)_servo, DetachHandler, NULL);
    CPhidget_set_OnError_Handler((CPhidgetHandle)_servo, ErrorHandler, NULL);

    //Registers a callback that will run when the motor position is changed.
    //Requires the handle for the Phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
    CPhidgetAdvancedServo_set_OnPositionChange_Handler(_servo, PositionChangeHandler, NULL);

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
    display_properties(_servo);

    //read event data
    printf("Reading.....\n");

    //display current motor position
    if(CPhidgetAdvancedServo_getPosition(_servo, 0, &curr_pos) == EPHIDGET_OK){
        printf("Motor: 0 > Current Position: %f\n", curr_pos);
    }
}

void ServoDriver::setScaleMaxAndMin( float scaleMaxAndMin_ )
{
    //Set up some initial acceleration and velocity values
    std::cout << "setting max and min scales to " << scaleMaxAndMin_ << std::endl;
    if( scaleMaxAndMin_ != 0 )
    {
        double minAccel, maxVel;
        for( int ii = 0; ii < _numberOfServos; ++ii )
        {
            CPhidgetAdvancedServo_getAccelerationMin(_servo, ii, &minAccel);
            CPhidgetAdvancedServo_setAcceleration(_servo, ii, minAccel*scaleMaxAndMin_);
            CPhidgetAdvancedServo_getVelocityMax(_servo, ii, &maxVel);
            CPhidgetAdvancedServo_setVelocityLimit(_servo, ii, maxVel/scaleMaxAndMin_);
        }
    }

}

void ServoDriver::EngageAll( int state_ )
{
    for( int servoNumber = 0; servoNumber < _numberOfServos; ++servoNumber ){
        this->EngageIndividual( servoNumber, state_ );
    }
}

void ServoDriver::EngageIndividual( int servoNumber_, int state_ ){
    CPhidgetAdvancedServo_setEngaged(_servo, servoNumber_, state_);
}

void ServoDriver::SetServoPosition( int servoNumber_, double position_ ){
    CPhidgetAdvancedServo_setPosition( _servo, servoNumber_, position_ );
}

double ServoDriver::GetPosition(int servoNumber_)
{
    double position = 0;
    CPhidgetAdvancedServo_getPosition( _servo, servoNumber_, &position);
    return position;
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

void ServoDriver::close()
{
    printf("Closing...\n");
    CPhidget_close((CPhidgetHandle)_servo);
    CPhidget_delete((CPhidgetHandle)_servo);
}

