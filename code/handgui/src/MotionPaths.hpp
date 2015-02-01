#ifndef JOINTPOSITIONS_HPP
#define JOINTPOSITIONS_HPP

#include "string"
#include "RoyCalibration.hpp"
#include <math.h>       /* sin */
#include <array>

// This class will house the joint positions for different hand positions. Unclear how the will currently be executed

#define PI 3.14159265

struct pose
{
    double millisecond;
    double positions[8];
};

pose generatePose( double millisecond_, double p0, double p1, double p2, double p3, double p4, double p5, double p6, double p7 )
{
    pose newPose;
    newPose.millisecond = millisecond_;
    newPose.positions[0] = p0;
    newPose.positions[1] = p1;
    newPose.positions[2] = p2;
    newPose.positions[3] = p3;
    newPose.positions[4] = p4;
    newPose.positions[5] = p5;
    newPose.positions[6] = p6;
    newPose.positions[7] = p7;
    return newPose;
}

std::vector<pose> returnPosition( std::string positionName_ )
{
    std::vector<pose> poses;
    if( positionName_ == "bird" )
    {
        //                     0           1       2      3     4        5         6            7
        //  enum finger { BottomWrist, TopWrist, Pinky, Ring, Middle, Pointer, ThumbPivot, ThumbFinger };
        //                         0,    1,   2,   3,   4,   5,    6,    7
        poses.push_back( generatePose( 100,  0,    0,   1,   1,  -1,   1,    0,  0.25 )  );
    }
    else if( positionName_ == "rock" )
    {
        for( int ii = 0; ii < 720; ii = ii + 7 ){
            poses.push_back( generatePose( 3, 0.5*sin(ii*PI/180), 0.5*sin(ii*PI/180),  -1,   1,   1,   -1,   -1,   -1 ) );
        }

    }
    else if( positionName_ == "hang10")
    {
        for( int ii = 0; ii < 720; ii = ii + 7 ){
            poses.push_back( generatePose( 3, 0.5*sin(ii*PI/180), -0.5*sin(ii*PI/180),  -1,   1,   1,   1,   -1,   -1) );
        }

    }
    else if( positionName_ == "motion")
    {
        for( int ii = 0; ii < 360*2; ii = ii + 7 ){
            poses.push_back( generatePose( 3,  0.5*sin(ii*PI/180), 0.5*cos(ii*PI/180),  1,   1,   1,   1,   -1,   -1) );
        }
        for( int ii = 0; ii < 360*2; ii = ii + 7 ){
            poses.push_back( generatePose( 3,  0, 0, sin(ii*PI/180), sin((30+ii)*PI/180),sin((60+ii)*PI/180),sin((90+ii)*PI/180),  sin((270+ii)*PI/180), sin((270+ii)*PI/180) ) );
        }
        for( int ii = 0; ii < 360*3; ii = ii + 7 ){
            poses.push_back( generatePose( 3,  0.5*sin(ii*PI/180), 0.5*cos(ii*PI/180), sin(ii*PI/180), sin((30+ii)*PI/180),sin((60+ii)*PI/180),sin((90+ii)*PI/180),  sin((270+ii)*PI/180), sin((270+ii)*PI/180) ) );
        }
        poses.push_back( generatePose( 100,  0,    0,   0,   0,  0,   0,   0,  0) );
    }
    else{
        poses.push_back( generatePose( 100,  0,    0,   0,   0,  0,   0,    0,  0) );
    }

    return poses;
}



#endif // JOINTPOSITIONS_HPP
