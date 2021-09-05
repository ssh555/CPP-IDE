/****************************************************************************
** Meta object code from reading C++ file 'searchwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../BITC/searchwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'searchwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SearchWindow_t {
    QByteArrayData data[18];
    char stringdata0[317];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SearchWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SearchWindow_t qt_meta_stringdata_SearchWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SearchWindow"
QT_MOC_LITERAL(1, 13, 15), // "SIGNAL_FindNext"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 8), // "findtext"
QT_MOC_LITERAL(4, 39, 19), // "SIGNAL_FindPrivious"
QT_MOC_LITERAL(5, 59, 16), // "SIGNAL_FindWhole"
QT_MOC_LITERAL(6, 76, 18), // "SIGNAL_ReplaceNext"
QT_MOC_LITERAL(7, 95, 11), // "replacetext"
QT_MOC_LITERAL(8, 107, 22), // "SIGNAL_ReplacePrivious"
QT_MOC_LITERAL(9, 130, 19), // "SIGNAL_ReplaceWhole"
QT_MOC_LITERAL(10, 150, 11), // "SIGNAL_Exit"
QT_MOC_LITERAL(11, 162, 22), // "on_btnFindNext_clicked"
QT_MOC_LITERAL(12, 185, 20), // "on_btnCancel_clicked"
QT_MOC_LITERAL(13, 206, 18), // "on_btnExit_clicked"
QT_MOC_LITERAL(14, 225, 23), // "on_btnFindWhole_clicked"
QT_MOC_LITERAL(15, 249, 26), // "on_btnFindPrivious_clicked"
QT_MOC_LITERAL(16, 276, 21), // "on_btnReplace_clicked"
QT_MOC_LITERAL(17, 298, 18) // "on_btnFind_clicked"

    },
    "SearchWindow\0SIGNAL_FindNext\0\0findtext\0"
    "SIGNAL_FindPrivious\0SIGNAL_FindWhole\0"
    "SIGNAL_ReplaceNext\0replacetext\0"
    "SIGNAL_ReplacePrivious\0SIGNAL_ReplaceWhole\0"
    "SIGNAL_Exit\0on_btnFindNext_clicked\0"
    "on_btnCancel_clicked\0on_btnExit_clicked\0"
    "on_btnFindWhole_clicked\0"
    "on_btnFindPrivious_clicked\0"
    "on_btnReplace_clicked\0on_btnFind_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SearchWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    1,   87,    2, 0x06 /* Public */,
       5,    1,   90,    2, 0x06 /* Public */,
       6,    2,   93,    2, 0x06 /* Public */,
       8,    2,   98,    2, 0x06 /* Public */,
       9,    2,  103,    2, 0x06 /* Public */,
      10,    0,  108,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,  109,    2, 0x08 /* Private */,
      12,    0,  110,    2, 0x08 /* Private */,
      13,    0,  111,    2, 0x08 /* Private */,
      14,    0,  112,    2, 0x08 /* Private */,
      15,    0,  113,    2, 0x08 /* Private */,
      16,    0,  114,    2, 0x08 /* Private */,
      17,    0,  115,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SearchWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SearchWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIGNAL_FindNext((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->SIGNAL_FindPrivious((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->SIGNAL_FindWhole((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->SIGNAL_ReplaceNext((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->SIGNAL_ReplacePrivious((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->SIGNAL_ReplaceWhole((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->SIGNAL_Exit(); break;
        case 7: _t->on_btnFindNext_clicked(); break;
        case 8: _t->on_btnCancel_clicked(); break;
        case 9: _t->on_btnExit_clicked(); break;
        case 10: _t->on_btnFindWhole_clicked(); break;
        case 11: _t->on_btnFindPrivious_clicked(); break;
        case 12: _t->on_btnReplace_clicked(); break;
        case 13: _t->on_btnFind_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SearchWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchWindow::SIGNAL_FindNext)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SearchWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchWindow::SIGNAL_FindPrivious)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SearchWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchWindow::SIGNAL_FindWhole)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SearchWindow::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchWindow::SIGNAL_ReplaceNext)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SearchWindow::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchWindow::SIGNAL_ReplacePrivious)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SearchWindow::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchWindow::SIGNAL_ReplaceWhole)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SearchWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchWindow::SIGNAL_Exit)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SearchWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SearchWindow.data,
    qt_meta_data_SearchWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SearchWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SearchWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SearchWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SearchWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void SearchWindow::SIGNAL_FindNext(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SearchWindow::SIGNAL_FindPrivious(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SearchWindow::SIGNAL_FindWhole(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SearchWindow::SIGNAL_ReplaceNext(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SearchWindow::SIGNAL_ReplacePrivious(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SearchWindow::SIGNAL_ReplaceWhole(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SearchWindow::SIGNAL_Exit()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
