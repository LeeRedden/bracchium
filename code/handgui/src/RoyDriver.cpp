
#include "RoyDriver.hpp"
#include <iostream>

RoyDriver::RoyDriver()
{
    // horizontal slider
    for( int ii = 0; ii < this->getNumberOfServos(); ++ii )
    {
        fingerCalibration cal = returnCalibration( static_cast<finger>(ii) );
        this->SetServoRange(cal.servo,cal.min,cal.max);
        this->SetServoPosition(cal.servo,cal.center);
    }
    this->EngageAll();
}

void RoyDriver::SetFingerPositions( double positions_[8] )
{
    for( int ii = 0; ii < 8; ++ii )
    {
        this->SetFingerPosition( static_cast<finger>(ii), positions_[ii] );
    }
}

void RoyDriver::SetFingerPosition( finger finger_, double position_)
{
    fingerCalibration cal = returnCalibration( finger_ );
    this->SetServoPosition( cal.servo, returnFingerMapping(finger_,position_) );
}

double RoyDriver::GetCurrentFinger( finger finger_ )
{
    fingerCalibration cal = returnCalibration( finger_ );
    return this->GetCurrent( cal.servo );
}
