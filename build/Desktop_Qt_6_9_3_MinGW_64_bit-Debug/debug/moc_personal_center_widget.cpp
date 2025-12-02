/****************************************************************************
** Meta object code from reading C++ file 'personal_center_widget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../personal_center_widget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'personal_center_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN20PersonalCenterWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto PersonalCenterWidget::qt_create_metaobjectdata<qt_meta_tag_ZN20PersonalCenterWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PersonalCenterWidget",
        "logoutSignal",
        "",
        "backToFunctionSignal",
        "onLogoutClicked",
        "onBackClicked",
        "onSaveClicked",
        "onUpdateResult",
        "success",
        "onAvatarClicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'logoutSignal'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'backToFunctionSignal'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onLogoutClicked'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBackClicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSaveClicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onUpdateResult'
        QtMocHelpers::SlotData<void(bool)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 8 },
        }}),
        // Slot 'onAvatarClicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PersonalCenterWidget, qt_meta_tag_ZN20PersonalCenterWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PersonalCenterWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20PersonalCenterWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20PersonalCenterWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN20PersonalCenterWidgetE_t>.metaTypes,
    nullptr
} };

void PersonalCenterWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PersonalCenterWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->logoutSignal(); break;
        case 1: _t->backToFunctionSignal(); break;
        case 2: _t->onLogoutClicked(); break;
        case 3: _t->onBackClicked(); break;
        case 4: _t->onSaveClicked(); break;
        case 5: _t->onUpdateResult((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->onAvatarClicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (PersonalCenterWidget::*)()>(_a, &PersonalCenterWidget::logoutSignal, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (PersonalCenterWidget::*)()>(_a, &PersonalCenterWidget::backToFunctionSignal, 1))
            return;
    }
}

const QMetaObject *PersonalCenterWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PersonalCenterWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20PersonalCenterWidgetE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PersonalCenterWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void PersonalCenterWidget::logoutSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PersonalCenterWidget::backToFunctionSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
