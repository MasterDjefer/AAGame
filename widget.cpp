#include "widget.h"

Widget::Widget()
{
    this->setFixedSize(500, 500);

    const int n = 30;
    mCenterCircle = new CenterCircle(n, this->width());

    for (int i = 0; i < n; ++i)
    {
        mVectorSticks.push_back(new Stick(mCenterCircle));
    }

    mTimer = new QTimer(this);
    QObject::connect(mTimer, &QTimer::timeout, this, &Widget::onTimeOut);
    mTimer->start(10);
}

Widget::~Widget()
{
    delete mCenterCircle;
    delete mTimer;

    while (mVectorSticks.size() > 0)
    {
        Stick *s = mVectorSticks.back();
        delete s;
        mVectorSticks.pop_back();
    }
}

void Widget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.setBrush(QBrush(Qt::black));
    painter.drawEllipse(mCenterCircle->x(), mCenterCircle->y(),
                        mCenterCircle->diameter(), mCenterCircle->diameter());

    for (int i = 0; i < mVectorSticks.size(); ++i)
    {
        painter.setPen(QPen(Qt::black, 1));
        painter.drawEllipse(mVectorSticks.at(i)->circle()->x(), mVectorSticks.at(i)->circle()->y(),
                    mVectorSticks.at(i)->circle()->diameter(), mVectorSticks.at(i)->circle()->diameter());

        if (mVectorSticks.at(i)->draw())
        {
            painter.drawLine(*mVectorSticks.at(i)->line());
        }

        painter.setFont(QFont("Times", 30));
        painter.setPen(QPen(Qt::white));
        painter.drawText(mCenterCircle->x() + mCenterCircle->diameter() / 2 - 18,
                         mCenterCircle->y() + mCenterCircle->diameter() / 2 + 12,
                         QString::number(mCenterCircle->number()));
    }
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    static int index = mVectorSticks.size() - 1;
    if (e->key() == Qt::Key_Space && index != -1)
    {
        mVectorSticks.at(index)->setDraw();

        mVectorSticks.at(index)->circle()->setY(this->height() / 4 * 3 + this->height() / 8);
        mVectorSticks.at(index)->line()->setP1(QPoint(mVectorSticks.at(index)->line()->x1(),
                                               this->height() / 4 * 3 + this->height() / 8));

        //if game over(length between points)
        for (int i = 0; i < mVectorSticks.size(); ++i)
        {
            if (i != index && mVectorSticks.at(i)->draw())
            {
                double length = sqrt((mVectorSticks.at(i)->circle()->x() - mVectorSticks.at(index)->circle()->x()) *
                                     (mVectorSticks.at(i)->circle()->x() - mVectorSticks.at(index)->circle()->x()) +
                                     (mVectorSticks.at(i)->circle()->y() - mVectorSticks.at(index)->circle()->y()) *
                                     (mVectorSticks.at(i)->circle()->y() - mVectorSticks.at(index)->circle()->y()));
                if (length - 3 <= (double)(mVectorSticks.at(i)->circle()->diameter()))
                {
                    mTimer->stop();
                    index = 0;
                }
            }
        }

        index--;
        mCenterCircle->incNumber();
    }
    else
        if (e->key() == Qt::Key_P)
        {
            static bool isPause = true;
            if (isPause)
            {
                mTimer->stop();
                isPause = !isPause;
            }
            else
            {
                mTimer->start(10);
                isPause = !isPause;
            }
        }

    this->update();
}

void Widget::onTimeOut()
{
    for (int i = 0; i < mVectorSticks.size(); ++i)
    {
        if (mVectorSticks.at(i)->draw())
        {
            mVectorSticks.at(i)->setAngle(mVectorSticks.at(i)->angle() + 1);
            double rad = (mVectorSticks.at(i)->angle() * M_PI) / 180.0;
            double length = this->height() / 4 * 3 + this->height() / 8 - this->height() / 2;
            int x = mVectorSticks.at(i)->line()->x2() + length * cos(rad);
            int y = mVectorSticks.at(i)->line()->y2() + length * sin(rad);
            mVectorSticks.at(i)->circle()->setX(x - mVectorSticks.at(i)->circle()->diameter() / 2);
            mVectorSticks.at(i)->circle()->setY(y - mVectorSticks.at(i)->circle()->diameter() / 2);

            mVectorSticks.at(i)->line()->setP1(QPoint(x, y));
        }
    }
    this->update();
}
