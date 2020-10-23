#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include <QtGui>

class Draw : public QWidget        
{
    Q_OBJECT
private:
    QPointF q;  //point
    std::vector <QPolygonF> map_polygons;   //map of polygons
    std::vector <int> results;  //variable for storing the result function algorithms

public:
    explicit Draw(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);    
    QPointF & getPoint (){return q;}
    QPolygonF & getPolygon (unsigned int index){return map_polygons[index];}    //function return polygon[i] from map of polygons
    std::vector<QPolygonF> & getMapPolygon (){return map_polygons;}

    bool importPolygonsFromFile(std::string &fail_path);
    void importPolygons(QVector<QPolygonF> polygons);

    void saveResult(std::vector<int> res){results = res;}
    void clearCanvas();
};

#endif // DRAW_H
