#include "Test.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Test w;                    //调用Testz类的构造函数
    w.showMaximized();
    return a.exec();
}
