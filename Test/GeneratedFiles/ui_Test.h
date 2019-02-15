/********************************************************************************
** Form generated from reading UI file 'Test.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter_3;
    QTextBrowser *textStat;
    QTreeWidget *treeTest;
    QSplitter *splitter_5;
    QSplitter *splitter_4;
    QPushButton *btnTest;
    QPushButton *btnPause;
    QListWidget *listNG;
    QGraphicsView *grpImageSrc;
    QTextBrowser *textLog;
    QSplitter *splitter;
    QComboBox *cboSrcInfo;
    QComboBox *cboDstInfo;
    QGraphicsView *grpImageDst;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TestClass)
    {
        if (TestClass->objectName().isEmpty())
            TestClass->setObjectName(QStringLiteral("TestClass"));
        TestClass->resize(1270, 841);
        centralWidget = new QWidget(TestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter_3 = new QSplitter(centralWidget);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Vertical);
        textStat = new QTextBrowser(splitter_3);
        textStat->setObjectName(QStringLiteral("textStat"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textStat->sizePolicy().hasHeightForWidth());
        textStat->setSizePolicy(sizePolicy);
        textStat->setMinimumSize(QSize(240, 64));
        textStat->setMaximumSize(QSize(240, 81));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\260\345\256\213\344\275\223"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        textStat->setFont(font);
        textStat->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textStat->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        splitter_3->addWidget(textStat);
        treeTest = new QTreeWidget(splitter_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeTest->setHeaderItem(__qtreewidgetitem);
        treeTest->setObjectName(QStringLiteral("treeTest"));
        treeTest->setMinimumSize(QSize(200, 0));
        treeTest->setSelectionMode(QAbstractItemView::MultiSelection);
        splitter_3->addWidget(treeTest);
        treeTest->header()->setVisible(false);
        splitter_5 = new QSplitter(splitter_3);
        splitter_5->setObjectName(QStringLiteral("splitter_5"));
        splitter_5->setOrientation(Qt::Horizontal);
        splitter_4 = new QSplitter(splitter_5);
        splitter_4->setObjectName(QStringLiteral("splitter_4"));
        splitter_4->setLayoutDirection(Qt::RightToLeft);
        splitter_4->setOrientation(Qt::Horizontal);
        btnTest = new QPushButton(splitter_4);
        btnTest->setObjectName(QStringLiteral("btnTest"));
        btnTest->setMinimumSize(QSize(0, 36));
        btnTest->setMaximumSize(QSize(16777215, 36));
        splitter_4->addWidget(btnTest);
        btnPause = new QPushButton(splitter_4);
        btnPause->setObjectName(QStringLiteral("btnPause"));
        btnPause->setMinimumSize(QSize(0, 26));
        splitter_4->addWidget(btnPause);
        splitter_5->addWidget(splitter_4);
        splitter_3->addWidget(splitter_5);
        listNG = new QListWidget(splitter_3);
        new QListWidgetItem(listNG);
        new QListWidgetItem(listNG);
        listNG->setObjectName(QStringLiteral("listNG"));
        listNG->setMaximumSize(QSize(16777215, 200));
        splitter_3->addWidget(listNG);

        gridLayout->addWidget(splitter_3, 0, 0, 3, 1);

        grpImageSrc = new QGraphicsView(centralWidget);
        grpImageSrc->setObjectName(QStringLiteral("grpImageSrc"));
        grpImageSrc->setSizeIncrement(QSize(4, 3));
        grpImageSrc->setBaseSize(QSize(320, 240));

        gridLayout->addWidget(grpImageSrc, 0, 1, 1, 1);

        textLog = new QTextBrowser(centralWidget);
        textLog->setObjectName(QStringLiteral("textLog"));
        textLog->setMinimumSize(QSize(260, 0));

        gridLayout->addWidget(textLog, 0, 2, 3, 1);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        cboSrcInfo = new QComboBox(splitter);
        cboSrcInfo->setObjectName(QStringLiteral("cboSrcInfo"));
        splitter->addWidget(cboSrcInfo);
        cboDstInfo = new QComboBox(splitter);
        cboDstInfo->setObjectName(QStringLiteral("cboDstInfo"));
        splitter->addWidget(cboDstInfo);

        gridLayout->addWidget(splitter, 1, 1, 1, 1);

        grpImageDst = new QGraphicsView(centralWidget);
        grpImageDst->setObjectName(QStringLiteral("grpImageDst"));

        gridLayout->addWidget(grpImageDst, 2, 1, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(2, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 4);
        gridLayout->setColumnStretch(2, 1);
        TestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1270, 23));
        TestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TestClass->setStatusBar(statusBar);

        retranslateUi(TestClass);

        listNG->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(TestClass);
    } // setupUi

    void retranslateUi(QMainWindow *TestClass)
    {
        TestClass->setWindowTitle(QApplication::translate("TestClass", "Test", Q_NULLPTR));
        textStat->setHtml(QApplication::translate("TestClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\346\226\260\345\256\213\344\275\223'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p></body></html>", Q_NULLPTR));
        btnTest->setText(QApplication::translate("TestClass", "\346\265\213\350\257\225", Q_NULLPTR));
        btnPause->setText(QApplication::translate("TestClass", "\346\232\202\345\201\234", Q_NULLPTR));

        const bool __sortingEnabled = listNG->isSortingEnabled();
        listNG->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listNG->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("TestClass", "NG\351\241\271\345\210\227\350\241\250", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem1 = listNG->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("TestClass", "\345\207\240\344\275\225\345\267\245\345\205\267/\350\256\241\347\256\227\345\210\232\346\200\247\347\237\251\351\230\265/testGetRigidVector", Q_NULLPTR));
        listNG->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class TestClass: public Ui_TestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
