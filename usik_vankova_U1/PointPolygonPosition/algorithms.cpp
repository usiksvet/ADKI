#include "algorithms.h"
#include <math.h>

Algorithms::Algorithms()
{

}

int Algorithms::getPointLinePosition(QPointF &q, QPointF &p1, QPointF &p2)
{
    //Tolerance
    double TOL = 0.4;

    //Point on the edge of polygon
    double d12 = distancePoints(p1, p2);    //distance of 2 polygon vertex
    double d1q = distancePoints(p1, q); //distance point q from first vertex
    double d2q = distancePoints(p2, q); //distance point q from second vertex
    if (fabs(d12 - (d1q+d2q)) < TOL) //if point near edge
        return 2;

    //Point on the vertex of polygon
    if (d1q < TOL)
        return 2;
    if (d2q < TOL)
        return 2;

    //Get point-line position
    double ux = p2.x() - p1.x();
    double uy = p2.y() - p1.y();

    double vx = q.x() - p1.x();
    double vy = q.y() - p1.y();

    //Determinant
    double t = ux*vy-uy*vx;

    //Determinant test
    //Point in the left halfplane
    if (t > 0)
        return 1;
    //Point in the right halfplane
    if (t < 0)
        return 0;

    //Error
    return -1;
}

double Algorithms::getAngle(QPointF &q1, QPointF &q2, QPointF &q3, QPointF &q4)
{
    double ux = q2.x() -  q1.x();
    double uy = q2.y() - q1.y();

    double vx = q4.x() - q3.x();
    double vy = q4.y() - q3.y();

    double angle = acos((ux*vx + uy*vy)/(sqrt(ux*ux + uy*uy)*sqrt(vx*vx + vy*vy)));
    return angle;
}


int Algorithms::getPositionWinding(QPointF &q, QPolygonF &pol)
{
    //Position of a point and polygon: Winding Algorithm
    //q inside P retur 1
    //q outside P return 0

    double Omega = 0.0;

    //Set tolerance
    const double eps = 1.0e-6;

    //Amount of polygon vertices
    const int n = pol.size();

    //Process all vertices of the polygon
    for (int i = 0; i < n; i++)
    {
        //Get angle omega
        double om = getAngle(pol[i], q, pol[(i+1)%n], q);

        //Get orientation of q and pol[i], pol[i+1]
        int orientation = getPointLinePosition(q, pol[i], pol[(i+1)%n]);
        if (orientation == 2)
            return 1;

        //Point in the left half plane
        else if (orientation == 1)
            Omega += om;

        //Point in the right half plane
        else
            Omega -= om;
    }

    //Point q inside polygon
    if (fabs(fabs(Omega) - 2*M_PI) <= eps)
        return 1;

    //Point q outside polygon
    return 0;

}

int Algorithms::getPositionRay(QPointF &q, QPolygonF &pol)
{
    //Position of a point and polygon: Ray Crossing Algorithm
    //q inside P return 1
    //q outside P return 0

    //Amount of intersections
    int k = 0;

    //Amount of polygon vertices
    int n = pol.size();

    //Process all vertices of the polygon
    for (int i = 1; i < n+1; i++)
    {
        //Compute xi, yi, xii, yii
        double xir = pol[i%n].x() - q.x();
        double yir = pol[i%n].y() - q.y();

        double xiir = pol[i-1].x() - q.x();
        double yiir = pol[i-1].y() - q.y();

        //Point lies on the edge or vertex
        int pos = getPointLinePosition(q, pol[i%n], pol[(i+1)%n]);
        if(pos == 2){return 1;}

        //Does segment (pi-1, pi) intersect ray
        if (((yir > 0) && (yiir <= 0)) || ((yiir > 0) && (yir <= 0)))
        {
            // Compute x coordinate of intersection
            double xm = (xir*yiir - xiir*yir)/(yir - yiir);

            // Point q in the right halfplane
            if (xm > 0)
                k += 1;
        }
    }

    //Number of intersections
    return k%2;
}

double Algorithms::distancePoints(QPointF &p, QPointF &q)
{
    double dx = q.x() - p.x();
    double dy = q.y() - p.y();
    double d = sqrt(dx*dx + dy*dy);
    return d;
}
