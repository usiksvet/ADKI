#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>

#include "qpoint3d.h"
#include "edge.h"
#include "triangle.h"
#include <widget.h>

class Draw : public QWidget
{
    Q_OBJECT

private:
    std::vector <QPoint3D> points;
    std::vector <Edge> dt;
    std::vector <Edge> contours, bold_contours;
    std::vector <Triangle> dtm;
    std::vector<int> contours_z; // store contour line height
    bool slope, aspect;
    double z_clicked;

public:
    explicit Draw(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void setPoints(std::vector<QPoint3D> &points_){points=points_;}
    std::vector<QPoint3D> & getPoints(){return points;}
    void setDT(std::vector<Edge> &dt_){dt = dt_;}
    std::vector<Edge> & getDT(){return dt;}
    void setContours(std::vector<Edge> &contours_){contours = contours_;}
    void setBoldContours(std::vector<Edge> &contours_, std::vector<int> &contours_z_);
    std::vector<Edge> & getContours(){return contours;}
    std::vector<Edge> & getBoldContours(){return bold_contours;}
    void setDTM(std::vector<Triangle> &dtm_){dtm = dtm_;}
    std::vector<Triangle> & getDTM(){return dtm;}    
    void importData(std::string &path, std::vector<QPoint3D> &points,  QSizeF &canvas_size, double &min_z, double &max_z);
    void setSlope(bool &slope_){slope = slope_;}// Flags to indicate type of analysis
    void setAspect(bool &aspect_){aspect = aspect_;}// Flags to indicate type of analysis
    void setZClicked(double z){z_clicked = z;}
    double getZClicked(){return z_clicked;}
signals:

public slots:
};

#endif // DRAW_H
