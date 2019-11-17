#ifndef CENTERCIRCLE_H
#define CENTERCIRCLE_H
#include <QPoint>


class CenterCircle : public QPoint
{
private:
    int mDiameter;
    int mNumber;

public:
    CenterCircle();
    CenterCircle(int number, int windowSize);
    int diameter() const;
    void setDiameter(int diameter);
    int number() const;
    void incNumber();
};

#endif // CENTERCIRCLE_H
