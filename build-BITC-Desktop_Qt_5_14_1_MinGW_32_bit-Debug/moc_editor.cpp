/****************************************************************************
** Meta object code from reading C++ file 'editor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../BITC/editor.h"
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
    QByteArrayData data[20];
    char stringdata0[324];
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
QT_MOC_LITERAL(3, 31, 17), // "SLOT_FindKeywords"
QT_MOC_LITERAL(4, 49, 7), // "keyword"
QT_MOC_LITERAL(5, 57, 14), // "SLOT_FindWhole"
QT_MOC_LITERAL(6, 72, 17), // "SLOT_FindPrivious"
QT_MOC_LITERAL(7, 90, 20), // "SLOT_ReplaceKeywords"
QT_MOC_LITERAL(8, 111, 11), // "replaceword"
QT_MOC_LITERAL(9, 123, 17), // "SLOT_ReplaceWhole"
QT_MOC_LITERAL(10, 141, 20), // "SLOT_ReplacePrivious"
QT_MOC_LITERAL(11, 162, 14), // "SLOT_SearchEnd"
QT_MOC_LITERAL(12, 177, 13), // "FoldUnfoldAll"
QT_MOC_LITERAL(13, 191, 7), // "folding"
QT_MOC_LITERAL(14, 199, 16), // "insertCompletion"
QT_MOC_LITERAL(15, 216, 10), // "completion"
QT_MOC_LITERAL(16, 227, 30), // "SLOT_UpdateLineNumberAreaWidth"
QT_MOC_LITERAL(17, 258, 13), // "newBlockCount"
QT_MOC_LITERAL(18, 272, 25), // "SLOT_HighlightCurrentLine"
QT_MOC_LITERAL(19, 298, 25) // "SLOT_UpdateLineNumberArea"

    },
    "Editor\0SIGNAL_ChangeCodeStyle\0\0"
    "SLOT_FindKeywords\0keyword\0SLOT_FindWhole\0"
    "SLOT_FindPrivious\0SLOT_ReplaceKeywords\0"
    "replaceword\0SLOT_ReplaceWhole\0"
    "SLOT_ReplacePrivious\0SLOT_SearchEnd\0"
    "FoldUnfoldAll\0folding\0insertCompletion\0"
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
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   80,    2, 0x0a /* Public */,
       5,    1,   83,    2, 0x0a /* Public */,
       6,    1,   86,    2, 0x0a /* Public */,
       7,    2,   89,    2, 0x0a /* Public */,
       9,    2,   94,    2, 0x0a /* Public */,
      10,    2,   99,    2, 0x0a /* Public */,
      11,    0,  104,    2, 0x0a /* Public */,
      12,    1,  105,    2, 0x0a /* Public */,
      14,    1,  108,    2, 0x08 /* Private */,
      16,    1,  111,    2, 0x08 /* Private */,
      18,    0,  114,    2, 0x08 /* Private */,
      19,    2,  115,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Bool, QMetaType::QString,    4,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,    4,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    8,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,    4,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::Int,   17,
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
        case 1: { bool _r = _t->SLOT_FindKeywords((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->SLOT_FindWhole((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: { bool _r = _t->SLOT_FindPrivious((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->SLOT_ReplaceKeywords((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->SLOT_ReplaceWhole((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: { bool _r = _t->SLOT_ReplacePrivious((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->SLOT_SearchEnd(); break;
        case 8: _t->FoldUnfoldAll((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->insertCompletion((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->SLOT_UpdateLineNumberAreaWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->SLOT_HighlightCurrentLine(); break;
        case 12: _t->SLOT_UpdateLineNumberArea((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Editor::SIGNAL_ChangeCodeStyle()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
