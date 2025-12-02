/****************************************************************************
** Meta object code from reading C++ file 'order_widget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../order_widget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'order_widget.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11OrderWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto OrderWidget::qt_create_metaobjectdata<qt_meta_tag_ZN11OrderWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "OrderWidget",
        "backToFunctionSignal",
        "",
        "onBackClicked",
        "onRefreshClicked",
        "onCancelClicked",
        "onChangeClicked",
        "onOrderListResult",
        "QList<OrderInfo>",
        "orders",
        "onCancelOrderResult",
        "success",
        "errMsg",
        "onChangeOrderResult",
        "newOrderId",
        "showChangeFlightDialog",
        "orderId",
        "onChangeRequested",
        "FlightInfo",
        "newFlight",
        "newSeatClass"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'backToFunctionSignal'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onBackClicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onRefreshClicked'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCancelClicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onChangeClicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onOrderListResult'
        QtMocHelpers::SlotData<void(const QList<OrderInfo> &)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Slot 'onCancelOrderResult'
        QtMocHelpers::SlotData<void(bool, QString)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 11 }, { QMetaType::QString, 12 },
        }}),
        // Slot 'onChangeOrderResult'
        QtMocHelpers::SlotData<void(bool, QString, QString)>(13, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 11 }, { QMetaType::QString, 12 }, { QMetaType::QString, 14 },
        }}),
        // Slot 'showChangeFlightDialog'
        QtMocHelpers::SlotData<void(const QString &)>(15, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 16 },
        }}),
        // Slot 'onChangeRequested'
        QtMocHelpers::SlotData<void(const QString &, const FlightInfo &, const QString &)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 16 }, { 0x80000000 | 18, 19 }, { QMetaType::QString, 20 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<OrderWidget, qt_meta_tag_ZN11OrderWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject OrderWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11OrderWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11OrderWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11OrderWidgetE_t>.metaTypes,
    nullptr
} };

void OrderWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<OrderWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->backToFunctionSignal(); break;
        case 1: _t->onBackClicked(); break;
        case 2: _t->onRefreshClicked(); break;
        case 3: _t->onCancelClicked(); break;
        case 4: _t->onChangeClicked(); break;
        case 5: _t->onOrderListResult((*reinterpret_cast< std::add_pointer_t<QList<OrderInfo>>>(_a[1]))); break;
        case 6: _t->onCancelOrderResult((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 7: _t->onChangeOrderResult((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 8: _t->showChangeFlightDialog((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->onChangeRequested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<FlightInfo>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (OrderWidget::*)()>(_a, &OrderWidget::backToFunctionSignal, 0))
            return;
    }
}

const QMetaObject *OrderWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OrderWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11OrderWidgetE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int OrderWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void OrderWidget::backToFunctionSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
