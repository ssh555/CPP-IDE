/****************************************************************************
** Meta object code from reading C++ file 'editor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "editor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Editor_t {
    QByteArrayData data[24];
    char stringdata0[370];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Editor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Editor_t qt_meta_stringdata_Editor = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Editor"
QT_MOC_LITERAL(1, 7, 22), // "SIGNAL_ChangeCodeStyle"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 17), // "SIGNAL_ChangeFont"
QT_MOC_LITERAL(4, 49, 4), // "flag"
QT_MOC_LITERAL(5, 54, 17), // "SLOT_FindKeywords"
QT_MOC_LITERAL(6, 72, 7), // "keyword"
QT_MOC_LITERAL(7, 80, 14), // "SLOT_FindWhole"
QT_MOC_LITERAL(8, 95, 17), // "SLOT_FindPrivious"
QT_MOC_LITERAL(9, 113, 20), // "SLOT_ReplaceKeywords"
QT_MOC_LITERAL(10, 134, 11), // "replaceword"
QT_MOC_LITERAL(11, 146, 17), // "SLOT_ReplaceWhole"
QT_MOC_LITERAL(12, 164, 20), // "SLOT_ReplacePrivious"
QT_MOC_LITERAL(13, 185, 14), // "SLOT_SearchEnd"
QT_MOC_LITERAL(14, 200, 13), // "FoldUnfoldAll"
QT_MOC_LITERAL(15, 214, 7), // "folding"
QT_MOC_LITERAL(16, 222, 18), // "SLOT_ChangeLineNum"
QT_MOC_LITERAL(17, 241, 3), // "num"
QT_MOC_LITERAL(18, 245, 16), // "insertCompletion"
QT_MOC_LITERAL(19, 262, 10), // "completion"
QT_MOC_LITERAL(20, 273, 30), // "SLOT_UpdateLineNumberAreaWidth"
QT_MOC_LITERAL(21, 304, 13), // "newBlockCount"
QT_MOC_LITERAL(22, 318, 25), // "SLOT_HighlightCurrentLine"
QT_MOC_LITERAL(23, 344, 25) // "SLOT_UpdateLineNumberArea"

    },
    "Editor\0SIGNAL_ChangeCodeStyle\0\0"
    "SIGNAL_ChangeFont\0flag\0SLOT_FindKeywords\0"
    "keyword\0SLOT_FindWhole\0SLOT_FindPrivious\0"
    "SLOT_ReplaceKeywords\0replaceword\0"
    "SLOT_ReplaceWhole\0SLOT_ReplacePrivious\0"
    "SLOT_SearchEnd\0FoldUnfoldAll\0folding\0"
    "SLOT_ChangeLineNum\0num\0insertCompletion\0"
    "completion\0SLOT_UpdateLineNumberAreaWidth\0"
    "newBlockCount\0SLOT_HighlightCurrentLine\0"
    "SLOT_UpdateLineNumberArea"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Editor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    1,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   93,    2, 0x0a /* Public */,
       7,    1,   96,    2, 0x0a /* Public */,
       8,    1,   99,    2, 0x0a /* Public */,
       9,    2,  102,    2, 0x0a /* Public */,
      11,    2,  107,    2, 0x0a /* Public */,
      12,    2,  112,    2, 0x0a /* Public */,
      13,    0,  117,    2, 0x0a /* Public */,
      14,    1,  118,    2, 0x0a /* Public */,
      16,    1,  121,    2, 0x0a /* Public */,
      18,    1,  124,    2, 0x08 /* Private */,
      20,    1,  127,    2, 0x08 /* Private */,
      22,    0,  130,    2, 0x08 /* Private */,
      23,    2,  131,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString,    6,
    QMetaType::Bool, QMetaType::QString,    6,
    QMetaType::Bool, QMetaType::QString,    6,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,    6,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,   10,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,    6,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRect, QMetaType::Int,    2,    2,

       0        // eod
};

void Editor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Editor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIGNAL_ChangeCodeStyle(); break;
        case 1: _t->SIGNAL_ChangeFont((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: { bool _r = _t->SLOT_FindKeywords((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->SLOT_FindWhole((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->SLOT_FindPrivious((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->SLOT_ReplaceKeywords((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->SLOT_ReplaceWhole((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { bool _r = _t->SLOT_ReplacePrivious((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->SLOT_SearchEnd(); break;
        case 9: _t->FoldUnfoldAll((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->SLOT_ChangeLineNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->insertCompletion((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->SLOT_UpdateLineNumberAreaWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->SLOT_HighlightCurrentLine(); break;
        case 14: _t->SLOT_UpdateLineNumberArea((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Editor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Editor::SIGNAL_ChangeCodeStyle)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Editor::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Editor::SIGNAL_ChangeFont)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Editor::staticMetaObject = { {
    QMetaObject::SuperData::link<QPlainTextEdit::staticMetaObject>(),
    qt_meta_stringdata_Editor.data,
    qt_meta_data_Editor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Editor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Editor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Editor.stringdata0))
        return static_cast<void*>(this);
    return QPlainTextEdit::qt_metacast(_clname);
}

int Editor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Editor::SIGNAL_ChangeCodeStyle()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Editor::SIGNAL_ChangeFont(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
