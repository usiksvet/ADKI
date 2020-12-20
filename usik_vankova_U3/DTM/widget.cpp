#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"
#include "triangle.h"
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    z_min = 0;
    z_max = 500;
    dz = 10;
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_lineEdit_editingFinished()
{
    //Set z_min
    z_min = ui -> lineEdit -> text().toDouble();
}


void Widget::on_lineEdit_2_editingFinished()
{
    //Set z_max
    z_max = ui -> lineEdit_2 -> text().toDouble();
}


void Widget::on_lineEdit_3_editingFinished()
{
    //Set dz
    dz = ui -> lineEdit_3 -> text().toDouble();
}


void Widget::on_loadPoints_clicked()
{
    //Clear screen
    on_clearAll_clicked();

    repaint();

    std::vector<QPoint3D> points;

    QSizeF canvas_size = ui->Canvas->size();

    QString path = QFileDialog::getOpenFileName(
                this,
                tr("Select file"),
                "/",
                "Text file (*.txt)");

    //transform path
    std::string path_utf8 = path.toUtf8().constData();

    Draw D;

    D.importData(path_utf8, points, canvas_size, z_min, z_max);

    ui->Canvas->setPoints(points);
    ui->Canvas->repaint();
}

void Widget::on_createContour_clicked()
{

    on_analysisClear_clicked();
    //Create contour lines
    Algorithms a;
    std::vector<Edge> dt;

    //DT needs to be created
    if(dt.size() == 0)
    {
        //Get points
        std::vector<QPoint3D> points = ui->Canvas->getPoints();

        //Create DT
        dt = a.DT(points);

        //Set DT
        ui->Canvas->setDT(dt);
    }

    std::vector<int> contour_z;
    std::vector<int> bold_contour_z;

    //Create contour lines
    std::vector<Edge> contours = a.contourLines(dt, z_min, z_max, dz, contour_z); // contour_z is empty
    std::vector<Edge> bold_contours = a.contourLines(dt, z_min, z_max, 5*dz, bold_contour_z); // bold_contour_z stores contours heights

    //Set contours
    ui->Canvas->setContours(contours);
    ui->Canvas->setBoldContours(bold_contours, bold_contour_z);

    //Repaint
    repaint();
}

void Widget::on_clearContour_clicked()
{
    //Get DT and contours
    //std::vector<Edge> &dt = ui->Canvas->getDT();
    std::vector<Edge> &contours = ui->Canvas->getContours();
    std::vector<Edge> &bold_contour = ui->Canvas->getBoldContours();


    //Clear contour lines
    //dt.clear();
    contours.clear();
    bold_contour.clear();

    //Repaint
    repaint();
}

void Widget::on_analyzeDTM_clicked()
{

    on_clearContour_clicked();

    Algorithms a;
    std::vector<Edge> dt;

    // Reset analysis type
    bool slope = FALSE;
    bool aspect = FALSE;

    //DT needs to be created
    if(dt.size() == 0)
    {
        //Get points
        std::vector<QPoint3D> points = ui->Canvas->getPoints();

        //Create DT
        dt = a.DT(points);

        //Set DT
        ui->Canvas->setDT(dt);
    }
    //Triangulation has been created
    else
    {
        dt = ui->Canvas->getDT();
    }

    //Analyze DTM
    std::vector<Triangle> dtm = a.analyzeDTM(dt);
    //Set analysis
    ui->Canvas->setDTM(dtm);

    //Repaint
    repaint();

    // Selected analyze
    if (ui->comboBox->currentIndex()==0){
        slope = TRUE;
        aspect = FALSE;
    }
    else if (ui->comboBox->currentIndex()==1){
        slope = FALSE;
        aspect = TRUE;
    }

    ui->Canvas->setSlope(slope);
    ui->Canvas->setAspect(aspect);

    repaint();
}

void Widget::on_analysisClear_clicked()
{
    //Clear DTM analysis
    std::vector<Triangle> &dtm = ui->Canvas->getDTM();

    //Clear DTM
    dtm.clear();

    //Repaint
    repaint();
}

void Widget::on_clearPoints_clicked()
{
    //Get points
    std::vector<QPoint3D> &points = ui->Canvas->getPoints();

    //Clear points
    points.clear();

    //Repaint
    repaint();
}


void Widget::on_clearAll_clicked()
{
    //Get all
    std::vector<QPoint3D> &points = ui->Canvas->getPoints();
    std::vector<Edge> &dt = ui->Canvas->getDT();
    std::vector<Edge> &contours = ui->Canvas->getContours();
    std::vector<Triangle> &dtm = ui->Canvas->getDTM();
    std::vector<Edge> &bold_contour = ui->Canvas->getBoldContours();

    //Clear all
    points.clear();
    dt.clear();
    contours.clear();
    dtm.clear();
    bold_contour.clear();

    //Repaint
    repaint();

}

void Widget::on_lineEdit_4_cursorPositionChanged(int arg1, int arg2)
{
    //Set Z
    z_clicked = ui -> lineEdit_4 -> text().toDouble();
    ui->Canvas->setZClicked(z_clicked);
}
