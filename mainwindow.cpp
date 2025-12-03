#include "mainwindow.h"
#include "flight_result_widget.h"
#include <QCalendarWidget>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("航班票务管理系统");
    setFixedSize(1200, 700);

    // 初始化子部件
    loginWidget = new LoginWidget(this);
    registerWidget = new RegisterWidget(this);
    personalCenter = new PersonalCenterWidget(this);
    functionWidget = new QWidget(this);
    userInfoLabel = new QLabel(this);
    orderWidget = new OrderWidget(this);
    userInfoLabel->setStyleSheet("font-size: 14px; color: #333; margin-right: 20px;");

    // 初始化布局和功能区
    initUI();
    initFunctionWidget();

    // 初始状态
    loginWidget->show();
    registerWidget->hide();
    personalCenter->hide();
    functionWidget->hide();
    userInfoLabel->hide();
    orderWidget->hide();

    // 信号连接
    connect(loginWidget, &LoginWidget::loginSuccess, this, &MainWindow::onLoginSuccess);
    connect(loginWidget, &LoginWidget::showRegisterWidget, this, &MainWindow::showRegisterWidget);
    connect(registerWidget, &RegisterWidget::showLoginWidget, this, &MainWindow::showLoginWidget);
    connect(personalCenter, &PersonalCenterWidget::logoutSignal, this, &MainWindow::onLogout);
    connect(personalCenter, &PersonalCenterWidget::backToFunctionSignal, this, &MainWindow::backToFunction);
}

MainWindow::~MainWindow()
{
}

void MainWindow::initUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // 顶部导航栏
    QWidget *topBar = new QWidget(this);
    topBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #0078D7, stop:1 #1E90FF); height: 60px;");
    QHBoxLayout *topLayout = new QHBoxLayout(topBar);
    topLayout->setContentsMargins(25, 0, 25, 0);

    QLabel *sysTitle = new QLabel("✈️ 航班票务管理系统", this);
    sysTitle->setStyleSheet("font-size: 20px; font-weight: bold; color: white;");
    topLayout->addWidget(sysTitle);
    topLayout->addStretch();
    topLayout->addWidget(userInfoLabel);

    // 中间内容区
    mainLayout->addWidget(topBar);
    mainLayout->addWidget(loginWidget);
    mainLayout->addWidget(registerWidget);
    mainLayout->addWidget(functionWidget);
    mainLayout->addWidget(personalCenter);
    mainLayout->addWidget(orderWidget);
}

void MainWindow::initFunctionWidget()
{
functionWidget->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #F8FAFC, stop:1 #E3F2FD);");
    QVBoxLayout *funcLayout = new QVBoxLayout(functionWidget);
    funcLayout->setContentsMargins(40, 40, 40, 40);

    // 欢迎标题
    QWidget *welcomeWidget = new QWidget(this);
    welcomeWidget->setStyleSheet("background: transparent;");
    QVBoxLayout *welcomeLayout = new QVBoxLayout(welcomeWidget);

    QLabel *welcomeLabel = new QLabel("欢迎使用航班票务系统", this);
    welcomeLabel->setStyleSheet("font-size: 28px; font-weight: bold; color: #1A237E; margin-bottom: 10px;");
    welcomeLabel->setAlignment(Qt::AlignCenter);

    QLabel *subTitle = new QLabel("便捷查询、快速购票、轻松出行", this);
    subTitle->setStyleSheet("font-size: 16px; color: #546E7A; margin-bottom: 40px;");
    subTitle->setAlignment(Qt::AlignCenter);

    welcomeLayout->addWidget(welcomeLabel);
    welcomeLayout->addWidget(subTitle);
    funcLayout->addWidget(welcomeWidget);

    // 购票功能表单
    QWidget *queryForm = new QWidget(this);
    queryForm->setStyleSheet("background: white; border-radius: 15px; padding: 35px; box-shadow: 0 4px 12px rgba(0,0,0,0.1);");
    QGridLayout *formLayout = new QGridLayout(queryForm);
    formLayout->setVerticalSpacing(25);
    formLayout->setHorizontalSpacing(30);
    formLayout->setColumnStretch(1, 1);
    formLayout->setColumnStretch(3, 1);

    // 出发地
    QLabel *fromLabel = new QLabel("出发地：", this);
    fromLabel->setStyleSheet("font-size: 15px; font-weight: bold; color: #455A64;");
    QLineEdit *fromEdit = new QLineEdit(this);
    fromEdit->setPlaceholderText("例如：北京");
    fromEdit->setStyleSheet(R"(
        QLineEdit {
            border: 2px solid #E3F2FD;
            border-radius: 8px;
            padding: 12px 15px;
            font-size: 14px;
            background: #FAFAFA;
        }
        QLineEdit:focus {
            border-color: #0078D7;
            background: white;
        }
    )");
    formLayout->addWidget(fromLabel, 0, 0, Qt::AlignRight);
    formLayout->addWidget(fromEdit, 0, 1);

    // 目的地
    QLabel *toLabel = new QLabel("目的地：", this);
    toLabel->setStyleSheet("font-size: 15px; font-weight: bold; color: #455A64;");
    QLineEdit *toEdit = new QLineEdit(this);
    toEdit->setPlaceholderText("例如：上海");
    toEdit->setStyleSheet(R"(
        QLineEdit {
            border: 2px solid #E3F2FD;
            border-radius: 8px;
            padding: 12px 15px;
            font-size: 14px;
            background: #FAFAFA;
        }
        QLineEdit:focus {
            border-color: #0078D7;
            background: white;
        }
    )");
    formLayout->addWidget(toLabel, 0, 2, Qt::AlignRight);
    formLayout->addWidget(toEdit, 0, 3);

    // 查询按钮
    QPushButton *queryBtn = new QPushButton("🔍 查询航班", this);
    queryBtn->setStyleSheet(R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #0078D7, stop:1 #005A9E);
            color: white;
            border: none;
            border-radius: 10px;
            padding: 15px 40px;
            font-size: 16px;
            font-weight: bold;
            margin-top: 10px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #005A9E, stop:1 #004578);
        }
        QPushButton:pressed {
            background: #003366;
        }
    )");
    formLayout->addWidget(queryBtn, 1, 0, 1, 4, Qt::AlignCenter);

    funcLayout->addWidget(queryForm);
    funcLayout->addStretch();

    // 底部功能按钮区域
    QWidget *bottomFuncWidget = new QWidget(this);
    bottomFuncWidget->setStyleSheet("background: transparent;");
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomFuncWidget);
    bottomLayout->setSpacing(40);

    QPushButton *buyTicketBtn = createFunctionBtn("✈️ 首页", ":/images/ticket.png");
    QPushButton *orderBtn = createFunctionBtn("📋 我的订单", ":/images/order.png");
    QPushButton *profileBtn = createFunctionBtn("👤 个人资料", ":/images/profile.png");

    bottomLayout->addStretch();
    bottomLayout->addWidget(buyTicketBtn);
    bottomLayout->addWidget(orderBtn);
    bottomLayout->addWidget(profileBtn);
    bottomLayout->addStretch();

    funcLayout->addWidget(bottomFuncWidget);

    // 按钮点击事件
    connect(queryBtn, &QPushButton::clicked, this, [=]() {
        QString from = fromEdit->text().trimmed();
        QString to = toEdit->text().trimmed();
        QDate date = QDate::currentDate(); // 使用当前日期作为默认值

        if (from.isEmpty() || to.isEmpty()) {
            QMessageBox::warning(this, "提示", "请输入出发地和目的地");
            return;
        }

        // 隐藏功能区，显示查询结果
        functionWidget->hide();

        // 创建并显示航班结果窗口
        FlightResultWidget *resultWidget = new FlightResultWidget(this);
        resultWidget->setSearchConditions(from, to, date);
        resultWidget->setFixedSize(this->size());
        resultWidget->move(0, 0);
        this->centralWidget()->layout()->addWidget(resultWidget);
        resultWidget->show();
        resultWidget->raise();
        resultWidget->activateWindow();

        // 连接信号
        connect(NetworkManager::getInstance(), &NetworkManager::flightSearchResult,
                resultWidget, &FlightResultWidget::updateFlightList);

        connect(resultWidget, &FlightResultWidget::backToSearchSignal, this, [=]() {
            // 先断开所有网络连接
            disconnect(NetworkManager::getInstance(), nullptr, resultWidget, nullptr);

            this->centralWidget()->layout()->removeWidget(resultWidget);
            resultWidget->hide();
            resultWidget->deleteLater();
            functionWidget->show();
        });

        connect(resultWidget, &FlightResultWidget::bookTicketSignal, this, [=](const FlightInfo &flight, const QString &seatClass, const QString &passengerType, int ticketCount) {
            // ticketCount 现在总是1
            auto *connection = new QMetaObject::Connection();
            *connection = connect(NetworkManager::getInstance(), &NetworkManager::bookResult,this, [=](bool success, const QStringList &orderIds, const QStringList &seatNumbers) {
                disconnect(*connection);
                delete connection;

                if (success) {
                    QString message = QString("购票成功！\n订单号：%1\n航班：%2\n舱位：%3\n乘客类型：%4\n座位号：%5")
                                        .arg(orderIds.first())
                                        .arg(flight.flightNumber)
                                        .arg(seatClass)
                                        .arg(passengerType)
                                        .arg(seatNumbers.first());

                    QMessageBox::information(this, "成功", message);

                    // 返回主界面
                    if (resultWidget) {
                        this->centralWidget()->layout()->removeWidget(resultWidget);
                        resultWidget->hide();
                        resultWidget->deleteLater();
                        functionWidget->show();
                    }
                } else {
                    QMessageBox::warning(this, "失败", "购票失败，请重试");
                }
            });

            // 发起购票请求，票数固定为1
            NetworkManager::getInstance()->bookFlight(flight, seatClass, currentUser.account, 1);
        });

        NetworkManager::getInstance()->searchFlights(from, to, date);
    });
    connect(buyTicketBtn, &QPushButton::clicked, this, [=]() {
        QMessageBox::information(this, "提示", "已是首页");
    });
    connect(orderBtn, &QPushButton::clicked, this, &MainWindow::showOrderWidget);
    connect(profileBtn, &QPushButton::clicked, this, &MainWindow::toPersonalCenter);
}

// 登录成功：切换到功能区
void MainWindow::onLoginSuccess(UserInfo userInfo)
{
    currentUser = userInfo;
    loginWidget->hide();
    registerWidget->hide();
    functionWidget->show();
    personalCenter->hide();
    userInfoLabel->setText("👤 当前用户：" + userInfo.username);
    userInfoLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold; background: rgba(255,255,255,0.2); padding: 8px 15px; border-radius: 15px;");
    userInfoLabel->show();
}

// 退出登录：返回登录页
void MainWindow::onLogout()
{
    functionWidget->hide();
    personalCenter->hide();
    userInfoLabel->hide();
    loginWidget->show();
    currentUser = UserInfo();
}

// 显示登录页
void MainWindow::showLoginWidget()
{
    registerWidget->hide();
    loginWidget->show();
}

// 显示注册页
void MainWindow::showRegisterWidget()
{
    loginWidget->hide();
    registerWidget->show();
}

// 返回功能区
void MainWindow::backToFunction()
{
    personalCenter->hide();
    functionWidget->show();
}

// 进入个人中心
void MainWindow::toPersonalCenter()
{
    functionWidget->hide();
    personalCenter->setUserInfo(currentUser);
    personalCenter->show();
}

// 创建功能按钮
QPushButton* MainWindow::createFunctionBtn(const QString &text, const QString &iconPath) {
    QPushButton *btn = new QPushButton(text);
    btn->setFixedSize(180, 80);

    btn->setStyleSheet(R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #0078D7,
                stop:0.5 #1E90FF,
                stop:1 #0078D7);
            color: white;
            border: none;
            border-radius: 12px;
            font-size: 16px;
            font-weight: bold;
            padding: 15px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #005A9E,
                stop:0.5 #0078D7,
                stop:1 #005A9E);
            border: 2px solid #B3E0FF;
        }
        QPushButton:pressed {
            background: #004578;
        }
    )");

    if (!iconPath.isEmpty()) {
        btn->setIcon(QIcon(iconPath));
        btn->setIconSize(QSize(32, 32));
    }

    return btn;
}

void MainWindow::showOrderWidget()
{
    functionWidget->hide();
    orderWidget->setUserId(currentUser.account);
    orderWidget->show();

    // 连接返回信号
    connect(orderWidget, &OrderWidget::backToFunctionSignal, this, [=]() {
        orderWidget->hide();
        functionWidget->show();
        disconnect(orderWidget, &OrderWidget::backToFunctionSignal, nullptr, nullptr);
    });
}
