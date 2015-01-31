#ifndef SERVODRIVER_HPP
#define SERVODRIVER_HPP


#include "phidgetUtilities.hpp"
#include <stdio.h>
#include <phidget21.h>



class ServoDriver
{
public:
    ServoDriver(float scaleMaxAndMin = 2);
    void SetServo(int servoNumber_, double position_ );
    double GetPosition( int servoNumber_ );
    void EngageAll( int state_ = 1 );
    void EngageIndividual( int servoNumber_, int state_ );
    double GetCurrent( int servoNumber_ );
    void SetServoRange( int servoNumber_, double min_, double max_ );
    void close();

    int getNumberOfServos(){ return _numberOfServos; }


private:
    int _numberOfServos;
    CPhidgetAdvancedServoHandle _servo;
};

#endif // SERVODRIVER_HPP
