/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <draw.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QHBoxLayout *horizontalLayout;
    Draw *Canvas;
    QVBoxLayout *verticalLayout_3;
    QPushButton *loadPoints;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QPushButton *createContour;
    QPushButton *clearContour;
    QSpacerItem *verticalSpacer_2;
    QComboBox *comboBox;
    QPushButton *analyzeDTM;
    QPushButton *analysisClear;
    QSpacerItem *verticalSpacer_4;
    QPushButton *clearPoints;
    QPushButton *clearAll;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1062, 681);
        horizontalLayout = new QHBoxLayout(Widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Canvas = new Draw(Widget);
        Canvas->setObjectName(QString::fromUtf8("Canvas"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(Canvas->sizePolicy().hasHeightForWidth());
        Canvas->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(Canvas);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        loadPoints = new QPushButton(Widget);
        loadPoints->setObjectName(QString::fromUtf8("loadPoints"));

        verticalLayout_3->addWidget(loadPoints);

        label_4 = new QLabel(Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_3->addWidget(label_4);

        lineEdit_4 = new QLineEdit(Widget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        verticalLayout_3->addWidget(lineEdit_4);

        verticalSpacer = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label);

        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout_3->addWidget(lineEdit);

        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);

        lineEdit_2 = new QLineEdit(Widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        verticalLayout_3->addWidget(lineEdit_2);

        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        lineEdit_3 = new QLineEdit(Widget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        verticalLayout_3->addWidget(lineEdit_3);

        createContour = new QPushButton(Widget);
        createContour->setObjectName(QString::fromUtf8("createContour"));

        verticalLayout_3->addWidget(createContour);

        clearContour = new QPushButton(Widget);
        clearContour->setObjectName(QString::fromUtf8("clearContour"));

        verticalLayout_3->addWidget(clearContour);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        comboBox = new QComboBox(Widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout_3->addWidget(comboBox);

        analyzeDTM = new QPushButton(Widget);
        analyzeDTM->setObjectName(QString::fromUtf8("analyzeDTM"));

        verticalLayout_3->addWidget(analyzeDTM);

        analysisClear = new QPushButton(Widget);
        analysisClear->setObjectName(QString::fromUtf8("analysisClear"));

        verticalLayout_3->addWidget(analysisClear);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        clearPoints = new QPushButton(Widget);
        clearPoints->setObjectName(QString::fromUtf8("clearPoints"));

        verticalLayout_3->addWidget(clearPoints);

        clearAll = new QPushButton(Widget);
        clearAll->setObjectName(QString::fromUtf8("clearAll"));

        verticalLayout_3->addWidget(clearAll);


        horizontalLayout->addLayout(verticalLayout_3);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "DTM", nullptr));
        loadPoints->setText(QCoreApplication::translate("Widget", "Load points", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "Set Z (insert point)", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("Widget", "200", nullptr));
        label->setText(QCoreApplication::translate("Widget", "Z_min [m]", nullptr));
        lineEdit->setText(QCoreApplication::translate("Widget", "0", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "Z_max [m]", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("Widget", "500", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "Interval z [m]", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("Widget", "10", nullptr));
        createContour->setText(QCoreApplication::translate("Widget", "Contour lines", nullptr));
        clearContour->setText(QCoreApplication::translate("Widget", "Clear contours", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Widget", "slope", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Widget", "aspect", nullptr));

        analyzeDTM->setText(QCoreApplication::translate("Widget", "Analyze DTM", nullptr));
        analysisClear->setText(QCoreApplication::translate("Widget", "Clear analysis", nullptr));
        clearPoints->setText(QCoreApplication::translate("Widget", "Clear Points", nullptr));
        clearAll->setText(QCoreApplication::translate("Widget", "Clear all", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
