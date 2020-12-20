#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
private:
    double z_min, z_max, dz;
    double z_clicked;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_loadPoints_clicked();

    void on_analyzeDTM_clicked();

    void on_createContour_clicked();

    void on_clearContour_clicked();

    void on_analysisClear_clicked();

    void on_clearPoints_clicked();

    void on_clearAll_clicked();

    void on_lineEdit_4_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
