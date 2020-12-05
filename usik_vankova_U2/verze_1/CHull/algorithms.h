#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QtGui>
#include <vector>

struct Angle
{
    QPoint point; //p
    double angle; //a
    double dist;  //d
};

class Algorithms
{
public:
    Algorithms();
    double getAngle(QPoint &q1, QPoint &q2, QPoint &q3, QPoint &q4);
    int getPointLinePosition(QPoint &q, QPoint &p1, QPoint &p2);
    double getPointLineDist(QPoint &a, QPoint &p1, QPoint &p2);
    double distancePoints(QPoint &p1, QPoint &p2);

    QPolygon jarvis(std::vector<QPoint> &points);
    QPolygon qhull(std::vector<QPoint> &points);
    QPolygon graham(std::vector<QPoint> &points);
    QPolygon sweepLine(std::vector<QPoint> &points);
    QPolygon fixPolygon(QPolygon &ch);

    void qh(int s, int e, std::vector<QPoint> &points, QPolygon &ch);
};

#endif // ALGORITHMS_H
