#ifndef COLOR_TRANSORM_H
#define COLOR_TRANSORM_H

#include <QWidget>
#include <iostream>

#include "ui_color_transorm.h"
#include "zv.h"

class Color_Transorm : public QWidget
{
    Q_OBJECT

public:
    ZvImage src_image;
    Color_Transorm(QWidget *parent = 0);
    ~Color_Transorm();

private:
    Ui::Color_Transorm ui;

private slots :
    void On_comboBox_activated();
    void On_comboBox_4_activated();
    void On_comboBox_5_activated();
    void on_run_clicked();
    void on_cancel_clicked();
    void on_sure_clicked();
    void on_radioButton_clicked();
    void on_radioButton2_clicked();
    void on_radioButton3_clicked();
    void on_radioButton4_clicked();
public:
    void show_print();
    void color_transorm();
};

#endif // COLOR_TRANSORM_H
