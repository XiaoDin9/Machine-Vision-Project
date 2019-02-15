/********************************************************************************
** Form generated from reading UI file 'filter_function.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTER_FUNCTION_H
#define UI_FILTER_FUNCTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Filter_Function
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QComboBox *comboBox;
    QGroupBox *groupBox_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QSlider *BoxFilterlSlider;
    QSlider *MeanBlurSlider;
    QSlider *GaussianBlurSlider;
    QSlider *MedianBlurSlider;
    QSlider *BilateralFilterSlider;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QGroupBox *groupBox_3;
    QLabel *label_7;
    QComboBox *comboBox_2;
    QGroupBox *groupBox_4;
    QCheckBox *checkBox;
    QLabel *label_14;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_8;
    QLabel *label_21;
    QLabel *label_22;

    void setupUi(QWidget *Filter_Function)
    {
        if (Filter_Function->objectName().isEmpty())
            Filter_Function->setObjectName(QStringLiteral("Filter_Function"));
        Filter_Function->resize(1122, 802);
        groupBox = new QGroupBox(Filter_Function);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 341, 81));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 30, 61, 20));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(160, 30, 141, 22));
        groupBox_2 = new QGroupBox(Filter_Function);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 230, 341, 231));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 30, 81, 16));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 70, 81, 16));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 110, 81, 16));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 150, 81, 16));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 190, 81, 16));
        BoxFilterlSlider = new QSlider(groupBox_2);
        BoxFilterlSlider->setObjectName(QStringLiteral("BoxFilterlSlider"));
        BoxFilterlSlider->setGeometry(QRect(120, 30, 211, 19));
        BoxFilterlSlider->setOrientation(Qt::Horizontal);
        MeanBlurSlider = new QSlider(groupBox_2);
        MeanBlurSlider->setObjectName(QStringLiteral("MeanBlurSlider"));
        MeanBlurSlider->setGeometry(QRect(120, 70, 211, 19));
        MeanBlurSlider->setOrientation(Qt::Horizontal);
        GaussianBlurSlider = new QSlider(groupBox_2);
        GaussianBlurSlider->setObjectName(QStringLiteral("GaussianBlurSlider"));
        GaussianBlurSlider->setGeometry(QRect(120, 110, 211, 19));
        GaussianBlurSlider->setOrientation(Qt::Horizontal);
        MedianBlurSlider = new QSlider(groupBox_2);
        MedianBlurSlider->setObjectName(QStringLiteral("MedianBlurSlider"));
        MedianBlurSlider->setGeometry(QRect(120, 150, 211, 19));
        MedianBlurSlider->setOrientation(Qt::Horizontal);
        BilateralFilterSlider = new QSlider(groupBox_2);
        BilateralFilterSlider->setObjectName(QStringLiteral("BilateralFilterSlider"));
        BilateralFilterSlider->setGeometry(QRect(120, 190, 211, 19));
        BilateralFilterSlider->setOrientation(Qt::Horizontal);
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(280, 10, 54, 12));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(280, 50, 54, 12));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(280, 90, 54, 12));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(280, 130, 54, 12));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(280, 170, 54, 12));
        groupBox_3 = new QGroupBox(Filter_Function);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 130, 341, 81));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(80, 30, 61, 20));
        comboBox_2 = new QComboBox(groupBox_3);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(160, 30, 141, 22));
        groupBox_4 = new QGroupBox(Filter_Function);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 500, 341, 91));
        checkBox = new QCheckBox(groupBox_4);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(130, 40, 111, 16));
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(130, 60, 81, 20));
        pushButton = new QPushButton(Filter_Function);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 690, 75, 23));
        pushButton_2 = new QPushButton(Filter_Function);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(290, 690, 75, 23));
        pushButton_3 = new QPushButton(Filter_Function);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(200, 690, 75, 23));
        label_15 = new QLabel(Filter_Function);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(0, 0, 1090, 10));
        label_15->setStyleSheet(QStringLiteral("background-color: rgb(85, 170, 255);"));
        label_16 = new QLabel(Filter_Function);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(0, 10, 10, 730));
        label_16->setStyleSheet(QStringLiteral("background-color: rgb(85, 170, 255);"));
        label_17 = new QLabel(Filter_Function);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 730, 1080, 10));
        label_17->setStyleSheet(QStringLiteral("background-color: rgb(85, 170, 255);"));
        label_18 = new QLabel(Filter_Function);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(1080, 10, 10, 730));
        label_18->setStyleSheet(QStringLiteral("background-color: rgb(85, 170, 255);"));
        label_19 = new QLabel(Filter_Function);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(370, 10, 10, 720));
        label_19->setStyleSheet(QStringLiteral("background-color: rgb(85, 170, 255);"));
        label_20 = new QLabel(Filter_Function);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(630, 270, 54, 12));
        label_8 = new QLabel(Filter_Function);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(380, 10, 700, 720));
        label_8->setStyleSheet(QStringLiteral(""));
        label_21 = new QLabel(Filter_Function);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(10, 110, 360, 10));
        label_21->setStyleSheet(QStringLiteral("background-color: rgb(85, 170, 255);"));
        label_22 = new QLabel(Filter_Function);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(10, 470, 360, 10));
        label_22->setStyleSheet(QStringLiteral("background-color: rgb(85, 170, 255);"));

        retranslateUi(Filter_Function);
        QObject::connect(pushButton, SIGNAL(clicked()), Filter_Function, SLOT(on_run_clicked()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), Filter_Function, SLOT(on_sure_clicked()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), Filter_Function, SLOT(on_cancel_clicked()));
        QObject::connect(comboBox, SIGNAL(activated(QString)), Filter_Function, SLOT(activate_comboBox_triggred()));
        QObject::connect(comboBox_2, SIGNAL(activated(QString)), Filter_Function, SLOT(activate_comboBox_2_triggred()));
        QObject::connect(BoxFilterlSlider, SIGNAL(valueChanged(int)), Filter_Function, SLOT(set_boxfilter_value(int)));
        QObject::connect(MeanBlurSlider, SIGNAL(valueChanged(int)), Filter_Function, SLOT(set_meanblur_value(int)));
        QObject::connect(GaussianBlurSlider, SIGNAL(valueChanged(int)), Filter_Function, SLOT(set_gaussianblur_value(int)));
        QObject::connect(MedianBlurSlider, SIGNAL(valueChanged(int)), Filter_Function, SLOT(set_medianblur_value(int)));
        QObject::connect(BilateralFilterSlider, SIGNAL(valueChanged(int)), Filter_Function, SLOT(set_bilateralfilter(int)));
        QObject::connect(checkBox, SIGNAL(stateChanged(int)), Filter_Function, SLOT(on_statechanged(int)));

        QMetaObject::connectSlotsByName(Filter_Function);
    } // setupUi

    void retranslateUi(QWidget *Filter_Function)
    {
        Filter_Function->setWindowTitle(QApplication::translate("Filter_Function", "Filter_Function", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Filter_Function", "\346\225\260\346\215\256\351\223\276\346\216\245", Q_NULLPTR));
        label->setText(QApplication::translate("Filter_Function", "\350\276\223\345\205\245\345\233\276\345\203\217\357\274\232", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Filter_Function", "\351\207\207\351\233\206\345\233\276\345\203\217", Q_NULLPTR)
        );
        groupBox_2->setTitle(QApplication::translate("Filter_Function", "\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        label_2->setText(QApplication::translate("Filter_Function", "\346\226\271\346\241\206\346\273\244\346\263\242\345\217\202\346\225\260\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("Filter_Function", "\345\235\207\345\200\274\346\273\244\346\263\242\345\217\202\346\225\260\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("Filter_Function", "\351\253\230\346\226\257\346\273\244\346\263\242\345\217\202\346\225\260\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("Filter_Function", "\344\270\255\345\200\274\346\273\244\346\263\242\345\217\202\346\225\260\357\274\232", Q_NULLPTR));
        label_6->setText(QApplication::translate("Filter_Function", "\345\217\214\350\276\271\346\273\244\346\263\242\345\217\202\346\225\260\357\274\232", Q_NULLPTR));
        label_9->setText(QString());
        label_10->setText(QString());
        label_11->setText(QString());
        label_12->setText(QString());
        label_13->setText(QString());
        groupBox_3->setTitle(QApplication::translate("Filter_Function", "\346\273\244\346\263\242\351\200\211\346\213\251", Q_NULLPTR));
        label_7->setText(QApplication::translate("Filter_Function", "\346\273\244\346\263\242\345\231\250\357\274\232", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("Filter_Function", "BoxFilter", Q_NULLPTR)
         << QApplication::translate("Filter_Function", "MeanBlur", Q_NULLPTR)
         << QApplication::translate("Filter_Function", "GaussianBlur", Q_NULLPTR)
         << QApplication::translate("Filter_Function", "MedianBlur", Q_NULLPTR)
         << QApplication::translate("Filter_Function", "BilateralFilter", Q_NULLPTR)
        );
        groupBox_4->setTitle(QApplication::translate("Filter_Function", "\346\230\276\347\244\272\350\256\276\347\275\256", Q_NULLPTR));
        checkBox->setText(QApplication::translate("Filter_Function", "\346\230\276\347\244\272\350\276\223\345\207\272\345\233\276", Q_NULLPTR));
        label_14->setText(QString());
        pushButton->setText(QApplication::translate("Filter_Function", "\346\211\247\350\241\214", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Filter_Function", "\345\217\226\346\266\210", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Filter_Function", "\347\241\256\350\256\244", Q_NULLPTR));
        label_15->setText(QString());
        label_16->setText(QString());
        label_17->setText(QString());
        label_18->setText(QString());
        label_19->setText(QString());
        label_20->setText(QString());
        label_8->setText(QString());
        label_21->setText(QString());
        label_22->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Filter_Function: public Ui_Filter_Function {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTER_FUNCTION_H
