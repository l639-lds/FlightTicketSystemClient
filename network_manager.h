#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H
#include <QObject>
#include <QMap>
#include <QString>
#include <QDate>

struct UserInfo {
    QString account;      // 账号
    QString username;     // 用户名
    QString password;     // 密码
    QString phone;        // 手机号
    QString gender;       // 性别
    QDate birthDate;      // 生日
    QString avatarPath;   // 头像路径
    QString signature;    // 个性签名
    QString idType;       // 证件类型
    QString idNumber;     // 证件号码
};

struct FlightInfo {
    QString flightNumber;    // 航班号
    QString departureCity;   // 出发城市
    QString arrivalCity;     // 到达城市
    QDate date;              // 日期
    QTime departureTime;     // 出发时间
    QTime arrivalTime;       // 到达时间
    int duration;            // 时长(分钟)
    double firstClassPrice;  // 头等舱价格
    double businessPrice;    // 商务舱价格
    double economyPrice;     // 经济舱价格
    int firstClassSeats;     // 头等舱余票
    int businessSeats;       // 商务舱余票
    int economySeats;        // 经济舱余票
};

struct OrderInfo {
    QString orderId;           // 订单号
    QString flightNumber;      // 航班号
    QString departureCity;     // 出发城市
    QString arrivalCity;       // 到达城市
    QDate date;                // 出行日期
    QTime departureTime;       // 出发时间
    QString seatClass;         // 舱位类型
    QString passengerType;     // 乘客类型
    double price;              // 价格
    QString status;            // 订单状态：已支付、已取消、已完成、已改签
    QDateTime createTime;      // 创建时间
    QString userId;            // 用户ID
    int remainingTime;         // 剩余可取消时间（分钟）
    int flightDuration;        // 航班行驶时间（分钟）
};

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    static NetworkManager* getInstance(QObject *parent = nullptr){
        static NetworkManager* instance = nullptr;
        if(!instance) instance = new NetworkManager(parent);
        return instance;
    }
    NetworkManager(const NetworkManager&) = delete;
    NetworkManager& operator=(const NetworkManager&) = delete;
    void searchFlights(const QString &from, const QString &to, const QDate &date);
    void bookFlight(const FlightInfo &flight, const QString &seatClass, const QString &userId);

signals:
    void loginResult(bool success, UserInfo userInfo);
    void registerResult(bool success, QString errMsg);
    void updateUserInfoResult(bool success);
    void flightSearchResult(const QList<FlightInfo> &flights);
    void bookResult(bool success, const QString &orderId);
    void orderListResult(const QList<OrderInfo> &orders);  // 订单列表查询结果
    void cancelOrderResult(bool success, QString errMsg);  // 取消订单结果
    void changeOrderResult(bool success, QString errMsg, QString newOrderId);

public slots:
    void sendRegisterRequest(UserInfo userInfo);
    void sendLoginRequest(QString accountOrUsername, QString password);
    void updateUserInfo(QString account, QString gender, QDate birthDate,
                        QString avatarPath = "", QString signature = "");
    QString loadAvatarPath(QString account);
    QString loadSignature(QString account);
    void getUserOrders(const QString &userId);              // 获取用户订单
    void cancelOrder(const QString &orderId);              // 取消订单
    void changeOrder(const QString &orderId, const FlightInfo &newFlight, const QString &newSeatClass); // 改签订单
    void addOrder(const OrderInfo &order);                 // 添加新订单（用于购票成功后）

private:
    explicit NetworkManager(QObject *parent = nullptr);
    QMap<QString, UserInfo> userMap;
    QSet<QString> usernameSet;
    QList<FlightInfo> mockFlightData();
    QMap<QString, OrderInfo> orderMap;                     // 订单存储
    QMap<QString, QList<QString>> userOrdersMap;           // 用户订单映射
};

#endif // NETWORK_MANAGER_H
