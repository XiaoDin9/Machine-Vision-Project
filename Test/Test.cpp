#pragma execution_character_set("utf-8")
#include <QTreeWidgetItem>
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include "test_frame.h"
#include "Test.h"


TestThread::TestThread(QObject * _param) : QThread(_param)
{
    param = _param;
}

TestThread::~TestThread()
{
}

void TestThread::run()
{
    while (1)
    {
        QThread::msleep(1);
        if (true == ((Test *)param)->isExit)
        {
            break;
        }
        if (false == ((Test *)param)->isRun)
        {
            continue;
        }
        QVector<QPoint> &testId = ((Test *)param)->testId;
        for (int i = 0; i < testId.size(); i++)
        {
            int set = testId[i].x();
            int func = testId[i].y();
            int testRst = ((Test *)param)->testFunc(set, func);     // QObject 的指针变量param 转换为 Test类的指针变量，并执行Test 类中的 testFunc 函数
            emit functionTested(testId[i].x(), testId[i].y(), testRst);
        }
        emit allTested();
        ((Test *)param)->isRun = false;
    }
}

Test::Test(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    isExit = false;
    isRun = false;
    testTotal = 0;
    tested = 0;
    testNG = 0;
    state = "空闲";

    //初始化
    init();

    thread = new TestThread(this);
    connect(thread, SIGNAL(functionTested(int, int, int)), this, SLOT(updateTestedInfo(int, int, int)));
    connect(thread, SIGNAL(allTested()), this, SLOT(testFinished()));
    thread->start();
}

void Test::init()
{
    int rst = test_frm_init();
    if (TEST_DATA_PATH_ERR >= rst)
    {
        QMessageBox::warning(this, tr("警告"), QString("测试图像[%1]打开失败！").
            arg(g_testImgInfo[TEST_DATA_PATH_ERR - rst].path), QMessageBox::Ok);
        test_frm_exit();
        exit(-1);
        return;
    }

    // 添加最左边的 QTW 中的各个项目条
    QTreeWidgetItem *all = new QTreeWidgetItem(ui.treeTest);      // 1级 目录
    all->setData(0, Qt::UserRole, -1);
    all->setData(0, Qt::UserRole + 1, -1);
    all->setText(0, tr("全部"));
    all->setExpanded(true);

    for (int i = 0; i < TEST_SET_MAX; i++)
    {
        TestSet * set = &g_testAll[i];
        QTreeWidgetItem *child = new QTreeWidgetItem(all);
        child->setData(0, Qt::UserRole, i);
        child->setData(0, Qt::UserRole + 1, -1);
        child->setText(0, QString::fromLocal8Bit(set->disp));
        for (int k = 0; k < set->size; k++)
        {
            TestFunction * fun = set->funcList + k;
            QTreeWidgetItem * leaf = new QTreeWidgetItem(child);
            leaf->setData(0, Qt::UserRole, i);
            leaf->setData(0, Qt::UserRole + 1, k);
            leaf->setText(0, QString::fromLocal8Bit(fun->disp));
            testTotal++;
        }
    }

    ui.textLog->document()->setMaximumBlockCount(1000);
    updateSrcCboItem();    // 往QComboBox 中插入数据，并显示图像
    clearData();           // 清除数据
    updateStat();          // 更新状态
}

void Test::clearData()
{
    ui.listNG->clear();
    ui.listNG->insertItem(0, "失败列表");

    testId.clear();
    tested = 0;
    testNG = 0;
    test_frm_start();
}

//下拉列表数据格式
//输入：1.[参数/缓存]2592x1944 Gray D://a.jpg/相机0 附加
QString Test::getSrcCboString(int id)
{
    if (!g_testImgInfo[id].isUse)
    {
        return QString();
    }

    return QString("输入：%1.[%2]%3x%4 %5 %6 %7").arg(id)
        .arg(g_testImgInfo[id].isParam ? "参数" : "缓存")
        .arg(g_testImgInfo[id].width).arg(g_testImgInfo[id].height)
        .arg(1 == g_testImgInfo[id].channels ? "Gray" : "RGB")
        .arg(g_testImgInfo[id].path).arg(g_testImgInfo[id].attach);
}

//输出：1.[参数/中间]2592x1944 Mono8  附加
QString Test::getDstCboString(int _id)
{
    int id = _id + TEST_IMAGE_COUNT;
    if (!test_frm_chkDstImgInfo(id))
    {
        return QString();
    }
    return QString("输出：%1.[%2]%3x%4 %5 %6").arg(_id)
        .arg(g_testImgInfo[id].isParam ? "参数" : "中间结果")
        .arg(g_testImgInfo[id].width).arg(g_testImgInfo[id].height)
        .arg(1 == g_testImgInfo[id].channels ? "Gray" : "RGB")
        .arg(g_testImgInfo[id].attach);
}

void Test::closeEvent(QCloseEvent *ev)
{
    isExit = true;
    QThread::msleep(100);
    delete thread;
    test_frm_exit();
    ev->accept();
}

QString Test::getColorString(QString str, QString color)
{
    stringToHtml(str);
    return QString(tr("<span style=\" color:#%1;\">%2</span>")).arg(color).arg(str);
}

void Test::stringToHtml(QString &string)
{
    string.replace("&", "&amp;");
    string.replace(">", "&gt;");
    string.replace("<", "&lt;");
    string.replace("\"", "&quot;");
    string.replace("\'", "&#39;");
    string.replace(" ", "&ensp;");
    string.replace("\n", "<br>");
    string.replace("\r", "<br>");
}

void Test::updateSrcCboItem()
{
    ui.cboSrcInfo->clear();
    int curId = -1;
    for (int i = 0; i < TEST_IMAGE_COUNT; i++)
    {
        QString item = getSrcCboString(i);
        if (item.isEmpty())
        {
            break;
        }
        ui.cboSrcInfo->addItem(item);
        if (g_testImgInfo[i].isParam && -1 == curId)
        {
            curId = i;
        }
    }

    if (-1 == curId) curId = 0;
    ui.cboSrcInfo->setCurrentIndex(curId);
    showImage(true, curId);
}

void Test::updateDstCboItem()
{
    ui.cboDstInfo->clear();
    for (int i = 0; i < TEST_IMAGE_COUNT; i++)
    {
        QString item = getDstCboString(i);
        if (!item.isEmpty())
        {
            ui.cboDstInfo->addItem(item);
        }
    }
    ui.cboDstInfo->setCurrentIndex(0);
    showImage(false, (ui.cboDstInfo->count() > 0)-1);
}

void Test::updateStat()
{
    QString stat = QString(tr("总计：%1 已选定：%2")).arg(testTotal, -4).arg(testId.size(), -4);
    stringToHtml(stat);
    stat += "<br>" + getColorString(QString("%1状态 已测试：%2").arg(state).arg(tested, -4), "0000FF");
    double rate = 0 == tested ? 0.0 : testNG*100.0 / tested;
    stat += "<br>" + getColorString(QString("失败：%1 比例：%2%").arg(testNG, -4).arg(rate, -6, 'f', 2), "FF0000");
    ui.textStat->clear();
    ui.textStat->insertHtml(stat);
}

void Test::showImage(bool isSrc, int id)
{
    static QImage::Format cft[] = { QImage::Format_Grayscale8 , QImage::Format_RGB16,
        QImage::Format_RGB888 , QImage::Format_RGBA8888 };
    QGraphicsScene *scene = isSrc ? ui.grpImageSrc->scene() : ui.grpImageDst->scene();
    if (NULL != scene)
    {
        scene->clear();
    }
  
    if (-1 == id)
    {
        return;
    }
    if (!isSrc)
    {
        id += DST_IMAGE_OFFSET;
    }

    ZvImage img = g_testImgInfo[id].img;
    if (ZV_PIXEL_8U != zv_imgDataType(img))
    {
        return;
    }
    int channel = zv_imgChannels(img);
    int width = zv_imgWidth(img);
    int height = zv_imgHeight(img);
    width = (width + 3) >> 2 << 2;             //数据四字节对齐，QImage显示要求
    height = (height + 3) >> 2 << 2;
    uchar* qImageBuffer = new uchar[height*width*channel];
    zv_imgGetData(img, qImageBuffer, height*width*channel, true);
    QImage qimage(qImageBuffer, width, height, cft[channel-1]);

    if (NULL == scene)
        scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(qimage));
    if (isSrc)
    {
        ui.grpImageSrc->setScene(scene);
        ui.grpImageSrc->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui.grpImageSrc->show();
    }
    else
    {
        ui.grpImageDst->setScene(scene);
        ui.grpImageDst->show();
    }
    delete[]qImageBuffer;
}

void Test::addLog(QString log)
{
    ui.textLog->append(log);
    ui.textLog->moveCursor(QTextCursor::End);
}

int Test::testFunc(int set, int func)
{
    int testRst = -1;
    TestLog log = { 0 };
    test_frm_clearCurInfo();
   
    if (set >= 0 && set < TEST_SET_MAX && func >= 0 && func < g_testAll[set].size)
    {
        testRst = test_frm_funcTest(&log, set, func);
    }
  
    int sleepCount = 200; //testLogStr多线程同步 - 界面显示部分不能放在线程中处理。
    while ("" != testLogStr && sleepCount-- > 0)
    {
        QThread::msleep(5);
    }
    bool isStatNg = 0 != testRst;
    if (-1 != testRst)
    {
        testLogStr = QString("测试：%1 - %2\n").arg(QString::fromLocal8Bit(g_testAll[set].disp))
            .arg(QString::fromLocal8Bit(g_testAll[set].funcList[func].disp));
        testLogStr += QString(QString::fromLocal8Bit((char *)log.buf));
        if (TEST_TEST == set && QString::fromLocal8Bit(g_testAll[set].funcList[func].name).contains("testFail"))
        {
            isStatNg = false;
        }
    }
    else
    {
        testLogStr = QString("索引错误：(%1, %2) 跳过\n测试结果：失败\n\n").arg(set).arg(func);
    }

    tested++;
    testNG += isStatNg;
    return testRst;
}

void Test::updateTestedInfo(int set, int func, int rst)
{
    addLog(testLogStr);
    testLogStr = "";
    updateStat();
    //updateSrcCboItem();  //异步更新，需要加锁
    //updateDstCboItem();

    if (0 == rst)
    {
        return;
    }

    if (1000 < ui.listNG->count())
    {
        return;
    }

    //添加到NG列表
    QListWidgetItem * ngItem = new QListWidgetItem(ui.listNG);
    ngItem->setData(Qt::UserRole, -1 == rst ? -1 : rst-1);
    ngItem->setData(Qt::UserRole + 1, QPoint(set, func));
    QString setStr;
    if (-1 == rst)
    {
        setStr = QString("%1/%2/%3").arg(set).arg(func).arg(tr("索引错误"));
    }
    else
    {
        setStr = QString("%1/%2/%3").arg(QString::fromLocal8Bit(g_testAll[set].disp))
            .arg(QString::fromLocal8Bit(g_testAll[set].funcList[func].disp))
            .arg(QString::fromLocal8Bit(g_testAll[set].funcList[func].name));
    }
    ngItem->setText(setStr);
}

void Test::testFinished()
{
    state = "空闲";
    updateStat();
    updateSrcCboItem();
    updateDstCboItem();
}

void Test::showNgInfo(int id) //NG信息设置，显示
{
    TestInfo * ng = test_frm_getNgInfo(id);
    if (NULL == ng)
    {
        return;
    }

    addLog(QString("\n查看缓存：%1\n").arg(id));
    addLog(QString::fromLocal8Bit((char *)ng->tLog.buf));

    for (int i = 0; i < TEST_IMAGE_COUNT; i++)
    {
        g_testImgInfo[i].isParam = ng->isSrcImgUse[i];
        g_testImgInfo[DST_IMAGE_OFFSET + i].isParam = ng->isDstImgOut[i];
        if (ng->imgOut[i])
        {
            g_testImgInfo[DST_IMAGE_OFFSET + i].isUse = true;
            zv_imgCopy(ng->imgOut[i], g_testImgInfo[DST_IMAGE_OFFSET + i].img);
        }
    }

    updateSrcCboItem();
    updateDstCboItem();
}

void Test::on_btnTest_clicked()
{
    //避免连续单击
    //启动后再次单击，则停止测试
    //获取选中项目，启动线程
    clearData();

    QList<QTreeWidgetItem*> item = ui.treeTest->selectedItems();    // 获取测试项选中的选项的列表
    for (int i = 0; i < item.size(); i++)
    {
        QPoint id(item[i]->data(0, Qt::UserRole).toInt(), item[i]->data(0, Qt::UserRole+1).toInt());
        if (-1 != id.x() && -1 != id.y())
        {
            testId.append(id);
        }
    }

    state = "测试";
    updateStat();
    isRun = true;
}

void Test::on_btnPause_clicked()
{
    //TODO
}

void Test::on_cboSrcInfo_currentIndexChanged(int index)
{
    showImage(true, index);
}

void Test::on_cboDstInfo_currentIndexChanged(int index)
{
    showImage(false, index);
}

void Test::on_listNG_itemDoubleClicked(QListWidgetItem *item)
{
    if (0 == ui.listNG->row(item))
    {
        return;
    }

    test_frm_clearCurInfo();
    int id = item->data(Qt::UserRole).toInt();
    if (-1 == id)
    {
        return;
    }

    showNgInfo(id);
}

void Test::on_treeTest_itemClicked(QTreeWidgetItem *item, int column)
{
    bool selected = item->isSelected();
    for (int i = 0; i < item->childCount(); i++)
    {
        item->child(i)->setSelected(selected);
        for (int k = 0; k < item->child(i)->childCount(); k++)
        {
            item->child(i)->child(k)->setSelected(selected);
        }
    }

    if (!selected)
    {
        if (item->parent())
        {
            item->parent()->setSelected(false);
            if (item->parent()->parent())
                item->parent()->parent()->setSelected(false);
        }
        item->setSelected(false);
    }
}

void Test::on_treeTest_itemSelectionChanged()
{
    return;
    QList<QTreeWidgetItem*> item = ui.treeTest->selectedItems();
    for (int i = 0; i < item.size(); i++)
    {
        for (int k = 0; k < item[i]->childCount(); k++)
        {
            item[i]->child(k)->setSelected(true);
            for (int j = 0; j < item[i]->child(k)->childCount(); j++)
            {
                item[i]->child(k)->child(j)->setSelected(true);
            }
        }
    }
}

void Test::on_treeTest_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    item->treeWidget()->clearSelection();
    item->setSelected(true);
}

//std::string 