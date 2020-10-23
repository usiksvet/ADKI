#include "draw.h"
#include <fstream>
#include <QMessageBox>
#include "qdebug.h"

Draw::Draw(QWidget *parent) : QWidget(parent)
{
    //Draw point outside canvas
    q.setX(-50);
    q.setY(-50);
}

void Draw::importPolygons(QVector<QPolygonF> polygons)
{

    map_polygons.clear();

    for (QPolygonF polygon : polygons)
    {
        map_polygons.push_back(polygon);
        polygon.clear();
    }

    polygons.clear();
}

bool Draw::importPolygonsFromFile(std::string &file_path)
{
    map_polygons.clear();

    QPolygonF polygon;
    int n;
    double x;
    double y;

    std::ifstream file(file_path);

    if(file.is_open())
    {
        while (file >> n >> x >> y)
        {
            if(n == 1)
            {
                if(polygon.empty() == FALSE)
                {
                    map_polygons.push_back(polygon);
                }
                polygon.clear();
                polygon << QPointF(x, y);
            }
            else
            {
                polygon << QPointF(x, y);
            }
        }

        map_polygons.push_back(polygon); //save last polygon
        polygon.clear();

        file.close();

        //Message box
        QMessageBox msgBox;
        msgBox.setWindowTitle("Import result");
        msgBox.setText("Import success!");
        msgBox.exec();
        return true;
    }
    QMessageBox msgBox;
    msgBox.setText("Import failed!");
    msgBox.exec();
    return false;
}

void Draw::mousePressEvent(QMouseEvent *e)
{
    //Cursor position
    int x=e->pos().x();
    int y=e->pos().y();

    q.setX(x);
    q.setY(y);

    repaint();
}

void Draw::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    //Start drawing
    QPainter painter(this);

    //Begin paint
    painter.begin(this);

    //Draw polygons from file
    for (unsigned int i = 0; i < map_polygons.size(); i++)
    {
        QPolygonF pol = map_polygons[i];
        painter.drawPolygon(pol);
    }

    //Show selected polygon
    QBrush brush;
    brush.setColor(Qt::darkMagenta);
    brush.setStyle(Qt::SolidPattern);
    QPainterPath brush_path;
    QPolygonF selected_polygon;
    for(unsigned int i = 0; i < results.size(); i++)
    {
        if(results[i] == 1)
        {
            selected_polygon << map_polygons[i];
            brush_path.addPolygon(selected_polygon);
            painter.fillPath(brush_path, brush);
            painter.drawPolygon(selected_polygon);
            selected_polygon.clear();
            brush_path.clear();
        }
    }

    //Draw q point
    int r = 5;
    painter.drawEllipse(q.x()-5,q.y()-5, 2*r, 2*r);

    //End paint
    painter.end();
}

void Draw::clearCanvas()
{
    map_polygons.clear();
    results.clear();
    q.setX(-50);
    q.setY(-50);
    repaint();
}
