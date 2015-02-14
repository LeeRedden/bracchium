//-*- c++ -*-------------------------------------------------------------------
#ifdef __GNUC__
#pragma implementation "RoyDriver.hpp"
#endif
//
// Class: RoyDriver
// Author: Lee Redden
// Email: leeredden@gmail.com
// Created: 31 Jan 2015
// Modifications:
// 20150131 LeeR Initial Version
//
//-----------------------------------------------------------------------------

#include <array>
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
RoyDriver::~RoyDriver(){
    this->EngageAll(0);
}

bool RoyDriver::CheckPositionLimits( std::array<double,8> &positions_ )
{
    // colision with pointer finger
    // check if thumb is in far enough
    if( positions_[Pointer] > 0.5 && (positions_[ThumbPivot]/2 + positions_[ThumbFinger] > 0.5) )
    {
        positions_[ThumbFinger] = 0.5 - positions_[ThumbPivot]/2; // set thumb finger
        return true;
    }
    return false;
}

void RoyDriver::SetFingerPositions( std::array<double,8> positions_ )
{
    CheckPositionLimits( positions_ );

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
