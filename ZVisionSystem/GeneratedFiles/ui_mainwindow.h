/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionOpen_file;
    QAction *actionOpen_Camer;
    QAction *actionSave;
    QAction *Grayscale_match;
    QAction *actionOriginal_image;
    QAction *action;
    QAction *actionOpen;
    QAction *actionSave_2;
    QAction *actionSave_3;
    QAction *actionClose;
    QAction *actionImage_filtering;
    QAction *actionColor_Transformation;
    QAction *actionGeometric_Transformation;
    QAction *actionImproved_Contrast;
    QAction *actionOutput_image2;
    QAction *actionOutput_image3;
    QAction *actionOutput_image_2;
    QAction *actionCorrosion;
    QAction *actionExpansion;
    QAction *actionBoxFilter;
    QAction *actionBlur_Filter;
    QAction *actionGaussianBlur;
    QAction *actionMedianBlur;
    QAction *actionBilateralFilter;
    QAction *actionLogarithmic_enhance;
    QAction *Canny_edge_detection;
    QAction *actionHistogram_equalization;
    QAction *actionLaplacian_Image_Enhancement;
    QAction *actionFilter;
    QAction *Open_Cammera;
    QAction *actionProcessed_image;
    QAction *action_open_opreator;
    QAction *actionClose_operator;
    QAction *actionSobel_edge;
    QAction *actionDynamic_binarization;
    QAction *actionInter_frame_subtraction;
    QAction *actionThree_frame_differential;
    QAction *actionShape_match;
    QAction *actionSet_ROI;
    QAction *actionRotary_offset_compensation;
    QAction *actionFeature_extraction;
    QAction *actionSpot_analysis;
    QAction *actionEdges_and_contours;
    QAction *actionNumerical_operations;
    QAction *actionGeometric_operations;
    QAction *actionLogic_operation;
    QAction *actionCoordinate_transformation;
    QAction *actionZVision_help;
    QAction *ZV_Help;
    QAction *ZV_Version;
    QAction *ZV_CameraParam_Set;
    QAction *ZV_CAMTYPE_GIGE;
    QAction *ZV_CAMTYPE_V4L2;
    QAction *ZV_CAMTYPE_OPENCV;
    QAction *ZV_CAMTYPE_ARAVIS;
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QLabel *label;
    QGroupBox *groupBox_3;
    QMenuBar *menuBar;
    QMenu *File;
    QMenu *menuOpen;
    QMenu *Image_process;
    QMenu *previous_process;
    QMenu *Image_init;
    QMenu *menuMorphological;
    QMenu *menuEnhance;
    QMenu *Default_extraction;
    QMenu *menuGray_difference;
    QMenu *View;
    QMenu *Help;
    QMenu *menu;
    QMenu *Set_Menu;
    QMenu *menuZV_Camera_Type;
    QToolBar *mainToolBar;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_2;
    QDockWidget *dockWidget_3;
    QWidget *dockWidgetContents_3;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(1477, 900);
        MainWindowClass->setAutoFillBackground(true);
        actionOpen_file = new QAction(MainWindowClass);
        actionOpen_file->setObjectName(QStringLiteral("actionOpen_file"));
        actionOpen_Camer = new QAction(MainWindowClass);
        actionOpen_Camer->setObjectName(QStringLiteral("actionOpen_Camer"));
        actionSave = new QAction(MainWindowClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon;
        icon.addFile(QStringLiteral("Qt ico/File save1.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon);
        Grayscale_match = new QAction(MainWindowClass);
        Grayscale_match->setObjectName(QStringLiteral("Grayscale_match"));
        Grayscale_match->setCheckable(true);
        actionOriginal_image = new QAction(MainWindowClass);
        actionOriginal_image->setObjectName(QStringLiteral("actionOriginal_image"));
        actionOriginal_image->setCheckable(true);
        action = new QAction(MainWindowClass);
        action->setObjectName(QStringLiteral("action"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("Qt ico/File open.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action->setIcon(icon1);
        actionOpen = new QAction(MainWindowClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave_2 = new QAction(MainWindowClass);
        actionSave_2->setObjectName(QStringLiteral("actionSave_2"));
        actionSave_3 = new QAction(MainWindowClass);
        actionSave_3->setObjectName(QStringLiteral("actionSave_3"));
        actionClose = new QAction(MainWindowClass);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionImage_filtering = new QAction(MainWindowClass);
        actionImage_filtering->setObjectName(QStringLiteral("actionImage_filtering"));
        actionColor_Transformation = new QAction(MainWindowClass);
        actionColor_Transformation->setObjectName(QStringLiteral("actionColor_Transformation"));
        actionGeometric_Transformation = new QAction(MainWindowClass);
        actionGeometric_Transformation->setObjectName(QStringLiteral("actionGeometric_Transformation"));
        actionImproved_Contrast = new QAction(MainWindowClass);
        actionImproved_Contrast->setObjectName(QStringLiteral("actionImproved_Contrast"));
        actionOutput_image2 = new QAction(MainWindowClass);
        actionOutput_image2->setObjectName(QStringLiteral("actionOutput_image2"));
        actionOutput_image3 = new QAction(MainWindowClass);
        actionOutput_image3->setObjectName(QStringLiteral("actionOutput_image3"));
        actionOutput_image_2 = new QAction(MainWindowClass);
        actionOutput_image_2->setObjectName(QStringLiteral("actionOutput_image_2"));
        actionCorrosion = new QAction(MainWindowClass);
        actionCorrosion->setObjectName(QStringLiteral("actionCorrosion"));
        actionCorrosion->setCheckable(true);
        actionExpansion = new QAction(MainWindowClass);
        actionExpansion->setObjectName(QStringLiteral("actionExpansion"));
        actionExpansion->setCheckable(true);
        actionBoxFilter = new QAction(MainWindowClass);
        actionBoxFilter->setObjectName(QStringLiteral("actionBoxFilter"));
        actionBlur_Filter = new QAction(MainWindowClass);
        actionBlur_Filter->setObjectName(QStringLiteral("actionBlur_Filter"));
        actionGaussianBlur = new QAction(MainWindowClass);
        actionGaussianBlur->setObjectName(QStringLiteral("actionGaussianBlur"));
        actionMedianBlur = new QAction(MainWindowClass);
        actionMedianBlur->setObjectName(QStringLiteral("actionMedianBlur"));
        actionBilateralFilter = new QAction(MainWindowClass);
        actionBilateralFilter->setObjectName(QStringLiteral("actionBilateralFilter"));
        actionLogarithmic_enhance = new QAction(MainWindowClass);
        actionLogarithmic_enhance->setObjectName(QStringLiteral("actionLogarithmic_enhance"));
        actionLogarithmic_enhance->setCheckable(true);
        Canny_edge_detection = new QAction(MainWindowClass);
        Canny_edge_detection->setObjectName(QStringLiteral("Canny_edge_detection"));
        Canny_edge_detection->setCheckable(true);
        actionHistogram_equalization = new QAction(MainWindowClass);
        actionHistogram_equalization->setObjectName(QStringLiteral("actionHistogram_equalization"));
        actionHistogram_equalization->setCheckable(true);
        actionLaplacian_Image_Enhancement = new QAction(MainWindowClass);
        actionLaplacian_Image_Enhancement->setObjectName(QStringLiteral("actionLaplacian_Image_Enhancement"));
        actionLaplacian_Image_Enhancement->setCheckable(true);
        actionFilter = new QAction(MainWindowClass);
        actionFilter->setObjectName(QStringLiteral("actionFilter"));
        Open_Cammera = new QAction(MainWindowClass);
        Open_Cammera->setObjectName(QStringLiteral("Open_Cammera"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("Qt ico/Camera.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Open_Cammera->setIcon(icon2);
        actionProcessed_image = new QAction(MainWindowClass);
        actionProcessed_image->setObjectName(QStringLiteral("actionProcessed_image"));
        actionProcessed_image->setCheckable(true);
        action_open_opreator = new QAction(MainWindowClass);
        action_open_opreator->setObjectName(QStringLiteral("action_open_opreator"));
        action_open_opreator->setCheckable(true);
        actionClose_operator = new QAction(MainWindowClass);
        actionClose_operator->setObjectName(QStringLiteral("actionClose_operator"));
        actionClose_operator->setCheckable(true);
        actionSobel_edge = new QAction(MainWindowClass);
        actionSobel_edge->setObjectName(QStringLiteral("actionSobel_edge"));
        actionSobel_edge->setCheckable(true);
        actionDynamic_binarization = new QAction(MainWindowClass);
        actionDynamic_binarization->setObjectName(QStringLiteral("actionDynamic_binarization"));
        actionInter_frame_subtraction = new QAction(MainWindowClass);
        actionInter_frame_subtraction->setObjectName(QStringLiteral("actionInter_frame_subtraction"));
        actionInter_frame_subtraction->setCheckable(true);
        actionThree_frame_differential = new QAction(MainWindowClass);
        actionThree_frame_differential->setObjectName(QStringLiteral("actionThree_frame_differential"));
        actionThree_frame_differential->setCheckable(true);
        actionShape_match = new QAction(MainWindowClass);
        actionShape_match->setObjectName(QStringLiteral("actionShape_match"));
        actionSet_ROI = new QAction(MainWindowClass);
        actionSet_ROI->setObjectName(QStringLiteral("actionSet_ROI"));
        actionRotary_offset_compensation = new QAction(MainWindowClass);
        actionRotary_offset_compensation->setObjectName(QStringLiteral("actionRotary_offset_compensation"));
        actionFeature_extraction = new QAction(MainWindowClass);
        actionFeature_extraction->setObjectName(QStringLiteral("actionFeature_extraction"));
        actionSpot_analysis = new QAction(MainWindowClass);
        actionSpot_analysis->setObjectName(QStringLiteral("actionSpot_analysis"));
        actionEdges_and_contours = new QAction(MainWindowClass);
        actionEdges_and_contours->setObjectName(QStringLiteral("actionEdges_and_contours"));
        actionNumerical_operations = new QAction(MainWindowClass);
        actionNumerical_operations->setObjectName(QStringLiteral("actionNumerical_operations"));
        actionGeometric_operations = new QAction(MainWindowClass);
        actionGeometric_operations->setObjectName(QStringLiteral("actionGeometric_operations"));
        actionLogic_operation = new QAction(MainWindowClass);
        actionLogic_operation->setObjectName(QStringLiteral("actionLogic_operation"));
        actionCoordinate_transformation = new QAction(MainWindowClass);
        actionCoordinate_transformation->setObjectName(QStringLiteral("actionCoordinate_transformation"));
        actionZVision_help = new QAction(MainWindowClass);
        actionZVision_help->setObjectName(QStringLiteral("actionZVision_help"));
        ZV_Help = new QAction(MainWindowClass);
        ZV_Help->setObjectName(QStringLiteral("ZV_Help"));
        ZV_Version = new QAction(MainWindowClass);
        ZV_Version->setObjectName(QStringLiteral("ZV_Version"));
        ZV_CameraParam_Set = new QAction(MainWindowClass);
        ZV_CameraParam_Set->setObjectName(QStringLiteral("ZV_CameraParam_Set"));
        ZV_CAMTYPE_GIGE = new QAction(MainWindowClass);
        ZV_CAMTYPE_GIGE->setObjectName(QStringLiteral("ZV_CAMTYPE_GIGE"));
        ZV_CAMTYPE_GIGE->setCheckable(true);
        ZV_CAMTYPE_V4L2 = new QAction(MainWindowClass);
        ZV_CAMTYPE_V4L2->setObjectName(QStringLiteral("ZV_CAMTYPE_V4L2"));
        ZV_CAMTYPE_V4L2->setCheckable(true);
        ZV_CAMTYPE_OPENCV = new QAction(MainWindowClass);
        ZV_CAMTYPE_OPENCV->setObjectName(QStringLiteral("ZV_CAMTYPE_OPENCV"));
        ZV_CAMTYPE_OPENCV->setCheckable(true);
        ZV_CAMTYPE_ARAVIS = new QAction(MainWindowClass);
        ZV_CAMTYPE_ARAVIS->setObjectName(QStringLiteral("ZV_CAMTYPE_ARAVIS"));
        ZV_CAMTYPE_ARAVIS->setCheckable(true);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 1220, 700));
        groupBox->setStyleSheet(QStringLiteral(""));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 1220, 700));
        QFont font;
        font.setFamily(QStringLiteral("AngsanaUPC"));
        font.setPointSize(48);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label->setAlignment(Qt::AlignCenter);
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 700, 1475, 145));
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1477, 23));
        File = new QMenu(menuBar);
        File->setObjectName(QStringLiteral("File"));
        menuOpen = new QMenu(File);
        menuOpen->setObjectName(QStringLiteral("menuOpen"));
        Image_process = new QMenu(menuBar);
        Image_process->setObjectName(QStringLiteral("Image_process"));
        previous_process = new QMenu(menuBar);
        previous_process->setObjectName(QStringLiteral("previous_process"));
        Image_init = new QMenu(previous_process);
        Image_init->setObjectName(QStringLiteral("Image_init"));
        menuMorphological = new QMenu(Image_init);
        menuMorphological->setObjectName(QStringLiteral("menuMorphological"));
        menuEnhance = new QMenu(Image_init);
        menuEnhance->setObjectName(QStringLiteral("menuEnhance"));
        Default_extraction = new QMenu(previous_process);
        Default_extraction->setObjectName(QStringLiteral("Default_extraction"));
        menuGray_difference = new QMenu(Default_extraction);
        menuGray_difference->setObjectName(QStringLiteral("menuGray_difference"));
        View = new QMenu(menuBar);
        View->setObjectName(QStringLiteral("View"));
        Help = new QMenu(menuBar);
        Help->setObjectName(QStringLiteral("Help"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        Set_Menu = new QMenu(menuBar);
        Set_Menu->setObjectName(QStringLiteral("Set_Menu"));
        menuZV_Camera_Type = new QMenu(Set_Menu);
        menuZV_Camera_Type->setObjectName(QStringLiteral("menuZV_Camera_Type"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        dockWidget_2 = new QDockWidget(MainWindowClass);
        dockWidget_2->setObjectName(QStringLiteral("dockWidget_2"));
        QFont font1;
        font1.setFamily(QStringLiteral("Aharoni"));
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setWeight(75);
        dockWidget_2->setFont(font1);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        dockWidget_2->setWidget(dockWidgetContents_2);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidget_2);
        dockWidget_3 = new QDockWidget(MainWindowClass);
        dockWidget_3->setObjectName(QStringLiteral("dockWidget_3"));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        dockWidget_3->setWidget(dockWidgetContents_3);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_3);
        dockWidget_2->raise();
        dockWidget_3->raise();

        menuBar->addAction(File->menuAction());
        menuBar->addAction(Set_Menu->menuAction());
        menuBar->addAction(previous_process->menuAction());
        menuBar->addAction(Image_process->menuAction());
        menuBar->addAction(View->menuAction());
        menuBar->addAction(Help->menuAction());
        menuBar->addAction(menu->menuAction());
        File->addAction(menuOpen->menuAction());
        File->addSeparator();
        File->addAction(actionSave_3);
        File->addSeparator();
        File->addAction(actionClose);
        menuOpen->addAction(actionOpen_file);
        menuOpen->addAction(actionOpen_Camer);
        Image_process->addAction(Grayscale_match);
        Image_process->addSeparator();
        Image_process->addAction(actionShape_match);
        Image_process->addSeparator();
        Image_process->addAction(actionSet_ROI);
        Image_process->addSeparator();
        Image_process->addAction(actionRotary_offset_compensation);
        Image_process->addSeparator();
        Image_process->addAction(actionFeature_extraction);
        Image_process->addSeparator();
        Image_process->addAction(actionSpot_analysis);
        Image_process->addSeparator();
        Image_process->addAction(actionEdges_and_contours);
        previous_process->addAction(Image_init->menuAction());
        previous_process->addSeparator();
        previous_process->addAction(actionImproved_Contrast);
        previous_process->addSeparator();
        previous_process->addAction(actionGeometric_Transformation);
        previous_process->addSeparator();
        previous_process->addAction(Default_extraction->menuAction());
        Image_init->addAction(menuMorphological->menuAction());
        Image_init->addSeparator();
        Image_init->addAction(menuEnhance->menuAction());
        Image_init->addSeparator();
        Image_init->addAction(actionColor_Transformation);
        Image_init->addSeparator();
        Image_init->addAction(actionFilter);
        menuMorphological->addAction(actionCorrosion);
        menuMorphological->addSeparator();
        menuMorphological->addAction(actionExpansion);
        menuMorphological->addSeparator();
        menuMorphological->addAction(action_open_opreator);
        menuMorphological->addSeparator();
        menuMorphological->addAction(actionClose_operator);
        menuEnhance->addAction(actionLogarithmic_enhance);
        menuEnhance->addSeparator();
        menuEnhance->addAction(Canny_edge_detection);
        menuEnhance->addSeparator();
        menuEnhance->addAction(actionHistogram_equalization);
        menuEnhance->addSeparator();
        menuEnhance->addAction(actionLaplacian_Image_Enhancement);
        menuEnhance->addSeparator();
        menuEnhance->addAction(actionSobel_edge);
        Default_extraction->addAction(menuGray_difference->menuAction());
        Default_extraction->addSeparator();
        Default_extraction->addAction(actionDynamic_binarization);
        menuGray_difference->addAction(actionInter_frame_subtraction);
        menuGray_difference->addSeparator();
        menuGray_difference->addAction(actionThree_frame_differential);
        View->addAction(actionProcessed_image);
        View->addAction(actionCoordinate_transformation);
        Help->addAction(actionNumerical_operations);
        Help->addAction(actionGeometric_operations);
        Help->addAction(actionLogic_operation);
        menu->addAction(ZV_Help);
        menu->addSeparator();
        menu->addAction(ZV_Version);
        Set_Menu->addAction(menuZV_Camera_Type->menuAction());
        Set_Menu->addSeparator();
        Set_Menu->addAction(ZV_CameraParam_Set);
        menuZV_Camera_Type->addAction(ZV_CAMTYPE_GIGE);
        menuZV_Camera_Type->addSeparator();
        menuZV_Camera_Type->addAction(ZV_CAMTYPE_V4L2);
        menuZV_Camera_Type->addSeparator();
        menuZV_Camera_Type->addAction(ZV_CAMTYPE_OPENCV);
        menuZV_Camera_Type->addSeparator();
        menuZV_Camera_Type->addAction(ZV_CAMTYPE_ARAVIS);
        mainToolBar->addAction(action);
        mainToolBar->addAction(Open_Cammera);
        mainToolBar->addAction(actionSave);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", Q_NULLPTR));
        actionOpen_file->setText(QApplication::translate("MainWindowClass", "Folder", Q_NULLPTR));
        actionOpen_Camer->setText(QApplication::translate("MainWindowClass", "Camer", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindowClass", "\344\277\235\345\255\230", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("MainWindowClass", "\344\277\235\345\255\230\346\226\207\344\273\266", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSave->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+S", Q_NULLPTR));
        Grayscale_match->setText(QApplication::translate("MainWindowClass", "Grayscale match", Q_NULLPTR));
        actionOriginal_image->setText(QApplication::translate("MainWindowClass", "Original image", Q_NULLPTR));
        action->setText(QApplication::translate("MainWindowClass", "\346\211\223\345\274\200\346\226\207\344\273\266", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindowClass", "Open", Q_NULLPTR));
        actionSave_2->setText(QApplication::translate("MainWindowClass", "Save", Q_NULLPTR));
        actionSave_3->setText(QApplication::translate("MainWindowClass", "Save", Q_NULLPTR));
        actionClose->setText(QApplication::translate("MainWindowClass", "Close", Q_NULLPTR));
        actionImage_filtering->setText(QApplication::translate("MainWindowClass", "Image Filtering", Q_NULLPTR));
        actionColor_Transformation->setText(QApplication::translate("MainWindowClass", "Color Transformation", Q_NULLPTR));
        actionGeometric_Transformation->setText(QApplication::translate("MainWindowClass", "Geometric Transformation", Q_NULLPTR));
        actionImproved_Contrast->setText(QApplication::translate("MainWindowClass", "Improved Contrast", Q_NULLPTR));
        actionOutput_image2->setText(QApplication::translate("MainWindowClass", "Output image2", Q_NULLPTR));
        actionOutput_image3->setText(QApplication::translate("MainWindowClass", "Output image3", Q_NULLPTR));
        actionOutput_image_2->setText(QApplication::translate("MainWindowClass", "Output_image", Q_NULLPTR));
        actionCorrosion->setText(QApplication::translate("MainWindowClass", "Erode", Q_NULLPTR));
        actionExpansion->setText(QApplication::translate("MainWindowClass", "Dilate", Q_NULLPTR));
        actionBoxFilter->setText(QApplication::translate("MainWindowClass", "BoxFilter", Q_NULLPTR));
        actionBlur_Filter->setText(QApplication::translate("MainWindowClass", "Blur_Filter", Q_NULLPTR));
        actionGaussianBlur->setText(QApplication::translate("MainWindowClass", "GaussianBlur", Q_NULLPTR));
        actionMedianBlur->setText(QApplication::translate("MainWindowClass", "medianBlur", Q_NULLPTR));
        actionBilateralFilter->setText(QApplication::translate("MainWindowClass", "bilateralFilter", Q_NULLPTR));
        actionLogarithmic_enhance->setText(QApplication::translate("MainWindowClass", "Logarithmic enhance", Q_NULLPTR));
        Canny_edge_detection->setText(QApplication::translate("MainWindowClass", "Canny edge detection", Q_NULLPTR));
        actionHistogram_equalization->setText(QApplication::translate("MainWindowClass", "Histogram equalization", Q_NULLPTR));
        actionLaplacian_Image_Enhancement->setText(QApplication::translate("MainWindowClass", "Laplacian Image Enhancement", Q_NULLPTR));
        actionFilter->setText(QApplication::translate("MainWindowClass", "Filter", Q_NULLPTR));
        Open_Cammera->setText(QApplication::translate("MainWindowClass", "\346\211\223\345\274\200Cammera", Q_NULLPTR));
        actionProcessed_image->setText(QApplication::translate("MainWindowClass", "Processed image", Q_NULLPTR));
        action_open_opreator->setText(QApplication::translate("MainWindowClass", "Open_operator", Q_NULLPTR));
        actionClose_operator->setText(QApplication::translate("MainWindowClass", "Close_operator", Q_NULLPTR));
        actionSobel_edge->setText(QApplication::translate("MainWindowClass", "Sobel edge", Q_NULLPTR));
        actionDynamic_binarization->setText(QApplication::translate("MainWindowClass", "Dynamic binarization", Q_NULLPTR));
        actionInter_frame_subtraction->setText(QApplication::translate("MainWindowClass", "Inter-frame subtraction", Q_NULLPTR));
        actionThree_frame_differential->setText(QApplication::translate("MainWindowClass", "Three-frame differential", Q_NULLPTR));
        actionShape_match->setText(QApplication::translate("MainWindowClass", "Shape\n"
"match", Q_NULLPTR));
        actionSet_ROI->setText(QApplication::translate("MainWindowClass", "Set ROI", Q_NULLPTR));
        actionRotary_offset_compensation->setText(QApplication::translate("MainWindowClass", "Rotary offset compensation", Q_NULLPTR));
        actionFeature_extraction->setText(QApplication::translate("MainWindowClass", "Feature extraction", Q_NULLPTR));
        actionSpot_analysis->setText(QApplication::translate("MainWindowClass", "Spot analysis", Q_NULLPTR));
        actionEdges_and_contours->setText(QApplication::translate("MainWindowClass", "Edges and contours", Q_NULLPTR));
        actionNumerical_operations->setText(QApplication::translate("MainWindowClass", "Numerical operations", Q_NULLPTR));
        actionGeometric_operations->setText(QApplication::translate("MainWindowClass", "Geometric operations", Q_NULLPTR));
        actionLogic_operation->setText(QApplication::translate("MainWindowClass", "logic operation", Q_NULLPTR));
        actionCoordinate_transformation->setText(QApplication::translate("MainWindowClass", "Coordinate transformation", Q_NULLPTR));
        actionZVision_help->setText(QApplication::translate("MainWindowClass", "ZVision help", Q_NULLPTR));
        ZV_Help->setText(QApplication::translate("MainWindowClass", "ZVision Help", Q_NULLPTR));
        ZV_Version->setText(QApplication::translate("MainWindowClass", "About ZVision", Q_NULLPTR));
        ZV_CameraParam_Set->setText(QApplication::translate("MainWindowClass", "ZV_CameraParam_Set", Q_NULLPTR));
        ZV_CAMTYPE_GIGE->setText(QApplication::translate("MainWindowClass", "ZV_CAMTYPE_GIGE", Q_NULLPTR));
        ZV_CAMTYPE_V4L2->setText(QApplication::translate("MainWindowClass", "ZV_CAMTYPE_V4L2", Q_NULLPTR));
        ZV_CAMTYPE_OPENCV->setText(QApplication::translate("MainWindowClass", "ZV_CAMTYPE_OPENCV", Q_NULLPTR));
        ZV_CAMTYPE_ARAVIS->setText(QApplication::translate("MainWindowClass", "ZV_CAMTYPE_ARAVIS", Q_NULLPTR));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("MainWindowClass", "ZVision 0.0.1", Q_NULLPTR));
        groupBox_3->setTitle(QString());
        File->setTitle(QApplication::translate("MainWindowClass", "\346\226\207\344\273\266(F)", Q_NULLPTR));
        menuOpen->setTitle(QApplication::translate("MainWindowClass", "File", Q_NULLPTR));
        Image_process->setTitle(QApplication::translate("MainWindowClass", "\345\233\276\345\203\217\345\244\204\347\220\206", Q_NULLPTR));
        previous_process->setTitle(QApplication::translate("MainWindowClass", "\345\233\276\345\203\217\351\242\204\345\244\204\347\220\206", Q_NULLPTR));
        Image_init->setTitle(QApplication::translate("MainWindowClass", "Image Initialization", Q_NULLPTR));
        menuMorphological->setTitle(QApplication::translate("MainWindowClass", "Morphological", Q_NULLPTR));
        menuEnhance->setTitle(QApplication::translate("MainWindowClass", "Enhance", Q_NULLPTR));
        Default_extraction->setTitle(QApplication::translate("MainWindowClass", "Defect extraction", Q_NULLPTR));
        menuGray_difference->setTitle(QApplication::translate("MainWindowClass", "Gray difference", Q_NULLPTR));
        View->setTitle(QApplication::translate("MainWindowClass", "\350\247\206\345\233\276", Q_NULLPTR));
        Help->setTitle(QApplication::translate("MainWindowClass", "\345\233\276\345\203\217\350\277\220\347\256\227", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindowClass", "\345\270\256\345\212\251", Q_NULLPTR));
        Set_Menu->setTitle(QApplication::translate("MainWindowClass", "\350\256\276\347\275\256", Q_NULLPTR));
        menuZV_Camera_Type->setTitle(QApplication::translate("MainWindowClass", "ZV_Camera_Type", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
