#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <QtGui>
#include <vector>

class Algorithms
{
public:
    Algorithms();
    double getAngle(QPoint &q1, QPoint &q2, QPoint &q3, QPoint &q4);
    QPolygon jarvis(std::vector<QPoint> &points);
};

#endif // ALGORITHMS_H
