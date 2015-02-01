#ifndef CMAKEQT_H
#define CMAKEQT_H

#include "ui_CMakeQt.h"
#include "RoyDriver.hpp"
//#include "servoDriver.hpp"

#include <QtGui>
#include <QSlider>
#include <QLCDNumber>

class CMakeQt : public QDialog
{
    Q_OBJECT

public:
    CMakeQt(QWidget *parent = 0);

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

};

#endif // CMAKEQT_H
