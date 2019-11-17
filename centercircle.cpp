#include "centercircle.h"

CenterCircle::CenterCircle()
{
}

CenterCircle::CenterCircle(int number, int windowSize) : QPoint(windowSize / 4, windowSize / 4),
                                             mDiameter(windowSize / 2), mNumber(number)
{
}

int CenterCircle::diameter() const
{
    return mDiameter;
}

void CenterCircle::setDiameter(int diameter)
{
    mDiameter = diameter;
}

int CenterCircle::number() const
{
    return mNumber;
}

void CenterCircle::incNumber()
{
    if (mNumber > 0)
        mNumber--;
}
