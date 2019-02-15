#include "mainwindow.h"
#include "color_transorm.h"
#include "filter_function.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <iostream>
#include <stdio.h>
#include <qdebug.h>

int main03(int argc, char* argv[]){
    QApplication a(argc, argv);
    MainWindow w1;        //创建主窗口类的对象，并显示
    w1.show();
    return a.exec();
}

