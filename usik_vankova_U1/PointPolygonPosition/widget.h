#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>  //library for work with files
#include "generate_random_polygon.cpp"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_2_clicked(); // analyse polygon/point position
    void on_pushButton_3_clicked(); // clear all on canvas
    void on_pushButton_4_clicked(); // import polygon from txt
    void on_pushButton_clicked();   // generate random polygons

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
