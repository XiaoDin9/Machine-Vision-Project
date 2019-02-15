#pragma execution_character_set("utf-8")
// 加载类头文件
#include "color_transorm.h"
#include "filter_function.h"
#include "mainwindow.h"
#include "camera_setparm.h"

ZvImage out_image;                //传值到子窗口的控件

int num = 0;

QString Data_anynas_type = NULL;      //图像数据的解析格式
static int c_countOfImagesToGrab = 200;     //设置连续抓取 1000 帧图像

/* camId 表示要设置哪个相机 {0, 1, 2, 3};
scanId 的取值为 -1：未绑定, 1：开始绑定
即：每一个camId 都有一个状态：scanId;
*/
static int camId = 0;
static int scanId = 0;
static bool Flag_parmSet = false;

Camera_SetParm *C_S;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    //允许嵌套dock
    setDockNestingEnabled(true);
    //记录所有的dock指针
    m_docks.append(ui.dockWidget_3);
    m_docks.append(ui.dockWidget_2);

    // 对窗体的布局的设置

    addDockWidget(Qt::RightDockWidgetArea, ui.dockWidget_3);
    ui.dockWidget_3->setMinimumWidth(255);    // 左右的需要设置 最大的宽，（以最左、右对齐） 
    
    // 在窗体中添加 树形控件
    QTreeWidget *treeWidget = new QTreeWidget;  //创建树形控件  
    QStringList headers;        //树头  
    headers << "Property" << "Value";
    treeWidget->setHeaderLabels(headers);

    ui.dockWidget_3->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);  //锚接部件 允许停靠的区域，左右  
    ui.dockWidget_3->setWidget(treeWidget);  //设置锚接部件的内容 TreeWidget  


    addDockWidget(Qt::BottomDockWidgetArea, ui.dockWidget_2);
    ui.dockWidget_2->setMinimumHeight(145);      // 上下的需要设置 最大的高，（以最上、下对齐）

    // 在窗体中添加 树形控件
    QTreeWidget *treeWidget1 = new QTreeWidget;  //创建树形控件  
    QStringList headers1;        //树头  
    headers1 << "Level" << "Time" << "Source" << "Message";
    treeWidget1->setHeaderLabels(headers1);

    //获取时间
    QDateTime time = QDateTime::currentDateTime();             //获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd");   //设置显示格式

    QStringList rootTextList;       //树的根节点, 下面的取值都是可以自己以后设定的 
    rootTextList << "!Information" << str << "Basler acA2500-14gm(22533411)" << "Start grab one picture";    //添加选项 Root --- 0  
    QTreeWidgetItem *root = new QTreeWidgetItem(treeWidget1, rootTextList);

    ui.dockWidget_2->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);  //锚接部件 允许停靠的区域，左右  
    ui.dockWidget_2->setWidget(treeWidget1);  //设置锚接部件的内容 TreeWidget 

    this->setWindowTitle("Image process Porject");    //给窗口设置标题
    this->setWindowIcon(QIcon("./Qt ico/Windows Media Player.ico"));    //给窗口添加图标

}

MainWindow::~MainWindow()
{
}


/*=======================================各个窗体布局====================================*/
void MainWindow::removeAllDock()
{
    for (int i = 0; i < 9; ++i)
    {
        removeDockWidget(m_docks[i]);
    }
}
/// \brief 显示指定序号的dock
/// \param index 指定序号，如果不指定，则会显示所有
void MainWindow::showDock(const QList<int> &index)
{
    if (index.isEmpty())
    {
        for (int i = 0; i < 9; ++i)
        {
            m_docks[i]->show();
        }
    }
    else
    {
        foreach(int i, index) {
            m_docks[i]->show();
        }
    }
}

/*===========================================Help Menu===========================================*/
void MainWindow::ZV_Version_triggered() {
    QMessageBox::information(this, tr("ZVision 版本"), tr(ZV_VERSION));   //打开保存消息盒
}

/*===========================================Set Menu===========================================*/
void MainWindow::ZV_CameraTyep_Gige_triggered() {
    Data_anynas_type = "GIGE";
}

void MainWindow::ZV_CameraTyep_Opencv_triggered() {
    Data_anynas_type = "OPENCV";

}

void MainWindow::ZV_CameraTyep_V4L2_triggered() {
    Data_anynas_type = "V4L2";
}

void MainWindow::ZV_CameraTyep_Aravis_triggered() {
    Data_anynas_type = "Aravis";
}

void MainWindow::ZV_CameraParmSet_triggered() {
    // 新建pylon ImageFormatConverter对象.
    C_S = new Camera_SetParm;
    C_S->show();    
    Flag_parmSet = true;
}

/*===========================================Define Tools===========================================*/
void MainWindow::on_action_Cammera() {
    if(Data_anynas_type == NULL)
        QMessageBox::critical(NULL, "critical", "请先设置好图像数据的解析格式！！！", QMessageBox::Ok);
    else {
        if (!Flag_parmSet) {
            if (QMessageBox::information(this, tr("ZVision"), tr(" 采用默认参数打开Camera ? "), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == 65536)  //打开保存消息盒
                ZV_CameraParmSet_triggered();       // 调用 opencv的 相机初始化参数设置 函数
            QMessageBox::information(this, tr("提醒"), tr("Please reopen Camera!"));   //打开保存消息盒
        }
        else {
            /* 调用Opencv 的方式
            对相机进行初始化的参数设置
            */
            //C_S->camsetparam;   //引进从QT 界面配置的参数
            int64_t time_out;

            ZvImage img = zv_imgCreate();
            zv_modInit(true);
            //开始扫描相机, 检索系统默认配置了 几个 相机
            if (!zv_camScan("TIS")) 
            {    // type 的取值有四种  "All","binding","GIGE", "USB" , 可以调整设置的相机最大数=1；
                int n = zv_camCount();
                if (!zv_camOpen(camId, scanId))
                {
                        //相机 初始化 参数设置
                        //zvSetCameraExposureTime(camId, C_S->camsetparam->ExpTime);

                        if (!zv_camSetROI(camId, 200, 100, 640, 480)) {

                            // 得到 相机的参数信息、曝光时间
                            int offsetX_out, offsetY_out, width_out, height_out;
                            if (1)//!zv_camGetROI(camId, &offsetX_out, &offsetY_out, &width_out, &height_out)) 
                            {
                                double dtime = 0;
                                zv_camGetExposure(camId, &dtime);     // 得到曝光的时间信息   error 
                                time_out = dtime;
                                ///////////////打印相机输出信息/////////////////
                                cout << "Now Use ID : " << C_S->camsetparam->m_strUserId.toStdString() << endl;
                                cout << "Camera name : " << C_S->camsetparam->m_strCamName.toStdString() << endl;
                                cout << "Banding camId : " << camId << endl;
                                cout << "Image format : " << C_S->camsetparam->m_strPixelFormat.toStdString() << endl;
                                cout << "Image depth : " << C_S->camsetparam->m_Depth << endl;
                                //cout << "offsetX : " << offsetX_out << endl;
                                //cout << "offsetY : " << offsetY_out << endl;
                                //cout << "width : " << width_out << endl;
                                //cout << "height : " << height_out << endl;
                                cout << "ExposureTime : " << time_out << endl;
                            }
                        }
                    }
                    else
                        QMessageBox::critical(NULL, "critical", "相机没有被正确的打开！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            }

            //直接打开相机 读取每一帧数据
            cout << "start to grab each image !" << endl;
            int cnt = 0;
            while (c_countOfImagesToGrab--) {
                zv_camGrab(img, camId);
                cout << "use grab" << endl;

                cout << "Read " << 200 - c_countOfImagesToGrab << "frame picture!" << endl;
                
                zv_fileWriteImage(img, QString("E:/aa%1.jpg").arg(cnt).toLocal8Bit().data(), NULL, 0);
                cnt++;

                if (c_countOfImagesToGrab == 0)
                {
                    if (!zv_modExit())
                        cout << " Release resources is succeed!" << endl;
                    break;
                }
            }
        }
    }
}    
