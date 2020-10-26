#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"
#include "qdebug.h"

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

    qDebug() << points;

    //Create convex hull
    QPolygon ch;
    Algorithms alg;

    //Get combo-box status
    switch(ui->comboBox->currentIndex())
    {
        case 0: ch = alg.jarvis(points);
                break;
        case 1: qDebug() << "QHull";
                break;
        case 2: qDebug() << "Sweep line";
                break;
    }

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
    switch(ui->comboBox->currentIndex())
    {
        case 0: type = 0;
                break;
        case 1: type = 1;
                qDebug() << type;
                break;
        case 2: type = 2;
                qDebug() << type;
                break;
    }

    ui->Canvas->generatePoints(n, width, height, type);

    qDebug() << ui->comboBox->currentIndex();

}
