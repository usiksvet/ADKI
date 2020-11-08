#include "algorithms.h"
#include "sortbyy.h"
#include "sortbyx.h"
#include "sortbyangle.h"
#include "uniquepoints.h"
#include "qdebug.h"
#include <cmath>

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

int Algorithms::getPointLinePosition(QPoint &q,QPoint &p1,QPoint &p2)
{
    //Analyze point and line position
    //1 point in the left half plane
    //0 point in the right half plane
    //-1 point on the line
    double ux = p2.x() - p1.x();
    double uy = p2.y() - p1.y();

    double vx = q.x() - p1.x();
    double vy = q.y() - p1.y();

    double t = ux * vy - uy * vx;

    //Point in the left half plane
    if (t>0)
        return 1;
    if (t<0)
        return 0;
    return -1;
}

double Algorithms::getPointLineDist(QPoint &a,QPoint &p1,QPoint &p2)
{
    //Compute distance of point a from line p(p1, p2)
    double numerator = a.x()* (p1.y() - p2.y()) + p1.x()*(p2.y() - a.y()) +
                      p2.x()*(a.y() - p1.y());

    //Coordinate differences
    double dx = p1.x() - p2.x();
    double dy = p1.y() - p2.y();

    //Point and line distance
    return fabs(numerator)/sqrt(dx*dx + dy*dy);
}
double Algorithms::distancePoints(QPoint &p1, QPoint &p2)
{
    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();
    double d = sqrt(dx*dx + dy*dy);
    return d;
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

    QPolygon fix_ch = fixPolygon(ch);
    return fix_ch;

}

QPolygon Algorithms::qhull(std::vector<QPoint> &points)
{
    //Create Convex Hull using QHull Algorithm (Global procedure)
    QPolygon ch;
    std::vector<QPoint> upoints, lpoints;

    //Sort points according to x coordinate
    std::sort(points.begin(), points.end(), sortByX());

    //Create q1, q3
    QPoint q1 = points[0];
    QPoint q3 = points.back();

    //Add q1, q3 to upoints/lpoints
    upoints.push_back(q1);
    upoints.push_back(q3);
    lpoints.push_back(q1);
    lpoints.push_back(q3);

    //Split points to upoints/lpoints
    for (unsigned int i = 0; i < points.size(); i++)
    {
        //Add point to upoints
        if (getPointLinePosition(points[i], q1,q3) == 1)
            upoints.push_back(points[i]);

        //Otherwise, add point to lpoints
        else if(getPointLinePosition(points[i], q1,q3) == 0)
            lpoints.push_back(points[i]);
    }

    //Add q3 to CH
    ch.push_back(q3);

    //Recursion for upoints
    qh(1, 0, upoints,ch);

    //Add q1 to CH
    ch.push_back(q1);

    //Recursion for lpoints
    qh(0, 1, lpoints,ch);

    QPolygon fix_ch = fixPolygon(ch);
    return fix_ch;
}

QPolygon Algorithms::graham(std::vector<QPoint> &points)
{
    //Create Convex Hull using Graham Algorithm
    QPolygon ch;
    std::vector<Angle> angles;


    //Sort points according to y coordinate
    std::sort(points.begin(), points.end(), sortByY());

    //Find pivot with min x
    unsigned int i_min = 0;
    for (unsigned int i = 1; i <points.size(); i++)
    {
        if(points[0].y() == points[i].y())
        {
            if(points[i].x() < points[0].x())
            {
                i_min = i;
            }
        }
    }

    QPoint q = points[i_min];
    ch.push_back(q);

    //Create supporting point s
    std::sort(points.begin(), points.end(), sortByX());
    QPoint s(points[0].x(), q.y());

    //Calculate angle and distance between axe x and i-point
    Angle pad;

    for(unsigned int i = 0; i < points.size(); i++)
    {
        //Set i-point
        pad.point.setX(points[i].x());
        pad.point.setY(points[i].y());

        if(points[i] == q)
        {
            pad.angle = 0;
            pad.dist = 0;
        }
        else
        {
            pad.angle = getAngle(q, s, q, points[i]);
            pad.dist = distancePoints(q, points[i]);
        }

        angles.push_back(pad);
    }

    //Firstly sort by angle, if anles equal sort by dist
    std::sort(angles.begin(), angles.end(), sortByAngle());

//    QPolygon polAngles;
//    polAngles.push_back(angles[0].point);
//    polAngles.push_back(angles[1].point);

    ch.push_back(angles[1].point);
    for (unsigned int i = 2; i < angles.size(); i++)
    {
        if (getPointLinePosition(ch[ch.size()-1], ch[ch.size()-2], angles[i].point) == 0)
        {
            ch.pop_back();
        }
        else
        {
            ch.push_back(angles[i].point);
        }
    }

    QPolygon fix_ch = fixPolygon(ch);
    return fix_ch;
}


QPolygon Algorithms::sweepLine(std::vector<QPoint> &points)
{
    //Create Convex Hull using Sweep Line Algorithm
    QPolygon ch;

    //Sort points by X
    std::sort(points.begin(),points.end(), sortByX());

    //Create lists of predecessors and successors
    int m = points.size();
    std::vector<int> p(m), n(m);

    //Create initial approximation
    n[0] = 1;
    n[1] = 0;
    p[0] = 1;
    p[1] = 0;

    //Process all points aacording to x coordinate
    for (int i = 2; i < m; i++)
    {
        //Point in the upper half plane
        if(points[i].y() >= points[i-1].y())
        {
            //Link i with predecessor and successor
            p[i] = i-1;
            n[i] = n[i-1];
        }

        //Point in the lower half plane
        else
        {
            //Link i with predecessor and successor
            p[i] = p[i-1];
            n[i] = i - 1;
        }

        //Remaining links (analogous for both cases)
        p[n[i]] = i;
        n[p[i]] = i;

        //Correct upper tangent
        while(getPointLinePosition(points[n[n[i]]], points[i], points[n[i]])== 0)
        {
            p[n[n[i]]] = i;
            n[i] = n[n[i]];
        }

        //Correct lower tangent
        while(getPointLinePosition(points[p[p[i]]], points[i], points[p[i]]) == 1)
        {
            n[p[p[i]]] = i;
            p[i] = p[p[i]];
        }
    }

    //Conversion of successors to vector
    //Add point with minimum x coordinate
    ch.push_back(points[0]);

    //Get index of its successor
    int index=n[0];

    //Repeat until first point is found
    while(index!=0)
    {
        //Add to ch
        ch.push_back(points[index]);

        //Get successor
        index = n[index];
     }

    QPolygon fix_ch = fixPolygon(ch);
    return fix_ch;
}

void Algorithms::qh(int s, int e, std::vector<QPoint> &points, QPolygon &ch)
{
    //Create Convex Hull using QHull Algorithm (Local procedure)
    int i_max = -1;
    double d_max = 0;

    //Browse all points
    for (unsigned int i = 2; i < points.size(); i++)
    {
        //Point in the right halfplane
        if (getPointLinePosition(points[i], points[s], points[e]) == 0)
        {
            double distance = getPointLineDist(points[i], points[s], points[e]);

            //Actualize i_max, d_max
            if (distance > d_max)
            {
                d_max=distance;
                i_max=i;
            }
        }
    }

    //Suitable point has been found
    if(i_max!=-1)
    {
        //Process first segment using recursion
        qh(s, i_max, points, ch);

        //Add furthest p to CH
        ch.push_back(points[i_max]);

        //Process second segment using recursion
        qh(i_max, e, points, ch);
    }
}

 QPolygon Algorithms::fixPolygon(QPolygon &ch)
 {
     //Sort by unique point value
     auto end = std::unique(ch.begin(), ch.end(), uniquePoints());

     //Delite identical points
     ch.erase(end, ch.end());

     //Delete points on the same line
     for (int i = 0; i < (ch.size() - 2); i++)
     {
         if (getPointLinePosition(ch[i+2], ch[i], ch[i+1]) == -1)
         {
             ch.remove(i+1);
             i--;
         }
     }

     return ch;
 }


