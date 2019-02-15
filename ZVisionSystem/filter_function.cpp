#pragma execution_character_set("utf-8")

#include "filter_function.h"
#include <qdebug.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qwidget.h>
#include <iostream>
#include <qobject.h>
#include <string.h>

#include "zv.h"

using namespace std;

QString Filter_choice_string = NULL;
QString Input_string = NULL;

extern ZvImage out_image;    //从主窗口中读取图像

bool flag3 = false;    //执行标记
bool flag4 = false;    //确认标记
int number;     //存取滑条数值
QString out_choice_type = NULL;

Filter_Function::Filter_Function(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    ui.MedianBlurSlider->setMinimum(0);
    ui.MedianBlurSlider->setMaximum(20);
    ui.MedianBlurSlider->setValue(2);

    ui.MeanBlurSlider->setMinimum(0);
    ui.MeanBlurSlider->setMaximum(20);
    ui.MeanBlurSlider->setValue(2);

    ui.GaussianBlurSlider->setMinimum(0);
    ui.GaussianBlurSlider->setMaximum(20);
    ui.GaussianBlurSlider->setValue(2);

    ui.BoxFilterlSlider->setMinimum(0);
    ui.BoxFilterlSlider->setMaximum(20);
    ui.BoxFilterlSlider->setValue(2);

    ui.BilateralFilterSlider->setMinimum(0);
    ui.BilateralFilterSlider->setMaximum(20);
    ui.BilateralFilterSlider->setValue(2);

    // 开启三态模式
    ui.checkBox->setTristate();
    convert_filter = zv_imgCreate();
}

Filter_Function::~Filter_Function()
{
    zv_imgRelease(&convert_filter);
}

//图像格式转换，从Mat类型-》QImage类型的变换
QImage Mat4QImage(ZvImage img)
{
    //8-bitsunsigned,NO.OFCHANNELS=1
    int channel = zv_imgChannels(img);
    uchar* qImageBuffer = new uchar(zv_imgHeight(img)*zv_imgWidth(img)*channel);
    if (channel == 1)
    {
        //cout<<"1"<<endl;
        //Setthecolortable(usedtotranslatecolourindexestoqRgbvalues)
        QVector<QRgb>colorTable;
        for (int i = 0; i<256; i++)
            colorTable.push_back(qRgb(i, i, i));
        //CopyinputMat
        zv_imgGetData(img, qImageBuffer, zv_imgHeight(img)*zv_imgWidth(img)*channel, true);
        //CreateQImagewithsamedimensionsasinputMat
        QImage qimg(qImageBuffer, zv_imgHeight(img), zv_imgWidth(img), QImage::Format_Indexed8);
        qimg.setColorTable(colorTable);
        return qimg;
    }
    //8-bitsunsigned,NO.OFCHANNELS=3
    else if (channel == 3)
    {
        //cout<<"3"<<endl;
        //CopyinputMat
        //CreateQImagewithsamedimensionsasinputMat
        QImage qimg(qImageBuffer, zv_imgHeight(img), zv_imgWidth(img), QImage::Format_RGB888);
        return qimg.rgbSwapped();

    }
    else
    {
        qDebug() << "ERROR:MatcouldnotbeconvertedtoQImage.";
        return QImage();
    }
}

/*-------------------------实现槽函数------------------------------*/
//输入图像选择触发函数
void Filter_Function::activate_comboBox_triggred() {
    Input_string = ui.comboBox->itemText(ui.comboBox->currentIndex());   //获得从comobox中选择的索引内容
}
//滤波器选择函数
void Filter_Function::activate_comboBox_2_triggred() {
    Filter_choice_string = ui.comboBox_2->itemText(ui.comboBox_2->currentIndex());
}
//执行函数
void Filter_Function::on_run_clicked() {
    flag3 = true;
}
//确认函数
void Filter_Function::on_sure_clicked() {
    flag4 = true;
    if ((flag3 && flag4) && (Filter_choice_string != NULL)) Filter_Processing();
}
//取消函数
void Filter_Function::on_cancel_clicked() {
    flag3 = false;
    flag4 = false;
}

/*-----------------滤波参数设置----------------------------*/
void Filter_Function::set_medianblur_value(int) {
    int pos = ui.MedianBlurSlider->value();     //在lable 中显示滑条的数字
    number = pos;
    QString str = QString("%1").arg(pos);
    ui.label_12->setText(str);
}
void Filter_Function::set_meanblur_value(int) {
    int pos = ui.MeanBlurSlider->value();     //在lable 中显示滑条的数字
    number = pos;
    QString str = QString("%1").arg(pos);
    ui.label_10->setText(str);
}
void Filter_Function::set_gaussianblur_value(int) {
    int pos = ui.GaussianBlurSlider->value();     //在lable 中显示滑条的数字
    number = pos;
    QString str = QString("%1").arg(pos);
    ui.label_11->setText(str);
}
void Filter_Function::set_boxfilter_value(int) {
    int pos = ui.BoxFilterlSlider->value();     //在lable 中显示滑条的数字
    number = pos;
    QString str = QString("%1").arg(pos);
    ui.label_9->setText(str);
}
void Filter_Function::set_bilateralfilter(int) {
    int pos = ui.BilateralFilterSlider->value();     //在lable 中显示滑条的数字
    number = pos;
    QString str = QString("%1").arg(pos);
    ui.label_13->setText(str);
}

//显示输出选择
void Filter_Function::on_statechanged(int state) {
    if (state == Qt::Checked) { out_choice_type = "processed image";  } // "选中"
    else if (state == Qt::PartiallyChecked) {out_choice_type = "original image"; print_show1();}  // "半选"
    else { ui.label_14->setText("未选择");  ui.label_8->clear();}   //对显示窗口进行擦除
}

//图像滤波处理函数
void Filter_Function::Filter_Processing() {
    if (Filter_choice_string == "BoxFilter") {zv_ipMeanBlur(out_image, convert_filter, number + 1); number = 0; print_show1();}
    else if (Filter_choice_string == "MeanBlur") { zv_ipMeanBlur(out_image, convert_filter, number + 1); number = 0; print_show1();}
    else if (Filter_choice_string == "GaussianBlur") { zv_ipGaussBlur(out_image, convert_filter, number * 2 + 1); number = 0; print_show1();}
    else if (Filter_choice_string == "MedianBlur") { zv_ipMedianBlur(out_image, convert_filter, number * 2 + 1); number = 0; print_show1();}
    else if (Filter_choice_string == "BilateralFilter") { zv_ipBilateralFilter(out_image, convert_filter, number / 2, number * 2); number = 0; print_show1(); }
    else  QMessageBox::information(this, tr("消息提醒框"), tr("请选择要执行的滤波操作！")); 
}

//图像显示函数
void Filter_Function::print_show1() {
    if (out_choice_type == "processed image") {
        QImage image1 = Mat4QImage(convert_filter);
        ui.label_8->setPixmap(QPixmap::fromImage(image1));
        ui.label_8->setScaledContents(true);    //使图像尺寸与label大小匹配
        ui.label_8->show();
        ui.label_14->setText("全选显示处理后的图");
    }
    if (out_choice_type == "original image") {
        QImage image1 = Mat4QImage(out_image);
        ui.label_8->setPixmap(QPixmap::fromImage(image1));
        ui.label_8->setScaledContents(true);    //使图像尺寸与label大小匹配
        ui.label_8->show();
        ui.label_14->setText("半选显示原图");
    }
}