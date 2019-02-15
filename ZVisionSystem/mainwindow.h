#ifndef IMAGE_PROGRAM1_H
#define IMAGE_PROGRAM1_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

//加载QT API.
#include <qdebug.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qwidget.h>
#include "qprocess.h" 
#include <qdir.h>
#include <qtextcodec.h>
#include <qdatetime.h>
#include <QTextEdit> 
#include <QTreeWidget>
#include <qmutex.h>


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "zv.h"

//命名空间.  
using namespace std;

#ifdef _DEBUG
#pragma comment( lib, "ZVisiond.lib" ) 
#else
#pragma comment( lib, "ZVision.lib" ) 
#endif

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
//     void view_show();
//     void GrabShow();

    /*=================dock窗体的函数声明================*/
    //移除并隐藏所有dock
    void removeAllDock();
    //显示dock窗口
    void showDock(const QList<int>& index = QList<int>());

private:
    Ui::MainWindowClass ui;
    QMutex m_mutex;  //创建线程的互斥向量

    QList<QDockWidget*> m_docks;///< 记录所有dockWidget的指针
    
/*---------------------------------------------------------*/
/*------------建立信号、必须在private slots：下面----------*/
/*---------------------------------------------------------*/
private slots :
    //help menu
    void ZV_Version_triggered();

    //set menu
    void ZV_CameraParmSet_triggered();
    void ZV_CameraTyep_Gige_triggered();
    void ZV_CameraTyep_Opencv_triggered();
    void ZV_CameraTyep_V4L2_triggered();
    void ZV_CameraTyep_Aravis_triggered();

    //void Action_Filefolder_triggered()；
    //Tools 
     void on_action_Cammera();
//         void Action_Save_triggered();
//         void Action_Close_triggered();
//         void Action_Color_Transformation_triggered();
//         void on_actionFilter_triggered();
//         void on_actionmenuEnhance_triggered();
// 
//         void on_Corrosion_triggered();
//         void on_Expansion_triggered();
//         void on_Open_operator_triggered();
//         void on_Close_operator_triggered();
// 
//         void on_Logarithmic_enhance_triggered();
//         void on_Canny_edge_detection_triggered();
//         void on_Histogram_equalization_triggered();
//         void on_Laplacian_enhancement_triggered();
//         void on_actionSobel_edge();
// 
//         void on_next_picture_clicked();
//         void on_Porcessed_image_view();
//         void on_last_image_view();
// 
//         void on_actionInter_frame_subtraction();
//         void on_actionThree_frame_differential();
// 
//         void on_Grayscale_match();
// 
//         void on_play_clicked();
//         void on_PauseGrabbing_clicked();
//         void on_StopPlay_clickede();
};

#endif // IMAGE_PROGRAM1_H
