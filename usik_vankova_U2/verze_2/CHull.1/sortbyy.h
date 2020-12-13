#ifndef SORTBYY_H
#define SORTBYY_H

#include <QtGui>

class sortByY
{
public:
    sortByY(){};

    //Sorter by y-coordinate
    bool operator () (QPointF &p1, QPointF &p2)
    {
        return p1.y() < p2.y() || ((p1.y() == p2.y()) && (p1.x() < p2.x()));
    }
};

#endif // SORTBYY_H
