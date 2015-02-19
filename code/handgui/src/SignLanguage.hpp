#ifndef SIGNLANGUAGE_HPP
#define SIGNLANGUAGE_HPP

#include "MotionPaths.hpp"
#include "RoyCalibration.hpp"
#include <iostream>


std::array<double,8> singleLetterPosition( char letter_ )
{
    std::cout << "  Signing a character " << letter_ << std::endl;

    std::array<double,8> pose;
    switch( letter_ )
    {
    case 'a': pose = {{-0.6,0.6,1,1,1,1,0,0}}; break;
    case 'b': pose = {{-0.6,0.6,-1,-1,-1,-1,1,1}}; break;
    case 'c': pose = {{-0.6,0.6,0.5,0.5,0.5,0.5,-1,0.5}}; break;
    case 'd': pose = {{-0.6,0.6,1,1,1,-1,1,1}}; break;
    case 'e': pose = {{-0.6,0.6,0.5,0.5,0.5,0.5,1,1}}; break;
    case 'f': pose = {{-0.6,0.6,-1,-1,-1,0.6,1,0.1}}; break;
    case 'g': pose = {{0.2,-0.2,1,1,1,-1,1,-1}}; break;
    case 'h': pose = {{0.2,-0.2,1,1,-1,-1,1,-1}}; break;
    case 'i': pose = {{-0.6,0.6,-1,1,1,1,1,1}}; break;
    case 'j': pose = {{-0.4,0.4,-1,1,1,1,1,1}}; break; // more work on j
    case 'k': pose = {{-0.6,0.6,1,1,0.5,-1,1,1}}; break;
    case 'l': pose = {{-0.6,0.6,1,1,1,-1,-1,-1}}; break;
    case 'm': pose = {{0.5,0.5,1,0.5,0.5,0.5,1,1}}; break;
    case 'n': pose = {{0.5,0.5,1,1,0.5,0.5,1,1}}; break;
    case 'o': pose = {{-0.6,0.6,0.5,0.5,0.5,0.5,1,1}}; break;
    case 'p': pose = {{0.2,-0.2,1,1,0.5,-1,1,0.5}}; break;


    case 'r': pose = {{-0.6,0.6,1,1,-1,0,0,0}}; break;
    case 's': pose = {{-0.6,0.6,1,1,1,1,1,1}}; break;


    case 'u': pose = {{-0.6,0.6,1,1,-1,-1,1,1}}; break;
    case 'v': pose = {{-0.6,0.6,1,1,0.2,-1,1,1}}; break;
    case 'w': pose = {{-0.6,0.6,1,-1,-1,-1,1,1}}; break;
    case 'x': pose = {{-0.6,0.6,1,1,1,0.5,1,1}}; break;
    case 'y': pose = {{-0.6,0.6,-1,1,1,1,-1,-1}}; break;
    case 'z': pose = {{0.2,-0.2,1,1,1,-1,1,1}}; break; // more work on z

    default:
        pose = {{0,0,0,0,0,0,0,0}};
        break;
    }

    return pose;
}

std::vector<pose> returnSignLanguagePositions( std::string signString_, float speed_ = 1 )
{
    std::vector<pose> poses;
    int timeStep = 30/speed_;
    int timeDurationHold = 300/speed_;
    int timeDurationMove = 200/speed_;

    if( signString_.size() >= 1 ){
        char c = signString_[0];
        linearInterpolatePoses( poses, singleLetterPosition(c), singleLetterPosition(c), timeStep, timeDurationHold );
    }

    for( std::string::size_type ii = 1; ii < signString_.size(); ++ii )
    {
        char current = signString_[ii-1];
        char next = signString_[ii];
        linearInterpolatePoses( poses, singleLetterPosition(current), singleLetterPosition(next), timeStep, timeDurationMove );
        linearInterpolatePoses( poses, singleLetterPosition(next), singleLetterPosition(next), timeStep, timeDurationHold );
    }

    return poses;
}

#endif // SIGNLANGUAGE_HPP
