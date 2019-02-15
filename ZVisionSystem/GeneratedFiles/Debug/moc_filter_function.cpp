/****************************************************************************
** Meta object code from reading C++ file 'filter_function.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../filter_function.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filter_function.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Filter_Function_t {
    QByteArrayData data[13];
    char stringdata0[241];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Filter_Function_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Filter_Function_t qt_meta_stringdata_Filter_Function = {
    {
QT_MOC_LITERAL(0, 0, 15), // "Filter_Function"
QT_MOC_LITERAL(1, 16, 26), // "activate_comboBox_triggred"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 28), // "activate_comboBox_2_triggred"
QT_MOC_LITERAL(4, 73, 14), // "on_run_clicked"
QT_MOC_LITERAL(5, 88, 15), // "on_sure_clicked"
QT_MOC_LITERAL(6, 104, 17), // "on_cancel_clicked"
QT_MOC_LITERAL(7, 122, 20), // "set_medianblur_value"
QT_MOC_LITERAL(8, 143, 18), // "set_meanblur_value"
QT_MOC_LITERAL(9, 162, 22), // "set_gaussianblur_value"
QT_MOC_LITERAL(10, 185, 19), // "set_boxfilter_value"
QT_MOC_LITERAL(11, 205, 19), // "set_bilateralfilter"
QT_MOC_LITERAL(12, 225, 15) // "on_statechanged"

    },
    "Filter_Function\0activate_comboBox_triggred\0"
    "\0activate_comboBox_2_triggred\0"
    "on_run_clicked\0on_sure_clicked\0"
    "on_cancel_clicked\0set_medianblur_value\0"
    "set_meanblur_value\0set_gaussianblur_value\0"
    "set_boxfilter_value\0set_bilateralfilter\0"
    "on_statechanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Filter_Function[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    1,   74,    2, 0x08 /* Private */,
       8,    1,   77,    2, 0x08 /* Private */,
       9,    1,   80,    2, 0x08 /* Private */,
      10,    1,   83,    2, 0x08 /* Private */,
      11,    1,   86,    2, 0x08 /* Private */,
      12,    1,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void Filter_Function::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Filter_Function *_t = static_cast<Filter_Function *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->activate_comboBox_triggred(); break;
        case 1: _t->activate_comboBox_2_triggred(); break;
        case 2: _t->on_run_clicked(); break;
        case 3: _t->on_sure_clicked(); break;
        case 4: _t->on_cancel_clicked(); break;
        case 5: _t->set_medianblur_value((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->set_meanblur_value((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->set_gaussianblur_value((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->set_boxfilter_value((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->set_bilateralfilter((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_statechanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Filter_Function::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Filter_Function.data,
      qt_meta_data_Filter_Function,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Filter_Function::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Filter_Function::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Filter_Function.stringdata0))
        return static_cast<void*>(const_cast< Filter_Function*>(this));
    return QWidget::qt_metacast(_clname);
}

int Filter_Function::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
