
#include "MotionPaths.hpp"

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

void linearInterpolatePoses( std::vector<pose> &poses_, std::array<double,8> startPose_, std::array<double,8> endPose_, int timeStep_, int timeDuration_ )
{
    for( int ii = 0; ii < timeDuration_; ii = ii + timeStep_ ){
        poses_.push_back( generatePose( timeStep_,
                                       (endPose_[0] - startPose_[0])*ii/timeDuration_ + startPose_[0],
                                       (endPose_[1] - startPose_[1])*ii/timeDuration_ + startPose_[1],
                                       (endPose_[2] - startPose_[2])*ii/timeDuration_ + startPose_[2],
                                       (endPose_[3] - startPose_[3])*ii/timeDuration_ + startPose_[3],
                                       (endPose_[4] - startPose_[4])*ii/timeDuration_ + startPose_[4],
                                       (endPose_[5] - startPose_[5])*ii/timeDuration_ + startPose_[5],
                                       (endPose_[6] - startPose_[6])*ii/timeDuration_ + startPose_[6],
                                       (endPose_[7] - startPose_[7])*ii/timeDuration_ + startPose_[7])
                         );
    }

}

std::vector<pose> returnPositions( std::string positionName_ )
{
    std::vector<pose> poses;
    if( positionName_ == "theBird" )
    {
        //                     0           1       2      3     4        5         6            7
        //  enum finger { BottomWrist, TopWrist, Pinky, Ring, Middle, Pointer, ThumbPivot, ThumbFinger };
        //                         0,    1,   2,   3,   4,   5,    6,    7
        poses.push_back( generatePose( 200,  0,    0,   1,   1,   1,   1,    0,  0 )  );

        for( int ii = 0; ii < 180; ii = ii + 1 ){
            poses.push_back( generatePose( 15, 0,    0,   1,   1,   cos(ii*PI/180),   1,    0.5*cos(ii*PI/180)-0.5,  0.5*cos(ii*PI/180)-0.5 )  );
        }
        for( int ii = 180; ii < 360; ii = ii + 1 ){
            poses.push_back( generatePose( 10, 0,    0,   1,   1,   cos(ii*PI/180),   1,    0.5*cos(ii*PI/180)-0.5,  0.5*cos(ii*PI/180)-0.5 )  );
        }
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
    else if( positionName_ == "davinci" )
    {
        std::array<double,8> startPose {{ 1, 0.929, 0.302, 0.349, 0.421, 0.413, 0.825, 0.48 }};
        std::array<double,8> endPose = {{ -0.38, -0.4, 0.405, 0.317, 0.167, -0.18, 0.762, 0.183 }};

        int timeStep = 7;
        int timeDuration = 1000;

        linearInterpolatePoses( poses, startPose, endPose, timeStep, timeDuration );
    }
    else if( positionName_ == "peace" )
    {
        // BottomWrist, TopWrist, Pinky, Ring, Middle, Pointer, ThumbPivot, ThumbFinger
        poses.push_back( generatePose( 100, -0.75, 0.75, 1, 1, -1, -1, 1, 1) );
    }
    else if( positionName_ == "italian123" )
    {
        // BottomWrist, TopWrist, Pinky, Ring, Middle, Pointer, ThumbPivot, ThumbFinger

        poses.push_back( generatePose( 1000, 0, 0, 1, 1, 1, 1, 1, 0) );
        poses.push_back( generatePose( 1000, 0, 0, 1, 1, 1, 1, -1, -1) );
        poses.push_back( generatePose( 1000, 0, 0, 1, 1, 1, -1, -1, -1) );
        poses.push_back( generatePose( 1000, 0, 0, 1, 1, -1, -1, -1, -1) );
        poses.push_back( generatePose( 1000, 0, 0, 1, -1, -1, -1, -1, -1) );
        poses.push_back( generatePose( 1000, 0, 0, -1, -1, -1, -1, -1, -1) );

        for( int ii = 0; ii < 720; ii = ii + 7 ){
            poses.push_back( generatePose( 3, 0.5*sin(ii*PI/180), -0.5*sin(ii*PI/180),  -1, -1, -1, -1, -1, -1) );
        }

    }
    else if( positionName_ == "test" )
    {
        poses.push_back( generatePose( 1000, 0, 0, 1, 1, 1, 0.4, 1, 1) );
    }
    else{
        poses.push_back( generatePose( 100,  0,    0,   0,   0,  0,   0,    0,  0) );
    }

    return poses;
}

