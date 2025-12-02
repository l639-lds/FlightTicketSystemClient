#include "network_manager.h"
#include <QSettings>
#include <random>
#include <QDateTime>
#include <QRandomGenerator>

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
    UserInfo testUser;
    testUser.account = "1";
    testUser.username = "测试用户";
    testUser.password = "111111";
    testUser.phone = "11111111111";
    testUser.gender = "男";
    testUser.birthDate = QDate(2000,1,1);
    testUser.avatarPath = "";
    testUser.signature = "无"; // 默认个性签名
    testUser.idType = "居民身份证";
    testUser.idNumber = "123456789123456789";
    userMap[testUser.account] = testUser;
    usernameSet.insert(testUser.username);

    // 添加测试订单
    OrderInfo testOrder;
    testOrder.orderId = "ORD20241201123456";
    testOrder.flightNumber = "CA1234";
    testOrder.departureCity = "北京";
    testOrder.arrivalCity = "上海";
    testOrder.date = QDate::currentDate().addDays(1);
    testOrder.departureTime = QTime(8, 30);
    testOrder.seatClass = "经济舱";
    testOrder.passengerType = "成人";
    testOrder.price = 900.00;
    testOrder.status = "已支付";
    testOrder.createTime = QDateTime::currentDateTime();
    testOrder.userId = "1";
    testOrder.remainingTime = 60 * 24;  // 24小时
    testOrder.flightDuration = 140;

    orderMap[testOrder.orderId] = testOrder;
    userOrdersMap["1"].append(testOrder.orderId);
}

// 添加新订单
void NetworkManager::addOrder(const OrderInfo &order)
{
    orderMap[order.orderId] = order;
    userOrdersMap[order.userId].append(order.orderId);
    qDebug() << "新增订单:" << order.orderId << "用户:" << order.userId;
}

// 获取用户订单
void NetworkManager::getUserOrders(const QString &userId)
{
    QList<OrderInfo> orders;

    if (userOrdersMap.contains(userId)) {
        const QList<QString> &orderIds = userOrdersMap[userId];
        foreach (const QString &orderId, orderIds) {
            if (orderMap.contains(orderId)) {
                OrderInfo order = orderMap[orderId];
                // 跳过已取消的订单
                if (order.status == "已取消") {
                    continue;
                }
                // 更新剩余时间（模拟）
                QDateTime now = QDateTime::currentDateTime();
                int elapsed = order.createTime.secsTo(now) / 60;
                order.remainingTime = qMax(0, 60 * 24 - elapsed);  // 24小时有效期
                orders.append(order);
            }
        }
    }

    qDebug() << "查询用户订单:" << userId << "找到" << orders.size() << "个订单";
    emit orderListResult(orders);
}

// 取消订单
void NetworkManager::cancelOrder(const QString &orderId)
{
    if (orderMap.contains(orderId)) {
        OrderInfo &order = orderMap[orderId];

        // 检查是否可取消（根据剩余时间）
        if (order.remainingTime <= 0) {
            emit cancelOrderResult(false, "订单已超过可取消时间");
            return;
        }

        if (order.status == "已支付") {
            order.status = "已取消";
            emit cancelOrderResult(true, "订单取消成功");
        } else {
            emit cancelOrderResult(false, "当前状态不可取消");
        }
    } else {
        emit cancelOrderResult(false, "订单不存在");
    }
}

// 改签订单
void NetworkManager::changeOrder(const QString &orderId, const FlightInfo &newFlight, const QString &newSeatClass)
{
    if (orderMap.contains(orderId)) {
        OrderInfo &order = orderMap[orderId];

        // 检查是否可改签
        if (order.status != "已支付") {
            emit changeOrderResult(false, "当前状态不可改签", "");
            return;
        }

        // 创建新的改签订单
        OrderInfo newOrder = order;
        newOrder.orderId = QString("CHG%1%2").arg(QDateTime::currentMSecsSinceEpoch()).arg(QRandomGenerator::global()->bounded(1000));
        newOrder.flightNumber = newFlight.flightNumber;
        newOrder.departureCity = newFlight.departureCity;
        newOrder.arrivalCity = newFlight.arrivalCity;
        newOrder.date = newFlight.date;
        newOrder.departureTime = newFlight.departureTime;
        newOrder.seatClass = newSeatClass;

        // 更新价格
        if (newSeatClass == "经济舱") newOrder.price = newFlight.economyPrice;
        else if (newSeatClass == "商务舱") newOrder.price = newFlight.businessPrice;
        else if (newSeatClass == "头等舱") newOrder.price = newFlight.firstClassPrice;

        newOrder.status = "已支付";
        newOrder.createTime = QDateTime::currentDateTime();
        newOrder.remainingTime = 60 * 24;

        // 原订单状态改为已改签
        order.status = "已改签";
        order.remainingTime = 0;

        // 添加新订单
        addOrder(newOrder);

        emit changeOrderResult(true, "改签成功", newOrder.orderId);
    } else {
        emit changeOrderResult(false, "订单不存在", "");
    }
}

void NetworkManager::sendRegisterRequest(UserInfo userInfo)
{
    if(usernameSet.contains(userInfo.username)){
        emit registerResult(false, "用户名已被占用！");
        return;
    }
    if(userInfo.signature.isEmpty()) userInfo.signature = "无";
    userMap[userInfo.account] = userInfo;
    usernameSet.insert(userInfo.username);
    emit registerResult(true, "注册成功！");
}

void NetworkManager::sendLoginRequest(QString accountOrPhone, QString password)
{
    for(auto it = userMap.begin(); it != userMap.end(); ++it){
        UserInfo user = it.value();
        if((user.account == accountOrPhone || user.phone == accountOrPhone)
            && user.password == password){
            emit loginResult(true, user);
            return;
        }
    }
    emit loginResult(false, UserInfo());
}

void NetworkManager::updateUserInfo(QString account, QString gender, QDate birthDate,
                                    QString avatarPath, QString signature)
{
    if(userMap.contains(account)){
        UserInfo &user = userMap[account];
        user.gender = gender;
        user.birthDate = birthDate;
        if(!avatarPath.isEmpty()) user.avatarPath = avatarPath;
        user.signature = signature.isEmpty() ? "无" : signature;

        QSettings settings("FlightTicketSystem", "UserInfo");
        settings.setValue("avatar/" + account, avatarPath);
        settings.setValue("signature/" + account, user.signature);
        emit updateUserInfoResult(true);
    } else {
        emit updateUserInfoResult(false);
    }
}

QString NetworkManager::loadAvatarPath(QString account)
{
    QSettings settings("FlightTicketSystem", "UserInfo");
    return settings.value("avatar/" + account, "").toString();
}

QString NetworkManager::loadSignature(QString account)
{
    QSettings settings("FlightTicketSystem", "UserInfo");
    return settings.value("signature/" + account, "无").toString();
}

void NetworkManager::searchFlights(const QString &from, const QString &to, const QDate &date)
{
    QList<FlightInfo> flights = mockFlightData();
    QList<FlightInfo> result;

    qDebug() << "搜索航班: 从" << from << "到" << to << "日期:" << date.toString("yyyy-MM-dd");
    qDebug() << "模拟数据总数:" << flights.size();

    foreach (const FlightInfo &f, flights) {
        qDebug() << "检查航班:" << f.flightNumber
                 << "出发:" << f.departureCity << "到达:" << f.arrivalCity
                 << "日期:" << f.date.toString("yyyy-MM-dd");

        // 精确匹配出发城市和到达城市，以及日期
        if (f.departureCity == from &&
            f.arrivalCity == to &&
            f.date == date) {
            qDebug() << "找到匹配航班:" << f.flightNumber;
            result.append(f);
        }
    }

    qDebug() << "找到" << result.size() << "个匹配航班";

    // 添加无结果提示
    if (result.isEmpty()) {
        qDebug() << "未找到从" << from << "到" << to << "在" << date.toString("yyyy-MM-dd") << "的航班";
    }

    emit flightSearchResult(result);
}

void NetworkManager::bookFlight(const FlightInfo &flight, const QString &seatClass, const QString &userId)
{
    // 模拟购票成功
    bool success = true;

    // 使用 C++11 随机数
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 999);

    QString orderId = QString("ORD%1%2").arg(QDateTime::currentMSecsSinceEpoch()).arg(dis(gen));

    // 创建订单信息
    OrderInfo order;
    order.orderId = orderId;
    order.flightNumber = flight.flightNumber;
    order.departureCity = flight.departureCity;
    order.arrivalCity = flight.arrivalCity;
    order.date = flight.date;
    order.departureTime = flight.departureTime;
    order.seatClass = seatClass;
    order.passengerType = "成人";  // 这里可以根据实际情况调整
    order.price = (seatClass == "经济舱") ? flight.economyPrice :
                      (seatClass == "商务舱") ? flight.businessPrice :
                      flight.firstClassPrice;
    order.status = "已支付";
    order.createTime = QDateTime::currentDateTime();
    order.userId = userId;
    order.remainingTime = 60 * 24;  // 24小时
    order.flightDuration = flight.duration;

    // 保存订单
    addOrder(order);

    emit bookResult(success, orderId);
}

QList<FlightInfo> NetworkManager::mockFlightData()
{
    QList<FlightInfo> flights;

    // 模拟一些航班数据
    FlightInfo f1;
    f1.flightNumber = "CA1234";
    f1.departureCity = "北京";
    f1.arrivalCity = "上海";
    f1.date = QDate::currentDate();
    f1.departureTime = QTime(8, 30);
    f1.arrivalTime = QTime(10, 50);
    f1.duration = 140;
    f1.firstClassPrice = 2500.00;
    f1.businessPrice = 1800.00;
    f1.economyPrice = 900.00;
    f1.firstClassSeats = 5;
    f1.businessSeats = 10;
    f1.economySeats = 30;
    flights.append(f1);

    FlightInfo f2;
    f2.flightNumber = "MU5678";
    f2.departureCity = "北京";
    f2.arrivalCity = "上海";
    f2.date = QDate::currentDate();
    f2.departureTime = QTime(14, 15);
    f2.arrivalTime = QTime(16, 35);
    f2.duration = 140;
    f2.firstClassPrice = 2600.00;
    f2.businessPrice = 1900.00;
    f2.economyPrice = 950.00;
    f2.firstClassSeats = 3;
    f2.businessSeats = 7;
    f2.economySeats = 25;
    flights.append(f2);

    // 可以添加更多模拟航班...
    FlightInfo f3;
    f3.flightNumber = "CA1234";
    f3.departureCity = "北京";
    f3.arrivalCity = "上海";
    f3.date = QDate(2025,12,2);
    f3.departureTime = QTime(8, 30);
    f3.arrivalTime = QTime(10, 50);
    f3.duration = 140;
    f3.firstClassPrice = 2500.00;
    f3.businessPrice = 1800.00;
    f3.economyPrice = 900.00;
    f3.firstClassSeats = 5;
    f3.businessSeats = 10;
    f3.economySeats = 30;
    flights.append(f3);

    FlightInfo f4;
    f4.flightNumber = "MU5678";
    f4.departureCity = "北京";
    f4.arrivalCity = "上海";
    f4.date = QDate(2025,12,5);
    f4.departureTime = QTime(15, 15);
    f4.arrivalTime = QTime(17, 35);
    f4.duration = 140;
    f4.firstClassPrice = 2700.00;
    f4.businessPrice = 2000.00;
    f4.economyPrice = 1000.00;
    f4.firstClassSeats = 6;
    f4.businessSeats = 12;
    f4.economySeats = 35;
    flights.append(f4);

    return flights;
}
