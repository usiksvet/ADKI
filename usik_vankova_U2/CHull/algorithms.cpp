#include "algorithms.h"
#include "sortbyy.h"
#include "qdebug.h"

Algorithms::Algorithms()
{

}

double Algorithms::getAngle(QPoint &q1, QPoint &q2, QPoint &q3, QPoint &q4)
{
    double ux = q2.x()-q1.x();
    double uy = q2.y()-q1.y();

    double vx = q4.x()-q3.x();
    double vy = q4.y()-q3.y();

    double angle = acos((ux*vx + uy*vy)/(sqrt(ux*ux + uy*uy)*sqrt(vx*vx + vy*vy)));
    return angle;
}

QPolygon Algorithms::jarvis(std::vector<QPoint> &points)
{
    //Create Convex Hull using Jarvis Scan Algoritms
    QPolygon ch;

    //1 - Sort points by Y
    std::sort(points.begin(), points.end(), sortByY());

    //2 - Create q
    QPoint q=points[0];

    //3 - Create r
    QPoint r(0,q.y());

    //4 - Add q into Convex Hull
    ch.push_back(q);

    //5 - Initialize pj, pjj
    QPoint pj = q; //pivot
    QPoint pjj = r;

    //Find all points of Convex Hull
    do {
        //Initialize i_max, om_max
        int i_max = -1;
        double o_max = 0;

        //Find suitable point maximazing angle omega
        for (unsigned int i = 0; i < points.size(); i++)
        {

            //Compute omega
            double omega = getAngle(pj, pjj, pj, points[i]);

            //Actualize maximum
            if(omega > o_max)
            {
                o_max = omega;
                i_max = i;
            }
        }

        //Add point to Convex Hull
        ch.push_back(points[i_max]);

        //Change index
        pjj = pj;
        pj = points[i_max];

    } while((pj != q));

    return ch;

}
