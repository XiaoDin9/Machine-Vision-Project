/****************************************************************************
** Meta object code from reading C++ file 'color_transorm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../color_transorm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'color_transorm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Color_Transorm_t {
    QByteArrayData data[12];
    char stringdata0[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Color_Transorm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Color_Transorm_t qt_meta_stringdata_Color_Transorm = {
    {
QT_MOC_LITERAL(0, 0, 14), // "Color_Transorm"
QT_MOC_LITERAL(1, 15, 21), // "On_comboBox_activated"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 23), // "On_comboBox_4_activated"
QT_MOC_LITERAL(4, 62, 23), // "On_comboBox_5_activated"
QT_MOC_LITERAL(5, 86, 14), // "on_run_clicked"
QT_MOC_LITERAL(6, 101, 17), // "on_cancel_clicked"
QT_MOC_LITERAL(7, 119, 15), // "on_sure_clicked"
QT_MOC_LITERAL(8, 135, 22), // "on_radioButton_clicked"
QT_MOC_LITERAL(9, 158, 23), // "on_radioButton2_clicked"
QT_MOC_LITERAL(10, 182, 23), // "on_radioButton3_clicked"
QT_MOC_LITERAL(11, 206, 23) // "on_radioButton4_clicked"

    },
    "Color_Transorm\0On_comboBox_activated\0"
    "\0On_comboBox_4_activated\0"
    "On_comboBox_5_activated\0on_run_clicked\0"
    "on_cancel_clicked\0on_sure_clicked\0"
    "on_radioButton_clicked\0on_radioButton2_clicked\0"
    "on_radioButton3_clicked\0on_radioButton4_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Color_Transorm[] = {

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
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Color_Transorm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Color_Transorm *_t = static_cast<Color_Transorm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->On_comboBox_activated(); break;
        case 1: _t->On_comboBox_4_activated(); break;
        case 2: _t->On_comboBox_5_activated(); break;
        case 3: _t->on_run_clicked(); break;
        case 4: _t->on_cancel_clicked(); break;
        case 5: _t->on_sure_clicked(); break;
        case 6: _t->on_radioButton_clicked(); break;
        case 7: _t->on_radioButton2_clicked(); break;
        case 8: _t->on_radioButton3_clicked(); break;
        case 9: _t->on_radioButton4_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Color_Transorm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Color_Transorm.data,
      qt_meta_data_Color_Transorm,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Color_Transorm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Color_Transorm::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Color_Transorm.stringdata0))
        return static_cast<void*>(const_cast< Color_Transorm*>(this));
    return QWidget::qt_metacast(_clname);
}

int Color_Transorm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
