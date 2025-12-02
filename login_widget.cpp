#include "login_widget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background-color: #F5F8FA;");

    // 标题
    QLabel *titleLabel = new QLabel("账号登录", this);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #333;");
    titleLabel->setAlignment(Qt::AlignCenter);

    // 账号/用户名输入区
    QWidget *accountWidget = new QWidget(this);
    accountWidget->setStyleSheet("background-color: white; border-radius: 25px;");
    accountWidget->setFixedHeight(45);
    QHBoxLayout *accountLayout = new QHBoxLayout(accountWidget);
    accountLayout->setContentsMargins(20, 0, 20, 0);
    QLabel *accountIcon = new QLabel(this);
    accountIcon->setPixmap(QIcon::fromTheme("user").pixmap(22, 22));
    accountOrUsernameEdit = new QLineEdit(this);
    accountOrUsernameEdit->setPlaceholderText("请输入账号或手机号");
    accountOrUsernameEdit->setStyleSheet("border: none; outline: none; font-size: 14px; color: #333;");
    accountLayout->addWidget(accountIcon);
    accountLayout->addSpacing(10);
    accountLayout->addWidget(accountOrUsernameEdit);

    // 密码输入区
    QWidget *passwordWidget = new QWidget(this);
    passwordWidget->setStyleSheet("background-color: white; border-radius: 25px;");
    passwordWidget->setFixedHeight(45);
    QHBoxLayout *passwordLayout = new QHBoxLayout(passwordWidget);
    passwordLayout->setContentsMargins(20, 0, 20, 0);
    QLabel *pwdIcon = new QLabel(this);
    pwdIcon->setPixmap(QIcon::fromTheme("password").pixmap(22, 22));
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("请输入密码");
    passwordEdit->setStyleSheet("border: none; outline: none; font-size: 14px; color: #333;");
    passwordLayout->addWidget(pwdIcon);
    passwordLayout->addSpacing(10);
    passwordLayout->addWidget(passwordEdit);

    // 登录按钮
    loginBtn = new QPushButton("登录", this);
    loginBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #0084FF;
            color: white;
            border: none;
            border-radius: 25px;
            font-size: 16px;
            font-weight: 500;
            height: 45px;
        }
        QPushButton:hover {
            background-color: #0078E7;
        }
        QPushButton:disabled {
            background-color: #8CC5FF;
        }
    )");

    // 注册按钮
    registerBtn = new QPushButton("注册账号", this);
    registerBtn->setStyleSheet(R"(
        QPushButton {
            background-color: white;
            color: #0084FF;
            border: 1px solid #0084FF;
            border-radius: 25px;
            font-size: 16px;
            font-weight: 500;
            height: 45px;
        }
        QPushButton:hover {
            background-color: #F0F7FF;
        }
    )");

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(60, 100, 60, 60);
    mainLayout->setSpacing(25);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(accountWidget);
    mainLayout->addWidget(passwordWidget);
    mainLayout->addStretch();
    mainLayout->addWidget(loginBtn);
    mainLayout->addWidget(registerBtn);

    // 信号连接
    connect(loginBtn, &QPushButton::clicked, this, &LoginWidget::onLoginClicked);
    connect(registerBtn, &QPushButton::clicked, this, &LoginWidget::showRegisterWidget);
    connect(NetworkManager::getInstance(), &NetworkManager::loginResult, this, &LoginWidget::onLoginResult);
}

void LoginWidget::onLoginClicked()
{
    QString accountOrUsername = accountOrUsernameEdit->text().trimmed();
    QString password = passwordEdit->text().trimmed();

    if (accountOrUsername.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "提示", "账号/用户名或密码不能为空！");
        return;
    }

    loginBtn->setDisabled(true);
    // 提交登录请求（支持账号/用户名）
    NetworkManager::getInstance()->sendLoginRequest(accountOrUsername, password);
}

void LoginWidget::onRegisterClicked()
{
    emit showRegisterWidget();
}

// 接收登录结果
void LoginWidget::onLoginResult(bool success, UserInfo userInfo)
{
    loginBtn->setEnabled(true);
    if (success) {
        emit loginSuccess(userInfo); // 登录成功，传递完整用户信息
        // 清空输入
        accountOrUsernameEdit->clear();
        passwordEdit->clear();
    } else {
        QMessageBox::warning(this, "登录失败", "账号/用户名或密码错误！");
    }
}
