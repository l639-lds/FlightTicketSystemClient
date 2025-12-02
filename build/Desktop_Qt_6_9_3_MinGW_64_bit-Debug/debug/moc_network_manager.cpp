/****************************************************************************
** Meta object code from reading C++ file 'network_manager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../network_manager.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'network_manager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14NetworkManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto NetworkManager::qt_create_metaobjectdata<qt_meta_tag_ZN14NetworkManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "NetworkManager",
        "loginResult",
        "",
        "success",
        "UserInfo",
        "userInfo",
        "registerResult",
        "errMsg",
        "updateUserInfoResult",
        "flightSearchResult",
        "QList<FlightInfo>",
        "flights",
        "bookResult",
        "orderId",
        "orderListResult",
        "QList<OrderInfo>",
        "orders",
        "cancelOrderResult",
        "changeOrderResult",
        "newOrderId",
        "sendRegisterRequest",
        "sendLoginRequest",
        "accountOrUsername",
        "password",
        "updateUserInfo",
        "account",
        "gender",
        "birthDate",
        "avatarPath",
        "signature",
        "loadAvatarPath",
        "loadSignature",
        "getUserOrders",
        "userId",
        "cancelOrder",
        "changeOrder",
        "FlightInfo",
        "newFlight",
        "newSeatClass",
        "addOrder",
        "OrderInfo",
        "order"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'loginResult'
        QtMocHelpers::SignalData<void(bool, UserInfo)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { 0x80000000 | 4, 5 },
        }}),
        // Signal 'registerResult'
        QtMocHelpers::SignalData<void(bool, QString)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 7 },
        }}),
        // Signal 'updateUserInfoResult'
        QtMocHelpers::SignalData<void(bool)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 },
        }}),
        // Signal 'flightSearchResult'
        QtMocHelpers::SignalData<void(const QList<FlightInfo> &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Signal 'bookResult'
        QtMocHelpers::SignalData<void(bool, const QString &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 13 },
        }}),
        // Signal 'orderListResult'
        QtMocHelpers::SignalData<void(const QList<OrderInfo> &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 15, 16 },
        }}),
        // Signal 'cancelOrderResult'
        QtMocHelpers::SignalData<void(bool, QString)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 7 },
        }}),
        // Signal 'changeOrderResult'
        QtMocHelpers::SignalData<void(bool, QString, QString)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 7 }, { QMetaType::QString, 19 },
        }}),
        // Slot 'sendRegisterRequest'
        QtMocHelpers::SlotData<void(UserInfo)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 5 },
        }}),
        // Slot 'sendLoginRequest'
        QtMocHelpers::SlotData<void(QString, QString)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 22 }, { QMetaType::QString, 23 },
        }}),
        // Slot 'updateUserInfo'
        QtMocHelpers::SlotData<void(QString, QString, QDate, QString, QString)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 25 }, { QMetaType::QString, 26 }, { QMetaType::QDate, 27 }, { QMetaType::QString, 28 },
            { QMetaType::QString, 29 },
        }}),
        // Slot 'updateUserInfo'
        QtMocHelpers::SlotData<void(QString, QString, QDate, QString)>(24, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 25 }, { QMetaType::QString, 26 }, { QMetaType::QDate, 27 }, { QMetaType::QString, 28 },
        }}),
        // Slot 'updateUserInfo'
        QtMocHelpers::SlotData<void(QString, QString, QDate)>(24, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 25 }, { QMetaType::QString, 26 }, { QMetaType::QDate, 27 },
        }}),
        // Slot 'loadAvatarPath'
        QtMocHelpers::SlotData<QString(QString)>(30, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::QString, 25 },
        }}),
        // Slot 'loadSignature'
        QtMocHelpers::SlotData<QString(QString)>(31, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::QString, 25 },
        }}),
        // Slot 'getUserOrders'
        QtMocHelpers::SlotData<void(const QString &)>(32, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 33 },
        }}),
        // Slot 'cancelOrder'
        QtMocHelpers::SlotData<void(const QString &)>(34, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 13 },
        }}),
        // Slot 'changeOrder'
        QtMocHelpers::SlotData<void(const QString &, const FlightInfo &, const QString &)>(35, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 13 }, { 0x80000000 | 36, 37 }, { QMetaType::QString, 38 },
        }}),
        // Slot 'addOrder'
        QtMocHelpers::SlotData<void(const OrderInfo &)>(39, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 40, 41 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<NetworkManager, qt_meta_tag_ZN14NetworkManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject NetworkManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14NetworkManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14NetworkManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14NetworkManagerE_t>.metaTypes,
    nullptr
} };

void NetworkManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<NetworkManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->loginResult((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<UserInfo>>(_a[2]))); break;
        case 1: _t->registerResult((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->updateUserInfoResult((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->flightSearchResult((*reinterpret_cast< std::add_pointer_t<QList<FlightInfo>>>(_a[1]))); break;
        case 4: _t->bookResult((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->orderListResult((*reinterpret_cast< std::add_pointer_t<QList<OrderInfo>>>(_a[1]))); break;
        case 6: _t->cancelOrderResult((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 7: _t->changeOrderResult((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 8: _t->sendRegisterRequest((*reinterpret_cast< std::add_pointer_t<UserInfo>>(_a[1]))); break;
        case 9: _t->sendLoginRequest((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 10: _t->updateUserInfo((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QDate>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5]))); break;
        case 11: _t->updateUserInfo((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QDate>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 12: _t->updateUserInfo((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QDate>>(_a[3]))); break;
        case 13: { QString _r = _t->loadAvatarPath((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 14: { QString _r = _t->loadSignature((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->getUserOrders((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->cancelOrder((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: _t->changeOrder((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<FlightInfo>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 18: _t->addOrder((*reinterpret_cast< std::add_pointer_t<OrderInfo>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (NetworkManager::*)(bool , UserInfo )>(_a, &NetworkManager::loginResult, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkManager::*)(bool , QString )>(_a, &NetworkManager::registerResult, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkManager::*)(bool )>(_a, &NetworkManager::updateUserInfoResult, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkManager::*)(const QList<FlightInfo> & )>(_a, &NetworkManager::flightSearchResult, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkManager::*)(bool , const QString & )>(_a, &NetworkManager::bookResult, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkManager::*)(const QList<OrderInfo> & )>(_a, &NetworkManager::orderListResult, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkManager::*)(bool , QString )>(_a, &NetworkManager::cancelOrderResult, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkManager::*)(bool , QString , QString )>(_a, &NetworkManager::changeOrderResult, 7))
            return;
    }
}

const QMetaObject *NetworkManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14NetworkManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NetworkManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void NetworkManager::loginResult(bool _t1, UserInfo _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void NetworkManager::registerResult(bool _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void NetworkManager::updateUserInfoResult(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void NetworkManager::flightSearchResult(const QList<FlightInfo> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void NetworkManager::bookResult(bool _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}

// SIGNAL 5
void NetworkManager::orderListResult(const QList<OrderInfo> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void NetworkManager::cancelOrderResult(bool _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2);
}

// SIGNAL 7
void NetworkManager::changeOrderResult(bool _t1, QString _t2, QString _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2, _t3);
}
QT_WARNING_POP
