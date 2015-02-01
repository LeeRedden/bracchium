#include "RoyCalibration.hpp"
#include <math.h>     /* abs */
#include <iostream>

fingerCalibration returnCalibration( finger finger_ )
{
    fingerCalibration calib;
    switch( finger_ ) {
    case ThumbFinger:
        calib.min = 30;
        calib.center = 38;
        calib.max = 90;
        calib.servo = 1;
        calib.direction = false;
        return calib;
    case ThumbPivot:
        calib.min = 75;
        calib.center = 100;
        calib.max = 174;
        calib.servo = 2;
        calib.direction = true;
        return calib;
    case Pointer:
        calib.min = 55;
        calib.center = 143;
        calib.max = 160;
        calib.servo = 5;
        calib.direction = true;
        return calib;
    case Middle:
        calib.min = 70;
        calib.center = 83;
        calib.max = 190;
        calib.servo = 0;
        calib.direction = false;
        return calib;
    case Ring:
        calib.min = 30;
        calib.center = 49;
        calib.max = 135;
        calib.servo = 6;
        calib.direction = false;
        return calib;
    case Pinky:
        calib.min = 105;
        calib.center = 125;
        calib.max = 200;
        calib.servo = 7;
        calib.direction = false;
        return calib;
    case TopWrist:
        calib.min = 60;
        calib.center = 114;
        calib.max = 150;
        calib.servo = 3;
        calib.direction = true;
        return calib;
    case BottomWrist:
        calib.min = 67;
        calib.center = 102;
        calib.max = 140;
        calib.servo = 4;
        calib.direction = false;
        return calib;
    default:
        throw std::invalid_argument( "not a finger type in fingerCalibration" );
    }
};


int returnFingerMapping( finger finger_, double position_ ) // position ranges from 0->1
{
    if( position_ > 1 || position_ < -1 )
    {
        throw std::invalid_argument( "position value is out of bounds in returnFingerMapping" );
    }

    fingerCalibration fc = returnCalibration( finger_ );
    if(  (position_ >= 0 && !fc.direction) || //value is between center and max
         (position_ <= 0 && fc.direction) )
    {
        return (fc.max - fc.center)*fabs(position_) + fc.center;
    }
    else
    {
        return (fc.min - fc.center)*fabs(position_) + fc.center;
    }
}
