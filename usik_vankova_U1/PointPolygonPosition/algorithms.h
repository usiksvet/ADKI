#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <QPointF>
#include <QPolygonF>

class Algorithms
{
public:
    Algorithms();
    int getPointLinePosition(QPointF &q, QPointF &p1, QPointF &p2);
    double getAngle(QPointF &q1, QPointF &q2, QPointF &q3, QPointF &q4);
    int getPositionWinding(QPointF &q, QPolygonF &pol);
    int getPositionRay(QPointF &q, QPolygonF &pol);
    double distancePoints(QPointF &p, QPointF &q);
};

#endif // ALGORITHMS_H
