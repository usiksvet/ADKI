#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"

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

void Widget::on_pushButton_2_clicked()
{
    //Get point q
    QPointF q = ui->Canvas->getPoint();

    std::vector<int> pom_res;

    Algorithms alg;

    //Get combo-box status, select method
    for (unsigned int i = 0; i < ui->Canvas->getMapPolygon().size(); i++)
    {
        QPolygonF polygon = ui->Canvas->getPolygon(i);
        int pom = 0;

        //Winding Number Algorithm
        if (ui->comboBox->currentIndex() == 0)
        {
            pom = alg.getPositionWinding(q, polygon);
        }        
        //Ray Crossing Algorithm
        else
        {
            pom = alg.getPositionRay(q, polygon);
        }

        pom_res.push_back(pom);

        ui->Canvas->saveResult(pom_res);
    }

    ui->Canvas->repaint();
}

void Widget::on_pushButton_3_clicked()
{
    ui->Canvas->clearCanvas();
    ui->Canvas->repaint();
}

void Widget::on_pushButton_4_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/", tr("Text files (*.txt)"));

    std::string file_path_utf8 = file_path.toUtf8().constData();

    ui->Canvas->importPolygonsFromFile(file_path_utf8);
    ui->Canvas->repaint();
}

void Widget::on_pushButton_clicked()
{
    ui->Canvas->clearCanvas();

    GenerateRandomPolygon grp;
    QVector<QPolygonF> polygons = grp.generateRandomPolygons();

    ui->Canvas->importPolygons(polygons);
    ui->Canvas->repaint();
}
