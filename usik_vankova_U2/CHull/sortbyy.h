#ifndef SORTBYY_H
#define SORTBYY_H

#include <QtGui>

class sortByY
{
public:
    sortByY(){};

    //Sorter by y-coordinate
    bool operator () (QPoint &p1, QPoint &p2)
    {
        return p1.y() < p2.y();
    }
};

#endif // SORTBYY_H
