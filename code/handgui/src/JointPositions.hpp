#ifndef JOINTPOSITIONS_HPP
#define JOINTPOSITIONS_HPP

#include "string"
#include "royCalibration.hpp"

// This class will house the joint positions for different hand positions. Unclear how the will currently be executed
struct position
{
    int positions[8];
};

position* returnPosition( std::string positionName_ )
{
    //if( positionName_ == "bird")
    {
        position* bird = (new position);

        fingerCalibration calib = returnCalibration( ThumbFinger );
        bird->positions[static_cast<int>(ThumbFinger)] = calib.center;

        calib = returnCalibration( ThumbPivot );
        bird->positions[static_cast<int>(ThumbPivot)] = calib.center;

        calib = returnCalibration( Pointer );
        bird->positions[static_cast<int>(Pointer)] = calib.center;

        calib = returnCalibration( Middle );
        bird->positions[static_cast<int>(Middle)] = calib.center;

        calib = returnCalibration( Ring );
        bird->positions[static_cast<int>(Ring)] = calib.max;

        calib = returnCalibration( Pinky );
        bird->positions[static_cast<int>(Pinky)] = calib.center;

        calib = returnCalibration( TopWrist );
        bird->positions[static_cast<int>(TopWrist)] = calib.center;

        calib = returnCalibration( BottomWrist );
        bird->positions[static_cast<int>(BottomWrist)] = calib.center;

        return bird;
    }
}



#endif // JOINTPOSITIONS_HPP
