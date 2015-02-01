//-*- c++ -*-------------------------------------------------------------------
#ifndef ROYCALIBRATION_HPP
#define ROYCALIBRATION_HPP

#ifdef __GNUC__
#pragma implementation
#endif
//
// Class: RoyCalibration
// Author: Lee Redden
// Email: leeredden@gmail.com
// Created: 31 Jan 2015
// Modifications:
// 20150131 LeeR Initial Version
//
//-----------------------------------------------------------------------------


/**
 * Class stores all of the calibration for an each joint and does a position
 * mapping from -1 -> 1 to the servo value sent to the servo driver
 */

#include <stdexcept>

struct fingerCalibration
{
    int min;
    int center;
    int max;
    int servo;
    bool direction;  // FALSE = higher values go IN, TRUE = higher values go OUT
};

enum finger { BottomWrist = 0, TopWrist, Pinky, Ring, Middle, Pointer, ThumbPivot, ThumbFinger };

/**
 * returns a calibration struct for the desired finger
 */
fingerCalibration returnCalibration( finger finger_ );

/**
 * Maps a finger and position -1 -> 1 to a servo driver value
 */
int returnFingerMapping( finger finger_, double position_ );

#endif // ROYCALIBRATION_HPP
