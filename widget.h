#ifndef WIDGET_H
#define WIDGET_H

#include "stick.h"
#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <qmath.h>

class Widget : public QWidget
{
    Q_OBJECT

private:
    CenterCircle *mCenterCircle;
    QVector<Stick*> mVectorSticks;
    QTimer *mTimer;

public:
    Widget();
    ~Widget();

private:
    virtual void paintEvent(QPaintEvent *e);
    virtual void keyPressEvent(QKeyEvent *e);

private slots:
    void onTimeOut();
};

#endif // WIDGET_H
