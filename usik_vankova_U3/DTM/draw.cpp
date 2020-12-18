#include "draw.h"
#include <fstream>

Draw::Draw(QWidget *parent) : QWidget(parent)
{

}

void Draw::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.begin(this);

    //Draw points
    for (unsigned int i = 0; i < points.size(); i++)
    {
        painter.drawEllipse(points[i].x() - 5, points[i].y() - 5, 10, 10);
    }

    //Draw Delaunay edges
    QPen p(Qt::green, 1);
    painter.setPen(p);

    for (unsigned int i = 0; i < dt.size(); i++)
    {
        painter.drawLine(dt[i].getStart(), dt[i].getEnd());
    }

    //Draw contour lines
    QPen q(Qt::gray, 1);
    painter.setPen(q);
    for (unsigned int i = 0; i < contours.size(); i++)
    {
        painter.drawLine(contours[i].getStart(), contours[i].getEnd());
    }

    //Draw main(bold) contour lines (brown, 2) with text description
    for(unsigned int i = 0; i < bold_contours.size(); i++)
    {
        painter.drawLine(bold_contours[i].getStart(), bold_contours[i].getEnd());
        painter.setPen(QPen(QColor(139,69,19), 2));

        int h_main = static_cast<int>(contours_z[i]);

        if (i % 10 == 0)
        {
            double text_x = (bold_contours[i].getStart().x() + bold_contours[i].getEnd().x())/2;
            double text_y = (bold_contours[i].getStart().y() + bold_contours[i].getEnd().y())/2;
            painter.drawText(static_cast<int>(text_x), static_cast<int>(text_y), QString::number(h_main));
        }
    }

    // Draw slope
    if (slope == TRUE)
    {
        double k = 255.0 / 90;
        for (Triangle t : dtm)
        {
            //Get triangle vertices
            QPoint3D p1 = t.getP1();
            QPoint3D p2 = t.getP2();
            QPoint3D p3 = t.getP3();
            int slope = 255 - t.getSlope() * k;

            //Set color brush
            QColor c(slope, slope, slope);
            painter.setBrush(c);

            //Create polygon
            QPolygonF triangle;
            triangle.append(QPointF(p1.x(), p1.y()));
            triangle.append(QPointF(p2.x(), p2.y()));
            triangle.append(QPointF(p3.x(), p3.y()));

            painter.drawPolygon(triangle);
        }
    }

    //Draw aspect
    if (aspect == TRUE)
    {
        double k2 = 255.0 / 360;
        for (Triangle t : dtm)
        {
            //Get triangle vertices
            QPoint3D p1 = t.getP1();
            QPoint3D p2 = t.getP2();
            QPoint3D p3 = t.getP3();

            int aspect = static_cast<int>(255 - t.getAspect() * k2);

            //Set brush colo
            QColor c(aspect, aspect, aspect);
            painter.setBrush(c);

            //Create polygon
            QPolygonF triangle;
            triangle.append(QPointF(p1.x(), p1.y()));
            triangle.append(QPointF(p2.x(), p2.y()));
            triangle.append(QPointF(p3.x(), p3.y()));

            painter.drawPolygon(triangle);
        }
    }

    painter.end();
}


void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get coordinates of cursor
    QPoint3D p;
    p.setX(event ->x());
    p.setY(event ->y());
    double random = std::rand() * 200.0 / RAND_MAX;
    p.setZ(random);

    //Add point to the list
    points.push_back(p);

    repaint();
};

void Draw::importData(std::string &path, std::vector<QPoint3D> &points,  QSizeF &canvas_size, double &min_z, double &max_z)
{
    double x, y, z;
    QPoint3D p;

    // Dataset limits
    min_z = std::numeric_limits<double>::max();
    max_z = std::numeric_limits<double>::min();
    double min_x = std::numeric_limits<double>::max();
    double min_y = std::numeric_limits<double>::max();
    double max_x = std::numeric_limits<double>::min();
    double max_y = std::numeric_limits<double>::min();


    std::ifstream myfile(path);
    if(myfile.is_open())
    {
        while(myfile >> x >> y >> z)
        {
            p.setX(x);
            p.setY(y);
            p.setZ(z);

            points.push_back(p);

            // Limits update
            if(x < min_x) min_x = x;
            if(x > max_x) max_x = x;
            if(y < min_y) min_y = y;
            if(y > max_y) max_y = y;
            if(z < min_z) min_z = z;
            if(z > max_z) max_z = z;
        }

        myfile.close();
    }

    //Rescaling points to the canvas size
    double h = canvas_size.height();
    double w = canvas_size.width();

    double x_coef = w/(max_x-min_x);
    double y_coef = h/(max_y-min_y);

    for(unsigned int i = 0; i < points.size(); i++)
    {
        points[i].setX((points[i].x()-min_x)*x_coef);
        points[i].setY((points[i].y()-min_y)*y_coef);
    }
}

void Draw::setBoldContours(std::vector<Edge> &contours_, std::vector<int> &contours_z_)
{
    bold_contours = contours_;
    contours_z = contours_z_;
}
