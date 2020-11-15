#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"
#include "qdebug.h"
#include <ctime>
#include <QString>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    //Get points
    std::vector<QPoint> points = ui->Canvas->getPoints();

    //Create convex hull
    QPolygon ch;
    Algorithms alg;

    //Start timer
    clock_t start = clock();

    //Get combo-box status
    switch(ui->comboBox->currentIndex())
    {
        case 0: ch = alg.jarvis(points);
                break;
        case 1: ch = alg.qhull(points);
                break;
        case 2: ch = alg.sweepLine(points);
                break;
        case 3: ch = alg.graham(points);
                break;
    }

    //End timer
    clock_t end = clock();
    clock_t run_time = end - start;
    ui->label_4->setText(QString::number(run_time) + "ms");

    //Set convex hull
    ui->Canvas->setCH(ch);

    //Repaint screen
    repaint();
}

void Widget::on_pushButton_2_clicked()
{
    //Get Convex Hull
    QPolygon &ch = ui->Canvas->getCH();

    //Clear points
    ch.clear();

    //Repaint screen
    repaint();
}

void Widget::on_generatePoints_clicked()
{

    // Get widnow width, height
    int width = ui ->Canvas->size().width();
    int height = ui ->Canvas->size().height();

    // Get number of points
    int n = ui->lineEdit->text().toInt();
    int type = 0;

    //Type of generation
    //0 - random
    //1 - grid
    //2 - circle

    //Get combo-box status
    switch(ui->comboBox_2->currentIndex())
    {
        case 0: type = 0;
                qDebug() << type;
                break;
        case 1: type = 1;
                qDebug() << type;
                break;
        case 2: type = 2;
                qDebug() << type;
                break;
        case 3: type = 3; //Ellipse
                qDebug() << type;
                break;
        case 4: type = 4; //Square
                qDebug() << type;
                break;
    }

    //Get Convex Hull
    QPolygon &ch = ui->Canvas->getCH();

    //Clear points CH
    ch.clear();

    ui->Canvas->generatePoints(n, width, height, type);

    qDebug() << ui->comboBox->currentIndex();




}

void Widget::on_pushButton_3_clicked()
{
    //Get Convex Hull
    QPolygon &ch = ui->Canvas->getCH();

    //Get Points
    std::vector<QPoint> &points = ui->Canvas->getPoints();

    //Clear points CH
    ch.clear();

    //Clear points
    points.clear();

    //Repaint screen
    repaint();
}
