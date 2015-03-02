#ifndef JOINTPOSITIONS_HPP
#define JOINTPOSITIONS_HPP

#include "string"
#include "RoyCalibration.hpp"
#include <math.h>       /* sin */
#include <array>
#include <vector>

// This class will house the joint positions for different hand positions.

#define PI 3.14159265

struct pose
{
    double millisecond;
    std::array<double,8> positions;
};

pose generatePose( double millisecond_, double p0, double p1, double p2, double p3, double p4, double p5, double p6, double p7 );

void linearInterpolatePoses( std::vector<pose> &poses_,
                             std::array<double,8> startPose_, std::array<double,8> endPose_,
                             int timeStep_, int timeDuration_ );

std::vector<pose> returnPositions( std::string positionName_ );



#endif // JOINTPOSITIONS_HPP
