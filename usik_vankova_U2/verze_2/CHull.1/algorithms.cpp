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

double Algorithms::getAngle(QPointF &q1, QPointF &q2, QPointF &q3, QPointF &q4)
{
    double ux = q2.x()-q1.x();
    double uy = q2.y()-q1.y();

    double vx = q4.x()-q3.x();
    double vy = q4.y()-q3.y();

    double angle = fabs(acos((ux*vx + uy*vy)/(sqrt(ux*ux + uy*uy)*sqrt(vx*vx + vy*vy))));
    return angle;
}

int Algorithms::getPointLinePosition(QPointF &q,QPointF &p1,QPointF &p2)
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

    double TOL = 1e-6;
    //Point in the left half plane
    if (t > TOL)
        return 1;
    if (t < -TOL)
        return 0;
    return -1;
}

double Algorithms::getPointLineDist(QPointF &a,QPointF &p1,QPointF &p2)
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
double Algorithms::distancePoints(QPointF &p1, QPointF &p2)
{
    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();
    double d = sqrt(dx*dx + dy*dy);
    return d;
}

QPolygonF Algorithms::jarvis(std::vector<QPointF> &points)
{
    //Create Convex Hull using Jarvis Scan Algoritms
    QPolygonF ch;

    //1 - Sort points by Y
    std::sort(points.begin(), points.end(), sortByY());

    //2 - Create q
    QPointF q=points[0];

    //3 - Create r
    QPointF r(0,q.y());

    //4 - Add q into Convex Hull
    ch.push_back(q);

    //5 - Initialize pj, pjj
    QPointF pj = q; //pivot
    QPointF pjj = r;

    //Find all points of Convex Hull
    do {
        //Initialize i_max, om_max
        int i_max = -1;
        double o_max = 0;
        double TOL = 1e-6;
        //Find suitable point maximazing angle omega
        for (unsigned int i = 0; i < points.size(); i++)
        {
            //Compute omega
            double omega = getAngle(pj, pjj, pj, points[i]);

            //Actualize maximum
            if((omega - o_max) >= TOL)
            {
                o_max = omega;
                i_max = i;
            }
            else if (fabs(omega - o_max) < TOL)
            {
                double distance_i = distancePoints(pj, points[i]);
                double distance_imax = distancePoints(pj, points[i_max]);
                if (distance_i > distance_imax)
                {
                    o_max = omega;
                    i_max = i;
                }
            }
        }

        //Add point to Convex Hull
        ch.push_back(points[i_max]);

        //Change index
        pjj = pj;
        pj = points[i_max];

    } while((pj != q));

    QPolygonF fix_ch = fixPolygon(ch);
    return fix_ch;

}

QPolygonF Algorithms::qhull(std::vector<QPointF> &points)
{
    //Create Convex Hull using QHull Algorithm (Global procedure)
    QPolygonF ch;
    std::vector<QPointF> upoints, lpoints;

    //Sort points according to x coordinate
    std::sort(points.begin(), points.end(), sortByX());

    //Create q1, q3
    QPointF q1 = points[0];
    QPointF q3 = points.back();

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

    QPolygonF fix_ch = fixPolygon(ch);
    return fix_ch;
}

QPolygonF Algorithms::graham(std::vector<QPointF> &points)
{
    //Create Convex Hull using Graham Algorithm
    QPolygonF ch;
    std::vector<Angle> angles;


    //Sort points according to y coordinate
    std::sort(points.begin(), points.end(), sortByY());


    //Find pivot with min y - solve non singular situation
    unsigned int i_min = 0;
    for (unsigned int i = 1; i <points.size(); i++)
    {
        if(points[0].y() == points[i].y())
        {
                i_min = i;
        }
    }

    QPointF q = points[i_min];
    ch.push_back(q);

    //Create supporting point s
    std::sort(points.begin(), points.end(), sortByX());
    QPointF s(points[0].x(), q.y());

    //Calculate angle and distance between axe x and i-point
    Angle pad;

    for(unsigned int i = 0; i < points.size(); i++)
    {
        //Set i-point
        pad.point.setX(points[i].x());
        pad.point.setY(points[i].y());

        if(q == points[i])
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

    //To save star shaped polygon
    QPolygonF star;

    angles.push_back(angles[angles.size()]);

    star.push_back(angles[0].point);


    //Solve singularity - points with same angle and different distance
    double help_angel = 0;
    double help_dist = 0;
    for(unsigned int i = 0; i < angles.size(); i++)
    {
        double TOL = 1.0e-6;
        if(fabs(angles[i].angle - help_angel) < TOL) //If angle is the same
        {
            if(angles[i].dist > help_dist) //If distance of new point is bigger, new point win and go to new cycle with this point
            {
                help_dist = angles[i].dist; //Move to next point
                help_angel = angles[i].angle; //Move to next point
            }
        }
        else
        {
            help_dist = angles[i].dist; //Move to next point
            help_angel = angles[i].angle; //Move to next point
            star.push_back(angles[i-1].point); //Save point to star-shaped polygon
        }
    }

    ch.push_back(star[1]);  //First point with smallest angle, after pivot

    //Make convex hull from non-convex star-shape
    for (int i = 2; i < star.size();)
    {
            if (getPointLinePosition(ch[ch.size()-1], ch[ch.size()-2], star[i]) == 0)
            {
                ch.pop_back(); //Give avay non-convex point, dont move to next i (dont do i++), because point i+1 move to i position so we need to use for cyclus again for the same i
            }
            else
            {
                ch.push_back(star[i]);
                i++;
            }
    }

    QPolygonF fix_ch = fixPolygon(ch);
    return fix_ch;
}


QPolygonF Algorithms::sweepLine(std::vector<QPointF> &points)
{
    //Create Convex Hull using Sweep Line Algorithm
    QPolygonF ch;

    //Sort points by X
    std::sort(points.begin(),points.end(), sortByX());

    //Solve duplicit points - find just non duplicit points
    std::vector<QPointF> nonDuplicit;
    for(unsigned int i =0; i<points.size() - 1; i++)
    {
        if((points[i].x()!=points[i+1].x()) || (points[i].y()!=points[i+1].y())) //if coord. x are not the same or y are not the same its not the same point
        {
                nonDuplicit.push_back(points[i]);
        }
    }
    //Last point
    nonDuplicit.push_back(points[points.size() - 1]);
    points = nonDuplicit; //save to points




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

    QPolygonF fix_ch = fixPolygon(ch);
    return fix_ch;
}

void Algorithms::qh(int s, int e, std::vector<QPointF> &points, QPolygonF &ch)
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

 QPolygonF Algorithms::fixPolygon(QPolygonF &ch)
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


