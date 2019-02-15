#ifndef FILTER_FUNCTION_H
#define FILTER_FUNCTION_H

#include <QWidget>
#include "ui_filter_function.h"
#include "zv.h"

class Filter_Function : public QWidget
{
    Q_OBJECT

public:
    Filter_Function(QWidget *parent = 0);
    ~Filter_Function();
    void print_show1();

private:
    Ui::Filter_Function ui;
    ZvImage convert_filter;           //处理后的图像

private slots :
    void activate_comboBox_triggred();
    void activate_comboBox_2_triggred();
    void on_run_clicked();
    void on_sure_clicked();
    void on_cancel_clicked();
    void set_medianblur_value(int);
    void set_meanblur_value(int);
    void set_gaussianblur_value(int);
    void set_boxfilter_value(int);
    void set_bilateralfilter(int);
    void on_statechanged(int);

public:
    void Filter_Processing();
};

#endif // FILTER_FUNCTION_H
