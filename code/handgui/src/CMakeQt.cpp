#include "CMakeQt.h"
#include <phidget21.h>

#include "boost/foreach.hpp"
#include "RoyDriver.hpp"
#include "MotionPaths.hpp"
#include "SignLanguage.hpp"


CMakeQt::CMakeQt(QWidget *parent)
    : QDialog(parent)
{
    m_ui.setupUi(this);
    m_ui.label->setText( "Hand Movement GUI for Roy the Robot, by Lee Redden" );

    // close, pause, resume button
    connect( m_ui.motionButton, SIGNAL(pressed()), this, SLOT(motionButton()) );
    connect( m_ui.pauseButton, SIGNAL(pressed()), this, SLOT(pauseButton()) );
    connect( m_ui.resumeButton, SIGNAL(pressed()), this, SLOT(resumeButton()) );
    connect( m_ui.rockoutButton, SIGNAL(pressed()), this, SLOT(rockoutButton()) );
    connect( m_ui.hangtenButton, SIGNAL(pressed()), this, SLOT(hangtenButton()) );
    connect( m_ui.theBirdButton, SIGNAL(pressed()), this, SLOT(theBirdButton()) );
    connect( m_ui.davinciButton, SIGNAL(pressed()), this, SLOT(davinciButton()) );
    connect( m_ui.peaceButton, SIGNAL(pressed()), this, SLOT(peaceButton()) );
    connect( m_ui.italian123Button, SIGNAL(pressed()), this, SLOT(italian123Button()) );
    connect( m_ui.testButton, SIGNAL(pressed()), this, SLOT(testButton()) );

    connect( m_ui.signButton, SIGNAL(pressed()), this, SLOT(signLanguageButton()) );

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
        _sliders[ii]->setRange(-1000,1000);
        // center the cursor
        _sliders[ii]->setSliderPosition(0);
        _commanded[ii]->display(0);
        // set connection
        connect( _sliders[ii], SIGNAL(sliderMoved(int)), this, SLOT(sliderMoved()) );
    }
}
CMakeQt::~CMakeQt()
{
    delete _rd;
}

void CMakeQt::sliderMoved()
{
    for( int ii = 0; ii < _rd->getNumberOfServos(); ++ii )
    {
        _rd->SetFingerPosition( static_cast<finger>(ii), (double)_sliders[ii]->value()/1000 );
        _commanded[ii]->display( (double)_sliders[ii]->value()/1000 );
        _current[ii]->display( _rd->GetCurrentFinger( static_cast<finger>(ii) ) );
    }
}

// **************ACTIONS*******************
void CMakeQt::executeMotion( std::vector<pose> poses )
{
    //std::vector<pose> poses = returnPositions( actionName_ );
    for( uint ii = 0; ii < poses.size(); ++ii )
    {
        _rd->SetFingerPositions( poses[ii].positions );
        for( int jj = 0; jj < 8; ++jj ) {
            _commanded[jj]->display( poses[ii].positions[jj] );
            _sliders[jj]->setSliderPosition( 1000*poses[ii].positions[jj] );
        }
        QCoreApplication::processEvents();
        usleep( poses[ii].millisecond*1000 );
    }
}

void CMakeQt::testButton() {
    executeMotion( returnPositions("test") );
}

void CMakeQt::italian123Button() {
    executeMotion( returnPositions("italian123") );
}

void CMakeQt::peaceButton() {
    executeMotion( returnPositions("peace") );
}

void CMakeQt::davinciButton() {
    executeMotion( returnPositions("davinci") );
}

void CMakeQt::hangtenButton() {
    executeMotion( returnPositions("hang10") );
}

void CMakeQt::rockoutButton() {
    executeMotion( returnPositions("rock") );
}

void CMakeQt::motionButton() {
    executeMotion( returnPositions("motion") );
}
void CMakeQt::theBirdButton() {
    executeMotion( returnPositions("theBird") );
}

void CMakeQt::signLanguageButton() {
    executeMotion( returnSignLanguagePositions( m_ui.signInput->text().toLower().toStdString(), 1 ) );
}

void CMakeQt::pauseButton(){
    _rd->EngageAll(0);
}

void CMakeQt::resumeButton(){
    _rd->EngageAll();
}
