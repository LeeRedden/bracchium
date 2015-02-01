#ifndef ROYDRIVER_HPP
#define ROYDRIVER_HPP

#include "royCalibration.hpp"
#include "servoDriver.hpp"



class RoyDriver: public ServoDriver
{
public:
    RoyDriver();

    void SetFingerPositions( double positions_[8] );
    void SetFingerPosition( finger finger_, double position_ );
    double GetCurrentFinger( finger finger_ );
//    void close();

//    // set parameters
//    void SetServoRange( int servoNumber_, double min_, double max_ );
//    void SetPosition( int servoNumber_, double position_ );
//    void EngageAll( int state_ = 1 );
//    void EngageIndividual( int servoNumber_, int state_ );

//    // get parameters
//    double GetPosition( int servoNumber_ );
//    double GetCurrent( int servoNumber_ );
//    int getNumberOfServos(){ return _numberOfServos; }

private:
    int _numberOfServos;
    CPhidgetAdvancedServoHandle _servo;
};

#endif // ROYDRIVER_HPP
