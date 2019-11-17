#include "stick.h"

Stick::Stick(CenterCircle *centerCircle) : mDraw(false), mAngle(90)
{
    mCircle = new CenterCircle;
    mCircle->setDiameter(centerCircle->diameter() / 10);
    mCircle->setX(centerCircle->x() * 2 - mCircle->diameter() / 2);
    mCircle->setY(centerCircle->x() * 4 - centerCircle->x() / 4);

    mLine = new QLine;
    mLine->setP1(QPoint(mCircle->x() + mCircle->diameter() / 2, mCircle->y() + mCircle->diameter() / 2));
    mLine->setP2(QPoint(centerCircle->x() * 2, centerCircle->y() * 2));
}

Stick::~Stick()
{
    delete mLine;
    delete mCircle;
}

QLine* Stick::line()
{
    return mLine;
}

CenterCircle* Stick::circle()
{
    return mCircle;
}

bool Stick::draw() const
{
    return mDraw;
}

void Stick::setDraw()
{
    mDraw = true;
}

void Stick::setAngle(int angle)
{
    mAngle = angle;
}

int Stick::angle() const
{
    return mAngle;
}
