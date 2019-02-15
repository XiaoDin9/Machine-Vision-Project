/****************************************************************************
** Meta object code from reading C++ file 'Test.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Test.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Test.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TestThread_t {
    QByteArrayData data[7];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TestThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TestThread_t qt_meta_stringdata_TestThread = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TestThread"
QT_MOC_LITERAL(1, 11, 14), // "functionTested"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 3), // "set"
QT_MOC_LITERAL(4, 31, 4), // "func"
QT_MOC_LITERAL(5, 36, 3), // "rst"
QT_MOC_LITERAL(6, 40, 9) // "allTested"

    },
    "TestThread\0functionTested\0\0set\0func\0"
    "rst\0allTested"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TestThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,
       6,    0,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void,

       0        // eod
};

void TestThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TestThread *_t = static_cast<TestThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->functionTested((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->allTested(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TestThread::*_t)(int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TestThread::functionTested)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TestThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TestThread::allTested)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject TestThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_TestThread.data,
      qt_meta_data_TestThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TestThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TestThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TestThread.stringdata0))
        return static_cast<void*>(const_cast< TestThread*>(this));
    return QThread::qt_metacast(_clname);
}

int TestThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void TestThread::functionTested(int _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TestThread::allTested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
struct qt_meta_stringdata_Test_t {
    QByteArrayData data[20];
    char stringdata0[323];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Test_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Test_t qt_meta_stringdata_Test = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Test"
QT_MOC_LITERAL(1, 5, 16), // "updateTestedInfo"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 3), // "set"
QT_MOC_LITERAL(4, 27, 4), // "func"
QT_MOC_LITERAL(5, 32, 3), // "rst"
QT_MOC_LITERAL(6, 36, 12), // "testFinished"
QT_MOC_LITERAL(7, 49, 18), // "on_btnTest_clicked"
QT_MOC_LITERAL(8, 68, 19), // "on_btnPause_clicked"
QT_MOC_LITERAL(9, 88, 33), // "on_cboSrcInfo_currentIndexCha..."
QT_MOC_LITERAL(10, 122, 5), // "index"
QT_MOC_LITERAL(11, 128, 33), // "on_cboDstInfo_currentIndexCha..."
QT_MOC_LITERAL(12, 162, 27), // "on_listNG_itemDoubleClicked"
QT_MOC_LITERAL(13, 190, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(14, 207, 4), // "item"
QT_MOC_LITERAL(15, 212, 23), // "on_treeTest_itemClicked"
QT_MOC_LITERAL(16, 236, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(17, 253, 6), // "column"
QT_MOC_LITERAL(18, 260, 32), // "on_treeTest_itemSelectionChanged"
QT_MOC_LITERAL(19, 293, 29) // "on_treeTest_itemDoubleClicked"

    },
    "Test\0updateTestedInfo\0\0set\0func\0rst\0"
    "testFinished\0on_btnTest_clicked\0"
    "on_btnPause_clicked\0"
    "on_cboSrcInfo_currentIndexChanged\0"
    "index\0on_cboDstInfo_currentIndexChanged\0"
    "on_listNG_itemDoubleClicked\0"
    "QListWidgetItem*\0item\0on_treeTest_itemClicked\0"
    "QTreeWidgetItem*\0column\0"
    "on_treeTest_itemSelectionChanged\0"
    "on_treeTest_itemDoubleClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Test[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   64,    2, 0x08 /* Private */,
       6,    0,   71,    2, 0x08 /* Private */,
       7,    0,   72,    2, 0x08 /* Private */,
       8,    0,   73,    2, 0x08 /* Private */,
       9,    1,   74,    2, 0x08 /* Private */,
      11,    1,   77,    2, 0x08 /* Private */,
      12,    1,   80,    2, 0x08 /* Private */,
      15,    2,   83,    2, 0x08 /* Private */,
      18,    0,   88,    2, 0x08 /* Private */,
      19,    2,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int,   14,   17,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int,   14,   17,

       0        // eod
};

void Test::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Test *_t = static_cast<Test *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateTestedInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->testFinished(); break;
        case 2: _t->on_btnTest_clicked(); break;
        case 3: _t->on_btnPause_clicked(); break;
        case 4: _t->on_cboSrcInfo_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_cboDstInfo_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_listNG_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->on_treeTest_itemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->on_treeTest_itemSelectionChanged(); break;
        case 9: _t->on_treeTest_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject Test::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Test.data,
      qt_meta_data_Test,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Test::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Test::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Test.stringdata0))
        return static_cast<void*>(const_cast< Test*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Test::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
