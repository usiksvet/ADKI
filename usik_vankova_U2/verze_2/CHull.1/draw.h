#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include <QtGui>

class Draw : public QWidget
{
    Q_OBJECT
    private:
        std::vector<QPointF> points;     //Input points
        QPolygonF ch;                    //Convex Hull

    public:
        explicit Draw(QWidget *parent = nullptr);

        void mousePressEvent (QMouseEvent *e); //parametr pointer *e jako event
        void paintEvent(QPaintEvent *e);
        std::vector<QPointF> & getPoints(){return points;}
        QPolygonF & getCH(){return ch;}
        void setCH(QPolygonF &ch_){ch = ch_;}
        void generatePoints(int num_points, int w, int h, int type);


signals:

};

#endif // DRAW_H
