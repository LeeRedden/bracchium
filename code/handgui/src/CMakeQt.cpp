#include "CMakeQt.h"
#include <phidget21.h>

#include "boost/foreach.hpp"
#include "servoDriver.hpp"

struct fingerCalibration
{
    int min;
    int center;
    int max;
    int servo;
};

enum finger { ThumbFinger = 0, ThumbPivot , Pointer , Middle , Ring , Pinky , TopWrist , BottomWrist };

fingerCalibration returnCalibration( finger finger_)
{
    fingerCalibration calib;
    switch( finger_ ) {
    case ThumbFinger:
        calib.min = 30;
        calib.center = 70;
        calib.max = 90;
        calib.servo = 1;
        return calib;
    case ThumbPivot:
        calib.min = 75;
        calib.center = 100;
        calib.max = 174;
        calib.servo = 2;
        return calib;
    case Pointer:
        calib.min = 40;
        calib.center = 95;
        calib.max = 105;
        calib.servo = 5;
        return calib;
    case Middle:
        calib.min = 70;
        calib.center = 100;
        calib.max = 190;
        calib.servo = 0;
        return calib;
    case Ring:
        calib.min = 30;
        calib.center = 60;
        calib.max = 135;
        calib.servo = 6;
        return calib;
    case Pinky:
        calib.min = 105;
        calib.center = 110;
        calib.max = 200;
        calib.servo = 7;
        return calib;
    case TopWrist:
        calib.min = 60;
        calib.center = 114;
        calib.max = 150;
        calib.servo = 3;
        return calib;
    case BottomWrist:
        calib.min = 67;
        calib.center = 102;
        calib.max = 140;
        calib.servo = 4;
        return calib;
    }
};

CMakeQt::CMakeQt(QWidget *parent)
    : QDialog(parent)
{
    m_ui.setupUi(this);
    m_ui.label->setText( "Hand Movement GUI for Roy the Robot, by Lee Redden" );

    // close button
    connect( m_ui.closeButton, SIGNAL(pressed()), this, SLOT(closeButton()) );
    connect( m_ui.pauseButton, SIGNAL(pressed()), this, SLOT(pauseButton()) );
    connect( m_ui.resumeButton, SIGNAL(pressed()), this, SIGNAL(resumeButton()) );

    // populate sliders
    _sliders.push_back( m_ui.horizontalSlider0 );
    _sliders.push_back( m_ui.horizontalSlider1 );
    _sliders.push_back( m_ui.horizontalSlider2 );
    _sliders.push_back( m_ui.horizontalSlider3 );
    _sliders.push_back( m_ui.horizontalSlider4 );
    _sliders.push_back( m_ui.horizontalSlider5 );
    _sliders.push_back( m_ui.horizontalSlider6 );
    _sliders.push_back( m_ui.horizontalSlider7 );

    // populate lcd for command
    _commanded.push_back( m_ui.lcd0_0 );
    _commanded.push_back( m_ui.lcd1_0 );
    _commanded.push_back( m_ui.lcd2_0 );
    _commanded.push_back( m_ui.lcd3_0 );
    _commanded.push_back( m_ui.lcd4_0 );
    _commanded.push_back( m_ui.lcd5_0 );
    _commanded.push_back( m_ui.lcd6_0 );
    _commanded.push_back( m_ui.lcd7_0 );

    // populate lcd for run
    _run.push_back( m_ui.lcd0_1 );
    _run.push_back( m_ui.lcd1_1 );
    _run.push_back( m_ui.lcd2_1 );
    _run.push_back( m_ui.lcd3_1 );
    _run.push_back( m_ui.lcd4_1 );
    _run.push_back( m_ui.lcd5_1 );
    _run.push_back( m_ui.lcd6_1 );
    _run.push_back( m_ui.lcd7_1 );

    // horizontal slider
    for( int ii = 0; ii < _sd.getNumberOfServos(); ++ii )
    {
        fingerCalibration cal = returnCalibration( static_cast<finger>(ii) );

        // set min and max
        _sliders[ii]->setRange(cal.min,cal.max);
        _sd.SetServoRange(cal.servo,cal.min,cal.max);

        // center the cursor
        _sliders[ii]->setSliderPosition(cal.center);
        _sd.SetServo(cal.servo,cal.center);

        // set connection
        connect( _sliders[ii], SIGNAL(sliderMoved(int)), this, SLOT(sliderMoved()) );
    }

    //    // initialize servos
    //    _sd.SetServo(0,100.0);  // middle finger
    //    _sd.SetServoRange(0,70,190);

    //    _sd.SetServo(1,70.0); // thumb finger
    //    _sd.SetServoRange(1,30,90);

    //    _sd.SetServo(2,100.0); // thumb pivot
    //    _sd.SetServoRange(2,75,174);

    //    _sd.SetServo(3,114.0); // top wrist
    //    _sd.SetServoRange(3,60,150);

    //    _sd.SetServo(4,102.0); // bottom wrist
    //    _sd.SetServoRange(4,50,140);

    //    _sd.SetServo(5,95.0); // pointer finger
    //    _sd.SetServoRange(5,40,105);

    //    _sd.SetServo(6,60.0); // ring finger
    //    _sd.SetServoRange(6,30,135);

    //    _sd.SetServo(7,110.0); // pinky finger
    //    _sd.SetServoRange(7,105,200);

    //_sd.EngageAll();
    _sd.EngageIndividual(3,1);
    _sd.EngageIndividual(4,1);
}

void CMakeQt::sliderMoved()
{
    for( int ii = 0; ii < _sd.getNumberOfServos(); ++ii )
    {
        fingerCalibration cal = returnCalibration( static_cast<finger>(ii) );

        _sd.SetServo( cal.servo, _sliders[ii]->value() );
        _commanded[ii]->display( _sliders[ii]->value() );
        _run[ii]->display( _sd.GetPosition(cal.servo) );
    }
}

void CMakeQt::closeButton() {
    _sd.close();
}
void CMakeQt::pauseButton(){
    _sd.EngageAll(0);
}
void CMakeQt::resumeButton(){
    _sd.EngageAll();
}
