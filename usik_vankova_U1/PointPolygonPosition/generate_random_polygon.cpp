#include <iostream>
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <algorithms.h>
#include <math.h>

class GenerateRandomPolygon //Class for generating polygons
{
  public:
    QVector<QPolygonF> generateRandomPolygons() //Method for generating polygons
    {
        QVector<QPolygonF> polygony; //Inicialize output variable
        int m;
        int n;
        for (int kv = 1; kv < 5; kv++) //4 quadrants, in each the polygons are generated
        {
            int number_of_polygons  = rand() % 6 + 1; //Get random number of polygons in quadrant from 1 to 6
            if (kv == 1)
            {
                m = rand() % 220; //Move y coordinates of polygon points
                n = rand() % 180; //Move x coordinates of polygon points
                for (int j = 0; j < number_of_polygons; j++)
                {
                    int polygon_type = rand() % 3; //Choose number of three polygon types
                    if (j == 0)
                    {
                        /*If type is 2, there are minus y coordinates and it might be out of the canvas or in other quadrant
                        and function if give theese wrong results away */
                        if (polygon_type!= 2)
                        {
                        polygony.push_back(generateRandomPolygon(m, n, polygon_type)); //There come result polygon
                        }
                        else if (m > 40)
                        {
                        polygony.push_back(generateRandomPolygon(m, n, polygon_type)); //There come result polygon
                        }
                    }
                    else
                    {
                        if (polygon_type == 0) //Different movement m, n for different types of polygon
                        {
                            n -= 80;
                            m += 40;
                        }
                        if (polygon_type == 1)
                        {
                            n -= 40;
                            m += 40;
                        }
                        if (polygon_type == 2)
                        {
                            n += 40;
                            m += 120;
                        }
                        /*Give away results, where polygon might be out of canvas or in other quadrant*/
                        if (m > 0 && m < 220 && n > 0 && n < 180 && (polygon_type != 2))
                        {
                            polygony.push_back(generateRandomPolygon(m, n, polygon_type)); //There come result polygon
                        }
                        if (m > 40 && m < 260 && n > 0 && n < 180 && (polygon_type == 2))
                        {
                            polygony.push_back(generateRandomPolygon(m, n, polygon_type)); //There come result polygon
                        }
                    }
                }
            }
            //Next is it the same for other quadrants
            if (kv == 2){
                m = rand() % 220;
                n = rand() % 180 + 300;
                for (int j = 0; j < number_of_polygons; j++)
                {
                    int polygon_type = rand() % 3;
                    if (j == 0)
                    {
                        if (polygon_type!= 2)
                        {
                        polygony.push_back(generateRandomPolygon(m, n, polygon_type));
                        }
                        else if (m > 40)
                        {
                        polygony.push_back(generateRandomPolygon(m, n, polygon_type));
                        }
                    }
                    else {
                        if (polygon_type == 0)
                        {
                            n -= 80;
                            m += 40;
                        }
                        if (polygon_type == 1)
                        {
                            n -= 40;
                            m += 40;
                        }
                        if (polygon_type == 2)
                        {
                            n += 40;
                            m += 120;
                        }
                        if (m > 0 && m < 220 && n > 300 && n < 480 && (polygon_type != 2))
                        {
                            polygony.push_back(generateRandomPolygon(m, n, polygon_type));
                        }
                        if (m > 40 && m < 260 && n > 300 && n < 480 && (polygon_type == 2))
                        {
                            polygony.push_back(generateRandomPolygon(m, n, polygon_type));
                        }
                    }
                }
            }
            if (kv == 3){
                m = rand() % 220 + 300;
                n = rand() % 180;
                for (int j = 0; j < number_of_polygons; j++)
                {
                    int polygon_type = rand() % 3;
                    if (j == 0)
                    {
                        if (polygon_type!= 2)
                        {
                        polygony.push_back(generateRandomPolygon(m, n, polygon_type));
                        }
                        else if (m > 340)
                        {
                        polygony.push_back(generateRandomPolygon(m, n, polygon_type));
                        }
                    }
                    else
                    {
                        if (polygon_type == 0)
                        {
                            n -= 80;
                            m += 40;
                        }
                        if (polygon_type == 1)
                        {
                            n -= 40;
                            m += 40;
                        }
                        if (polygon_type == 2)
                        {
                            n += 40;
                            m += 120;
                        }
                        if (m > 300 && m < 520 && n > 0 && n < 180 && (polygon_type != 2))
                        {
                            polygony.push_back(generateRandomPolygon(m, n, polygon_type));
                        }
                        if (m > 340 && m < 560 && n > 0 && n < 180 && (polygon_type == 2))
                        {
                            polygony.push_back(generateRandomPolygon(m, n, polygon_type));
                        }
                    }
                }
            }
            if (kv == 4)
            {
                m = rand() % 220 + 300;
                n = rand() % 180 + 300;
                for (int j = 0; j< number_of_polygons; j++)
                {
                    int polygon_type = rand() % 3;
                    if (j == 0)
                    {
                        if (polygon_type!= 2)
                        {
                        polygony.push_back(generateRandomPolygon(m, n, polygon_type));
                        }
                        else if (m > 340)
                        {
                        polygony.push_back(generateRandomPolygon(m, n, polygon_type));
                        }
                    }
                    else
                    {
                        if (polygon_type == 0)
                        {
                            n -= 80;
                            m += 40;
                        }
                        if (polygon_type == 1)
                        {
                            n -= 40;
                            m += 40;
                        }
                        if (polygon_type == 2)
                        {
                            n += 40;
                            m += 120;
                        }
                        if (m > 300 && m < 520 && n > 300 && n < 480 && (polygon_type != 2))
                        {
                            polygony.push_back(generateRandomPolygon(m, n, polygon_type));
                        }
                        if (m > 340 && m < 560 && n > 300 && n < 480 && (polygon_type == 2))
                        {
                            polygony.push_back(generateRandomPolygon(m, n, polygon_type));
                        }
                    }
                }
            }
        }
        return polygony; //Return all polygons
    };

  private:
    QPolygonF generateRandomPolygon(int &m, int &n, int &o) //We generate random type of polygon, using this method
    {
        QVector<QPointF> pointy;
        if (o == 0) //If its type 0, count this points and save to pointy
        {
            QPointF point1(0+n, 0+m);
            QPointF point2(120+n, 0+m);
            QPointF point3(120+n, 40+m);
            QPointF point4(80+n, 40+m);
            QPointF point5(80+n, 80+m);
            QPointF point6(40+n, 80+m);
            QPointF point7(40+n, 40+m);
            QPointF point8(0+n, 40+m);
            pointy.push_back(point1);
            pointy.push_back(point2);
            pointy.push_back(point3);
            pointy.push_back(point4);
            pointy.push_back(point5);
            pointy.push_back(point6);
            pointy.push_back(point7);
            pointy.push_back(point8);
        }
        if (o == 1)
        {
            QPointF point1(0+n, 0+m);
            QPointF point2(80+n, 0+m);
            QPointF point3(80+n, 40+m);
            QPointF point4(120+n, 40+m);
            QPointF point5(120+n, 80+m);
            QPointF point6(40+n, 80+m);
            QPointF point7(40+n, 40+m);
            QPointF point8(0+n, 40+m);
            pointy.push_back(point1);
            pointy.push_back(point2);
            pointy.push_back(point3);
            pointy.push_back(point4);
            pointy.push_back(point5);
            pointy.push_back(point6);
            pointy.push_back(point7);
            pointy.push_back(point8);
        }
        if (o == 2)
        {
            QPointF point1(0+n, 0+m);
            QPointF point2(80+n, 0+m);
            QPointF point3(80+n, -40+m);
            QPointF point4(120+n, -40+m);
            QPointF point5(120+n, 40+m);
            QPointF point6(0+n, 40+m);
            pointy.push_back(point1);
            pointy.push_back(point2);
            pointy.push_back(point3);
            pointy.push_back(point4);
            pointy.push_back(point5);
            pointy.push_back(point6);
        }
        QPolygonF polygon(pointy); //Save points like polygon
        return polygon; //Return 1 polygon
    }
};
