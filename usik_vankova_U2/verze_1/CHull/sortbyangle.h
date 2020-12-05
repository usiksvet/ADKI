#ifndef SORTBYANGLE_H
#define SORTBYANGLE_H
#include "algorithms.h"


class sortByAngle
{
public:

    bool operator()(Angle &t1, Angle &t2)
    {
        //Tolerance
        double eps = 10e-12;

        // If difference between two angles is very small, sort according to distance
        if(fabs(t1.angle-t2.angle) < eps)
        {
            if(t1.dist < t2.dist)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        else if(t1.angle < t2.angle)
        {
            return 1;
        }

        else
        {
            return 0;
        }
    }

};

#endif // SORTBYANGLE_H
