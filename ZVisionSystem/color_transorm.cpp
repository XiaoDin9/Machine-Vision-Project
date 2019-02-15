#pragma execution_character_set("utf-8")
#include "color_transorm.h"
#include <qdebug.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qwidget.h>
#include <iostream>
#include <qobject.h>
#include <string.h>

using namespace std;

extern ZvImage out_image;          //定义图像变量
ZvImage convert_color;      //转换后的图像

bool flag1 = false;     //执行标记
bool flag2 = false;     //确认标记 

QString str = NULL;     //转换的标记
QString input_string = "File";   //从qcomobox 设置初始的默认值
QString choice_string = "Processed image";
QString out_string = NULL;

Color_Transorm::Color_Transorm(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

Color_Transorm::~Color_Transorm()
{
    
}


/*---------------------------------------槽函数的实现-------------------------------------------*/
//设置comboBox 控件的函数
//选择原始图像是来自文件还是摄像头
void Color_Transorm::On_comboBox_activated() {
    input_string = ui.comboBox->itemText(ui.comboBox->currentIndex());
}
//处理后的图像
void Color_Transorm::On_comboBox_4_activated() {
    choice_string = ui.comboBox_4->itemText(ui.comboBox_4->currentIndex());
}
//显示设置选择
void Color_Transorm::On_comboBox_5_activated() {
    out_string = ui.comboBox_5->itemText(ui.comboBox_5->currentIndex());
}

//执行按钮函数
void Color_Transorm::on_run_clicked() {
    flag1 = true;
}
//取消函数实现
void Color_Transorm::on_cancel_clicked() {
    flag1 = false;
    flag2 = false;
}
//确定函数实现
void Color_Transorm::on_sure_clicked() {
    flag2 = true;
    if ((flag1 && flag2) && (out_string != NULL)) color_transorm();
}

//radioButton 函数实现
void Color_Transorm::on_radioButton_clicked() {   //RGB->GRAY
    str = "RGB->GRAY";
}
void Color_Transorm::on_radioButton2_clicked() {  //RGB->HSV
    str = "RGB->HSV";
}
void Color_Transorm::on_radioButton3_clicked() {  //RGB->HLS
    str = "RGB->HLS";
}
void Color_Transorm::on_radioButton4_clicked() {  //RGB->YCrCb
    str = "RGB->YCrCb";
}

extern QImage Mat4QImage(ZvImage img);

//显示函数
void Color_Transorm::show_print() {
    if (out_string == "Original image") {   //打开原图 src_iamge
        QImage image1 = Mat4QImage(out_image);
        ui.label_2->clear();
        ui.label_2->setPixmap(QPixmap::fromImage(image1));
        ui.label_2->setScaledContents(true);//使图像尺寸与label大小匹配
        ui.label_2->show();
    }
    if (out_string == "Processed image") {
        QImage image1 = Mat4QImage(convert_color);
        ui.label_2->clear();
        ui.label_2->setPixmap(QPixmap::fromImage(image1));
        ui.label_2->setScaledContents(true);    //使图像尺寸与label大小匹配
        ui.label_2->show();
    }
}

//颜色转换函数
void Color_Transorm::color_transorm() {
    if (str == "RGB->GRAY") { /*cvtColor(out_image, convert_color, COLOR_RGB2GRAY)*/; show_print();}
    else if (str == "RGB->HSV") { /*cvtColor(out_image, convert_color, COLOR_RGB2HSV)*/; show_print();}
    else if (str == "RGB->HLS") { /*cvtColor(out_image, convert_color, COLOR_RGB2HLS)*/; show_print(); }
    else if (str == "RGB->YCrCb") { /*cvtColor(out_image, convert_color, COLOR_RGB2YCrCb)*/; show_print();}
    else { QMessageBox::information(this, tr("消息提醒框"), tr("请选择要执行的颜色转换操作！")); }   //打开保存消息盒子 
}