//-*- c++ -*-------------------------------------------------------------------
#ifndef ROYDRIVER_HPP
#define ROYDRIVER_HPP

#ifdef __GNUC__
#pragma implementation
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
/**
 * High level class that initiates all of the low level servo driver code, calibration
 * code and finger mapping. This function allows the user to easily specify what each
 * finger should be driven to, or all eight joints at the same time.
 */

#include "RoyCalibration.hpp"
#include "ServoDriver.hpp"
#include <array>

class RoyDriver: public ServoDriver
{
public:
    RoyDriver();
    ~RoyDriver();

    //! Sets all of the finger positions at once with a single vector
    /*!
   \param positions_ finger positions where order is dictated by the enum finger in RoyCalibration.hpp
   */
    void SetFingerPositions( std::array<double,8> positions_ );

    //! Set an individual finger position
    /*!
   \param position_ desired finger position where 1 = all the way closed for fingers, toward the body for wrist
   \                                              0 = neutral
   \                                             -1 = all the way out for fingers, away from the body for wrist
   */
    void SetFingerPosition( finger finger_, double position_ );

    //! Servo driver returns how much current is being sent to the servo
    /*!
   \param finger_: which finger
   \return value generated by servo driver
   */
    double GetCurrentFinger( finger finger_ );

private:
    int _numberOfServos;
    CPhidgetAdvancedServoHandle _servo;

    bool CheckPositionLimits( std::array<double,8> &positions_ );
};

#endif // ROYDRIVER_HPP
