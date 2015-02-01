#include "CMakeQt.h"
#include <phidget21.h>

#include "boost/foreach.hpp"
//#include "servoDriver.hpp"
//#include "royCalibration.hpp"
#include "RoyDriver.hpp"
#include "JointPositions.hpp"

CMakeQt::CMakeQt(QWidget *parent)
    : QDialog(parent)
{
    m_ui.setupUi(this);
    m_ui.label->setText( "Hand Movement GUI for Roy the Robot, by Lee Redden" );

    // close, pause, resume button
    connect( m_ui.motionButton, SIGNAL(pressed()), this, SLOT(motionButton()) );
    connect( m_ui.pauseButton, SIGNAL(pressed()), this, SLOT(pauseButton()) );
    connect( m_ui.resumeButton, SIGNAL(pressed()), this, SLOT(resumeButton()) );

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
    _current.push_back( m_ui.lcd0_1 );
    _current.push_back( m_ui.lcd1_1 );
    _current.push_back( m_ui.lcd2_1 );
    _current.push_back( m_ui.lcd3_1 );
    _current.push_back( m_ui.lcd4_1 );
    _current.push_back( m_ui.lcd5_1 );
    _current.push_back( m_ui.lcd6_1 );
    _current.push_back( m_ui.lcd7_1 );

    _rd = new RoyDriver();

    // horizontal slider
    for( int ii = 0; ii < _rd->getNumberOfServos(); ++ii )
    {
        _sliders[ii]->setRange(0,1);
        // center the cursor
        _sliders[ii]->setSliderPosition(0.5);
        _commanded[ii]->display(0.5);
        // set connection
        connect( _sliders[ii], SIGNAL(sliderMoved(int)), this, SLOT(sliderMoved()) );
    }
}

void CMakeQt::sliderMoved()
{
    for( int ii = 0; ii < _rd->getNumberOfServos(); ++ii )
    {
        _rd->SetFingerPosition( static_cast<finger>(ii), _sliders[ii]->value() );
        _commanded[ii]->display( _sliders[ii]->value() );
        _current[ii]->display( _rd->GetCurrentFinger( static_cast<finger>(ii) ) );
    }
}

void CMakeQt::motionButton() {
//    position* pos = returnPosition( "bird" );
//    for( int ii = 0; ii < _rd->getNumberOfServos(); ++ii )
//    {
//        _rd->SetPosition( ii, pos->positions[ii] );
//        _commanded[ii]->display( _sliders[ii]->value() );
//    }
}

void CMakeQt::pauseButton(){
    _rd->EngageAll(0);
}

void CMakeQt::resumeButton(){
    _rd->EngageAll();
}
