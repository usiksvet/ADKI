#include "draw.h"
#include "qdebug.h"


Draw::Draw(QWidget *parent) : QWidget(parent)
{

}

void Draw::mousePressEvent(QMouseEvent *e)
{
    //Get coordinates
    int x = e->x();
    int y = e->y();

    //Add point to the list
    QPoint q(x, y);         //create point
    points.push_back(q);    //add to point list

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

    if (type == 0)
    {
        //Generate points randomly
        for(int i = 0; i < num_points; i++)
        {
            point.setX(rand()%w);
            point.setY(rand()%h);
            points.push_back(point);
        }
    }


//    // Interval for generation points on grid
//    int step_x = w/num_points;
//    int step_y = h/num_points;
//    int x = 0;
//    int y = 0;

//    qDebug() <<"Interval x, y";
//    qDebug() << step_x;
//    qDebug() << step_y;

//    //Generate points on grid

//    for (x = 0; ((x*step_x) < w); x++)
//    {
//        for (y = 0; ((y*step_y) < h); y++)
//        {
//            point.setX(x * step_x);
//            point.setY(y * step_y);
//            points.push_back(point);
//            num_points--;

//        }
//    }

    qDebug() <<"Points";
    qDebug() << points;

    repaint();
}


