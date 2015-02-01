//-*- c++ -*-------------------------------------------------------------------
#ifndef SERVODRIVER_HPP
#define SERVODRIVER_HPP

#ifdef __GNUC__
#pragma implementation
#endif
//
// Class: ServoDriver
// Author: Lee Redden
// Email: leeredden@gmail.com
// Created: 31 Jan 2015
// Modifications:
// 20150131 LeeR Initial Version
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <phidget21.h>


class ServoDriver
{
public:
    ServoDriver();
    void close();

    // set parameters
    void EngageAll( int state_ = 1 );
    void EngageIndividual( int servoNumber_, int state_ );

    // get parameters
    double GetPosition( int servoNumber_ );
    double GetCurrent( int servoNumber_ );
    int getNumberOfServos(){ return _numberOfServos; }

protected:
    // set parameters
    void SetServoRange( int servoNumber_, double min_, double max_ );
    void SetServoPosition( int servoNumber_, double position_ );
    void setScaleMaxAndMin( float scaleMaxAndMin_ = 0 );

private:
    int _numberOfServos;
    CPhidgetAdvancedServoHandle _servo;
};


#endif // SERVODRIVER_HPP
