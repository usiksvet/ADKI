#ifndef UNIQUEPOINTS_H
#define UNIQUEPOINTS_H

#include <QtGui>

class uniquePoints
{
public:
    uniquePoints(){};

    //Sorter by unique point value
    bool operator () (QPoint &p1, QPoint &p2)
    {
        double tol = 0.001;
        if ((abs(p1.x() - p2.x()) < tol) && (abs(p1.y() - p2.y()) < tol))
        {
            return true;
        }
        return false;
    }
};

#endif // UNIQUEPOINTS_H
