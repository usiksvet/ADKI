#ifndef UNIQUEPOINTS_H
#define UNIQUEPOINTS_H

#include <QtGui>

class uniquePoints
{
public:
    //Sorter by unique point value
    bool operator () (QPointF &p1, QPointF &p2)
    {
        double tol = 1e-6;
        if ((abs(p1.x() - p2.x()) < tol) && (abs(p1.y() - p2.y()) < tol))
        {
            return true;
        }
        return false;
    }
};

#endif // UNIQUEPOINTS_H
