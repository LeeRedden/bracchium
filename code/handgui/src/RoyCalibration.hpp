#ifndef ROYCALIBRATION_HPP
#define ROYCALIBRATION_HPP

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

fingerCalibration returnCalibration( finger finger_ );
int returnFingerMapping( finger finger_, double position_ );

#endif // ROYCALIBRATION_HPP
