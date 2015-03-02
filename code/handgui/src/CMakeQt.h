#ifndef CMAKEQT_H
#define CMAKEQT_H

#include "ui_CMakeQt.h"
#include "RoyDriver.hpp"
#include "MotionPaths.hpp"

#include <QtGui>
#include <QSlider>
#include <QLCDNumber>

class CMakeQt : public QDialog
{
    Q_OBJECT

public:
    CMakeQt(QWidget *parent = 0);
    ~CMakeQt();

private:
    Ui::CMakeQt m_ui;
    RoyDriver* _rd;

    std::vector< QSlider* > _sliders;
    std::vector< QLCDNumber* > _commanded;
    std::vector< QLCDNumber* > _current;

private slots:
    void sliderMoved();
    void motionButton();
    void pauseButton();
    void resumeButton();
    void rockoutButton();
    void hangtenButton();
    void theBirdButton();
    void davinciButton();
    void peaceButton();
    void italian123Button();
    void testButton();

    void signLanguageButton();

    void executeMotion( std::vector<pose> poses_ );
};

#endif // CMAKEQT_H
