#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QtGui>
#include <vector>

struct Angle
{
    QPointF point; //p
    double angle; //a
    double dist;  //d
};

class Algorithms
{
public:
    Algorithms();
    double getAngle(QPointF &q1, QPointF &q2, QPointF &q3, QPointF &q4);
    int getPointLinePosition(QPointF &q, QPointF &p1, QPointF &p2);
    double getPointLineDist(QPointF &a, QPointF &p1, QPointF &p2);
    double distancePoints(QPointF &p1, QPointF &p2);

    QPolygonF jarvis(std::vector<QPointF> &points);
    QPolygonF qhull(std::vector<QPointF> &points);
    QPolygonF graham(std::vector<QPointF> &points);
    QPolygonF sweepLine(std::vector<QPointF> &points);
    QPolygonF fixPolygon(QPolygonF &ch);

    void qh(int s, int e, std::vector<QPointF> &points, QPolygonF &ch);
};

#endif // ALGORITHMS_H
