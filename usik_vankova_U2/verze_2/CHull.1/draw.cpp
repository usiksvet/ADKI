#include "draw.h"
#include "qdebug.h"
#include <cmath>
#include <QMessageBox>
#include <QVector>

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
    int r = 3;
    for(unsigned int i = 0; i < points.size(); i++)
    {
        qp.drawEllipse(points[i].x() - r, points[i].y() - r, 2 * r, 2 * r);
    }

    //Draw polygon (draw CH)
    qp.setPen(Qt::red);
    qp.drawPolygon(ch);

    //Draw CH points in different colour
    QPen pen(QBrush(Qt::darkRed), 5);
    qp.setPen(pen);

    for(int i = 0; i < ch.size(); i++)
    {
        qp.drawEllipse(ch[i].x() - r, ch[i].y() - r, 2 * r, 2 * r);
    }

    //End draw
    qp.end();

}


void Draw::generatePoints(int num_points, int w, int h, int type)
{
    QPoint point;
    points.clear();

    if(num_points<=0)
    {
        QMessageBox errorBox;
        errorBox.setText("Warning: Only positive inteeger is allowed as input number of points!");
        errorBox.exec();
    }
    else
    {
        //Generate points randomly
        if (type == 0)
        {
            for(int i = 0; i < num_points; i++)
            {
                point.setX(rand()%(w-20)+10); //generate random value from 10 to w-10 (moved from the edge because of visibility)
                point.setY(rand()%(h-20)+10); //generate random value from 10 to h-10
                points.push_back(point);
            }
        }

        //Generate points on square grid
        if (type == 1)
        {
            if(num_points<4)
            {
                QMessageBox errorBox;
                errorBox.setText("Warning: Square grid need input at least 4 points! ");
                errorBox.exec();
            }
            else
            {
                //Square edge
                int a = sqrt(num_points);

                if (num_points!=a*a)
                {
                    QMessageBox errorBox;
                    errorBox.setText("Warning: Square grid need number of points having inteeger square root. Number will be reduced on nearest smaller number with inteeger square root.");
                    errorBox.exec();
                }

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
        }

        //Generate points in circle
        if (type == 2)
        {
            if(num_points<3)
            {
                QMessageBox errorBox;
                errorBox.setText("Warning: Circle need input at least 3 points! ");
                errorBox.exec();
            }
            else
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
        }
        //Generate points on ellipse
        if (type == 3)
        {
            if(num_points<3)
            {
                QMessageBox errorBox;
                errorBox.setText("Warning: Ellipse need input at least 3 points! ");
                errorBox.exec();
            }
            else
            {
                //Ellipse center
                int three_wide = w/3;
                int three_height = h/3;
                QPoint center(rand()%three_wide+three_wide,rand()%three_height+three_height);

                //Generate length of axis
                double a = rand()%three_wide+1;
                double b = rand()%three_height+1;
                double fi = (2*M_PI)/num_points;
                QPoint q;

                //Points on ellipse
                for(int i = 0; i < num_points; i++)
                {
                    q.setX(center.x() + static_cast<int>(a*cos(i*fi)));
                    q.setY(center.y() + static_cast<int>(b*sin(i*fi)));
                    points.push_back(q);
                }
            }
        }
        //Generate points on Square
        if (type == 4)
        {
            if(num_points<4)
            {
                QMessageBox errorBox;
                errorBox.setText("Warning: Square need input at least 4 points! ");
                errorBox.exec();
            }
            else
            {
                if(num_points%4!=0)
                {
                    QMessageBox errorBox;
                    errorBox.setText("Warning: Square need input divisible by 4 without rest. Your input will be reduced to nearest smaller point divisible by 4 without rest. ");
                    errorBox.exec();
                }
                //Left up corner
                double lcx = rand()%(w-70)+10;
                double lcy = rand()%(h-70)+10;
                QPoint p(lcx,lcy);
                int pom;
                if (w-lcx > h-lcy)
                {
                    pom =  h-lcy;
                }
                else
                {
                    pom = w-lcx;
                }
                int length = rand()%(pom-30)+20;
                //Other corners
                QPoint p1(p.x()+(length),p.y());
                QPoint p2(p.x()+(length),p.y()+(length));
                QPoint p3(p.x(),(p.y()+length));
                points.push_back(p);
                points.push_back(p1);
                points.push_back(p2);
                points.push_back(p3);
                //Other points
                int part = (length)/(num_points/4); //Distance between other points
                for(int i = 0; i < num_points/4; i++)
                {
                    points.push_back(QPoint(p1.x()-((i*part)),p1.y()));
                    points.push_back(QPoint(p2.x(),p2.y()-(i*part)));
                    points.push_back(QPoint(p3.x()+((i*part)),p3.y()));
                    points.push_back(QPoint(p.x(),p.y()+(i*part)));
                }
            }
        }
    }
            repaint();
}
