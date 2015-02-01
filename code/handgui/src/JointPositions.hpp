#ifndef JOINTPOSITIONS_HPP
#define JOINTPOSITIONS_HPP

#include "string"
#include "RoyCalibration.hpp"
#include <math.h>       /* sin */

// This class will house the joint positions for different hand positions. Unclear how the will currently be executed

#define PI 3.14159265

struct pose
{
    double millisecond;
    double positions[8];
};

std::vector<pose> returnPosition( std::string positionName_ )
{
    std::vector<pose> poses;
    if( positionName_ == "bird" )
    {
        //                     0           1       2      3     4        5         6            7
        //  enum finger { BottomWrist, TopWrist, Pinky, Ring, Middle, Pointer, ThumbPivot, ThumbFinger };
        //                         0,    1,   2,   3,   4,   5,    6,    7
        poses.push_back( { 100, {  0,    0,   1,   1,  -1,   1,    0,  0.25} } );
}
else if( positionName_ == "rock" )
{
    //                         0,    1,   2,   3,   4,   5,    6,    7
    for( int ii = 0; ii < 720; ii = ii + 7 )
    {
        poses.push_back( { 3, { 0.5*sin(ii*PI/180), 0.5*sin(ii*PI/180),  -1,   1,   1,   -1,   -1,   -1} } );
    }

//    poses.push_back( { 300, {  0,    0,  -1,   1,   1,  -1,   -1,   -1} } );
}
else if( positionName_ == "hang10")
{
//                         0,    1,   2,   3,   4,   5,    6,    7
for( int ii = 0; ii < 720; ii = ii + 7 )
{
    poses.push_back( { 3, { 0.5*sin(ii*PI/180), -0.5*sin(ii*PI/180),  -1,   1,   1,   1,   -1,   -1} } );
}

}
else if( positionName_ == "motion")
{
//                         0,    1,   2,   3,   4,   5,    6,    7
    for( int ii = 0; ii < 720; ii = ii + 7 )
    {
        poses.push_back( { 3, { 0.5*sin(ii*PI/180), 0.5*cos(ii*PI/180),  1,   1,   1,   1,   -1,   -1} } );
    }
    for( int ii = 0; ii < 720; ii = ii + 7 )
    {
        poses.push_back( { 3, { 0, 0, sin(ii*PI/180), sin((30+ii)*PI/180),sin((60+ii)*PI/180),sin((90+ii)*PI/180),  sin((270+ii)*PI/180), sin((270+ii)*PI/180) } } );
    }
    for( int ii = 0; ii < 1080; ii = ii + 7 )
    {
       poses.push_back( { 3, { 0.5*sin(ii*PI/180), 0.5*cos(ii*PI/180), sin(ii*PI/180), sin((30+ii)*PI/180),sin((60+ii)*PI/180),sin((90+ii)*PI/180),  sin((270+ii)*PI/180), sin((270+ii)*PI/180) } } );
    }

    poses.push_back({ 100, {  0,    0,   0,   0,  0,   0,    0,  0} });
}
else
{
pose newPose = { 100, {  0,    0,   0,   0,  0,   0,    0,  0} };
poses.push_back({ 100, {  0,    0,   0,   0,  0,   0,    0,  0} });
}

return poses;
}



#endif // JOINTPOSITIONS_HPP
