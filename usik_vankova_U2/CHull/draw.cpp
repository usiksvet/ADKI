#include "draw.h"
#include "qdebug.h"
#include <cmath>


Draw::Draw(QWidget *parent) : QWidget(parent)
{

}

void Draw::mousePressEvent(QMouseEvent *e)
{
    //Get coordinates
    int x = e->x();
    int y = e->y();

    //Add point to the list
    QPoint q(x, y); //vytvorim bod
    points.push_back(q); //pridam do seznamu bodu

    //Repaint screen
    repaint();

}

void Draw::paintEvent(QPaintEvent *e)
{
    Q_UNUSED (e);
    //Start draw
    QPainter qp(this);
    qp.begin (this);

    //Draw points
    int r = 5;
    for(unsigned int i = 0; i < points.size(); i++)
    {
        qp.drawEllipse(points[i].x() - r, points[i].y() - r, 2 * r, 2 * r);
    }

    //Draw polygon (draw CH)
    qp.drawPolygon(ch);

    //End draw
    qp.end();

}


void Draw::generatePoints(int num_points, int w, int h, int type)
{
    QPoint point;

    points.clear();

    //Generate points randomly
    if (type == 0)
    {
        for(int i = 0; i < num_points; i++)
        {
            point.setX(rand()%w); //generate random value from 0 to w
            point.setY(rand()%h); //generate random value from 0 to h
            points.push_back(point);
        }
    }

    //Generate points on square grid
    if (type == 1)
    {
        //Square edge
        int a = sqrt(num_points);

        for (int x = 0; x < a; x++)
        {
            for (int y = 0; y < a; y++)
            {
                point.setX(x*20+10);
                point.setY(y*20+10);
//                point.setX(x*20+10); //nastaveni odsazeni, pouzij pro PrtSc do TZ!!!
//                point.setY(y*20+10);
                points.push_back(point);
            }
        }
    }

    //Generate points in circle
    if (type == 2)
    {
        //Find minimal canvas size for circle radius
        int min_size;
        if (w > h)
        {
            min_size = h;
        }
        else
        {
            min_size = w;
        }

        //Circle center in the middle of canvas
        QPoint centr(w/2, h/2);

        //Circle radius
        int delta = 10;
        double radius = (min_size - delta)/2;

        // Relative point angle
        double fi = (2*M_PI)/num_points;

        //Generate points on circle
        for(int i = 0; i < num_points; i++)
        {
            point.setX(centr.x() + static_cast<int>(radius*cos(i*fi))); //static_cast<int> return int from any data type
            point.setY(centr.y() + static_cast<int>(radius*sin(i*fi)));
            points.push_back(point);
        }

    }
        repaint();

}
