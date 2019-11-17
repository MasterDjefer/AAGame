#ifndef STICK_H
#define STICK_H
#include "centercircle.h"
#include <QLine>


class Stick
{
private:
    QLine *mLine;
    CenterCircle *mCircle;
    bool mDraw;
    int mAngle;

public:
    Stick(CenterCircle *centerCircle);
    ~Stick();

    QLine* line();
    CenterCircle* circle();
    bool draw() const;
    void setDraw();
    void setAngle(int angle);
    int angle() const;
};

#endif // STICK_H
