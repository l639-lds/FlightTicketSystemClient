#include "register_widget.h"

RegisterWidget::RegisterWidget(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background-color: #F5F8FA;");

    // 标题
    QLabel *titleLabel = new QLabel("账号注册", this);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #333;");
    titleLabel->setAlignment(Qt::AlignCenter);

    // 1. 账号输入区
    QWidget *accountWidget = new QWidget(this);
    accountWidget->setStyleSheet("background-color: white; border-radius: 25px;");
    accountWidget->setFixedHeight(45);
    QHBoxLayout *accountLayout = new QHBoxLayout(accountWidget);
    accountLayout->setContentsMargins(20, 0, 20, 0);
    QLabel *accountIcon = new QLabel(this);
    accountIcon->setPixmap(QIcon::fromTheme("user").pixmap(22, 22));
    accountEdit = new QLineEdit(this);
    accountEdit->setPlaceholderText("请设置账号（登录可用）");
    accountEdit->setStyleSheet("border: none; outline: none; font-size: 14px; color: #333;");
    accountLayout->addWidget(accountIcon);
    accountLayout->addSpacing(10);
    accountLayout->addWidget(accountEdit);

    // 2. 用户名输入区（唯一）
    QWidget *usernameWidget = new QWidget(this);
    usernameWidget->setStyleSheet("background-color: white; border-radius: 25px;");
    usernameWidget->setFixedHeight(45);
    QHBoxLayout *usernameLayout = new QHBoxLayout(usernameWidget);
    usernameLayout->setContentsMargins(20, 0, 20, 0);
    QLabel *usernameIcon = new QLabel(this);
    usernameIcon->setPixmap(QIcon::fromTheme("user").pixmap(22, 22));
    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("请设置用户名（登录不可用）");
    usernameEdit->setStyleSheet("border: none; outline: none; font-size: 14px; color: #333;");
    usernameLayout->addWidget(usernameIcon);
    usernameLayout->addSpacing(10);
    usernameLayout->addWidget(usernameEdit);

    // 3. 密码输入区
    QWidget *passwordWidget = new QWidget(this);
    passwordWidget->setStyleSheet("background-color: white; border-radius: 25px;");
    passwordWidget->setFixedHeight(45);
    QHBoxLayout *passwordLayout = new QHBoxLayout(passwordWidget);
    passwordLayout->setContentsMargins(20, 0, 20, 0);
    QLabel *pwdIcon = new QLabel(this);
    pwdIcon->setPixmap(QIcon::fromTheme("password").pixmap(22, 22));
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("请设置密码（不少于6位）");
    passwordEdit->setStyleSheet("border: none; outline: none; font-size: 14px; color: #333;");
    passwordLayout->addWidget(pwdIcon);
    passwordLayout->addSpacing(10);
    passwordLayout->addWidget(passwordEdit);

    // 4.确认密码输入区
    QWidget *confirmPwdWidget = new QWidget(this);
    confirmPwdWidget->setStyleSheet("background-color: white; border-radius: 25px;");
    confirmPwdWidget->setFixedHeight(45);
    QHBoxLayout *confirmPwdLayout = new QHBoxLayout(confirmPwdWidget);
    confirmPwdLayout->setContentsMargins(20, 0, 20, 0);
    QLabel *confirmPwdIcon = new QLabel(this);
    confirmPwdIcon->setPixmap(QIcon::fromTheme("password").pixmap(22, 22));
    confirmPwdEdit = new QLineEdit(this);
    confirmPwdEdit->setEchoMode(QLineEdit::Password);
    confirmPwdEdit->setPlaceholderText("请再次输入密码");
    confirmPwdEdit->setStyleSheet("border: none; outline: none; font-size: 14px; color: #333;");
    confirmPwdLayout->addWidget(confirmPwdIcon);
    confirmPwdLayout->addSpacing(10);
    confirmPwdLayout->addWidget(confirmPwdEdit);

    // 5. 手机号输入区
    QWidget *phoneWidget = new QWidget(this);
    phoneWidget->setStyleSheet("background-color: white; border-radius: 25px;");
    phoneWidget->setFixedHeight(45);
    QHBoxLayout *phoneLayout = new QHBoxLayout(phoneWidget);
    phoneLayout->setContentsMargins(20, 0, 20, 0);
    QLabel *phoneIcon = new QLabel(this);
    phoneIcon->setPixmap(QIcon::fromTheme("phone").pixmap(22, 22));
    phoneEdit = new QLineEdit(this);
    phoneEdit->setPlaceholderText("请输入手机号（11位数字）");
    phoneEdit->setStyleSheet("border: none; outline: none; font-size: 14px; color: #333;");
    phoneLayout->addWidget(phoneIcon);
    phoneLayout->addSpacing(10);
    phoneLayout->addWidget(phoneEdit);

    // 新增：证件类型选择区
    QWidget *idTypeWidget = new QWidget(this);
    idTypeWidget->setStyleSheet("background-color: white; border-radius: 25px;");
    idTypeWidget->setFixedHeight(45);
    QHBoxLayout *idTypeLayout = new QHBoxLayout(idTypeWidget);
    idTypeLayout->setContentsMargins(20, 0, 20, 0);
    QLabel *idTypeIcon = new QLabel(this);
    idTypeIcon->setPixmap(QIcon::fromTheme("card").pixmap(22, 22));
    QLabel *idTypeLabel = new QLabel("证件类型：", this);
    idTypeLabel->setStyleSheet("font-size: 14px; color: #666;");
    idTypeCombo = new QComboBox(this);
    idTypeCombo->addItems({"居民身份证", "护照", "军官证", "其他"});
    idTypeCombo->setStyleSheet("border: none; outline: none; font-size: 14px; color: #333;");
    idTypeLayout->addWidget(idTypeIcon);
    idTypeLayout->addSpacing(10);
    idTypeLayout->addWidget(idTypeLabel);
    idTypeLayout->addSpacing(5);
    idTypeLayout->addWidget(idTypeCombo);

    // 新增：证件号输入区
    QWidget *idNumberWidget = new QWidget(this);
    idNumberWidget->setStyleSheet("background-color: white; border-radius: 25px;");
    idNumberWidget->setFixedHeight(45);
    QHBoxLayout *idNumberLayout = new QHBoxLayout(idNumberWidget);
    idNumberLayout->setContentsMargins(20, 0, 20, 0);
    QLabel *idNumberIcon = new QLabel(this);
    idNumberIcon->setPixmap(QIcon::fromTheme("card").pixmap(22, 22));
    idNumberEdit = new QLineEdit(this);
    idNumberEdit->setPlaceholderText("请输入证件号码");
    idNumberEdit->setStyleSheet("border: none; outline: none; font-size: 14px; color: #333;");
    idNumberLayout->addWidget(idNumberIcon);
    idNumberLayout->addSpacing(10);
    idNumberLayout->addWidget(idNumberEdit);

    // 6. 性别选择区
    QWidget *genderWidget = new QWidget(this);
    genderWidget->setStyleSheet("background-color: white; border-radius: 25px;");
    genderWidget->setFixedHeight(45);
    QHBoxLayout *genderLayout = new QHBoxLayout(genderWidget);
    genderLayout->setContentsMargins(20, 0, 20, 0);
    QLabel *genderIcon = new QLabel(this);
    genderIcon->setPixmap(QIcon::fromTheme("user").pixmap(22, 22));
    QLabel *genderLabel = new QLabel("性别：", this);
    genderLabel->setStyleSheet("font-size: 14px; color: #666;");
    genderCombo = new QComboBox(this);
    genderCombo->addItems({"男", "女"});
    genderCombo->setStyleSheet("border: none; outline: none; font-size: 14px; color: #333;");
    genderLayout->addWidget(genderIcon);
    genderLayout->addSpacing(10);
    genderLayout->addWidget(genderLabel);
    genderLayout->addSpacing(5);
    genderLayout->addWidget(genderCombo);

    // 7. 出生年月选择区
    QWidget *birthDateWidget = new QWidget(this);
    birthDateWidget->setStyleSheet("background-color: white; border-radius: 25px;");
    birthDateWidget->setFixedHeight(45);
    QHBoxLayout *birthDateLayout = new QHBoxLayout(birthDateWidget);
    birthDateLayout->setContentsMargins(20, 0, 20, 0);
    QLabel *birthDateIcon = new QLabel(this);
    birthDateIcon->setPixmap(QIcon::fromTheme("calendar").pixmap(22, 22));
    QLabel *birthDateLabel = new QLabel("出生年月：", this);
    birthDateLabel->setStyleSheet("font-size: 14px; color: #666;");
    birthDateEdit = new QDateEdit(this);
    birthDateEdit->setDate(QDate::currentDate().addYears(-20)); // 默认20年前
    birthDateEdit->setDisplayFormat("yyyy-MM-dd");
    birthDateEdit->setStyleSheet("border: none; outline: none; font-size: 14px; color: #333;");
    birthDateLayout->addWidget(birthDateIcon);
    birthDateLayout->addSpacing(10);
    birthDateLayout->addWidget(birthDateLabel);
    birthDateLayout->addSpacing(5);
    birthDateLayout->addWidget(birthDateEdit);

    // 注册按钮
    registerBtn = new QPushButton("注册", this);
    registerBtn->setStyleSheet(R"(
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

    // 返回登录按钮
    backLoginBtn = new QPushButton("返回登录", this);
    backLoginBtn->setStyleSheet(R"(
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
    mainLayout->setContentsMargins(60, 50, 60, 60);
    mainLayout->setSpacing(15);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(usernameWidget);
    mainLayout->addWidget(accountWidget);
    mainLayout->addWidget(passwordWidget);
    mainLayout->addWidget(confirmPwdWidget);
    mainLayout->addWidget(phoneWidget);
    mainLayout->addWidget(idTypeWidget);
    mainLayout->addWidget(idNumberWidget);
    mainLayout->addWidget(genderWidget);
    mainLayout->addWidget(birthDateWidget);
    mainLayout->addStretch();
    mainLayout->addWidget(registerBtn);
    mainLayout->addWidget(backLoginBtn);

    // 信号连接
    connect(registerBtn, &QPushButton::clicked, this, &RegisterWidget::onRegisterClicked);
    connect(backLoginBtn, &QPushButton::clicked, this, &RegisterWidget::onBackLoginClicked);
    connect(NetworkManager::getInstance(), &NetworkManager::registerResult, this, &RegisterWidget::onRegisterResult);
}

// 注册按钮点击：收集信息并提交
void RegisterWidget::onRegisterClicked()
{
    // 收集输入信息（去除空格）
    UserInfo user;
    user.account = accountEdit->text().trimmed();
    user.username = usernameEdit->text().trimmed();
    user.password = passwordEdit->text().trimmed();
    QString confirmPwd = confirmPwdEdit->text().trimmed();
    user.phone = phoneEdit->text().trimmed();
    QString idType = idTypeCombo->currentText();
    QString idNumber = idNumberEdit->text().trimmed();
    user.gender = genderCombo->currentText();
    user.birthDate = birthDateEdit->date();

    // 输入校验
    if (user.account.isEmpty() || user.username.isEmpty() ||
        user.password.isEmpty() || confirmPwd.isEmpty() ||  // 新增确认密码校验
        user.phone.isEmpty() || idNumber.isEmpty()) {       // 新增证件号校验
        QMessageBox::warning(this, "提示", "带*的字段、密码、确认密码、手机号和证件号不能为空！");
        return;
    }
    // 密码一致性校验
    if (user.password != confirmPwd) {
        QMessageBox::warning(this, "提示", "两次输入的密码不一致！");
        return;
    }
    if (user.password.length() < 6) {
        QMessageBox::warning(this, "提示", "密码长度不能少于6位！");
        return;
    }
    if (user.phone.length() != 11 || user.phone[0] != '1') {
        QMessageBox::warning(this, "提示", "请输入正确的手机号（11位且以1开头）！");
        return;
    }
    // 证件号校验（简单校验，可根据实际需求增强）
    if (idType == "居民身份证" && idNumber.length() != 18) {
        QMessageBox::warning(this, "提示", "身份证号必须为18位！");
        return;
    }

    // 提交注册请求
    registerBtn->setDisabled(true);
    NetworkManager::getInstance()->sendRegisterRequest(user);
}

void RegisterWidget::onBackLoginClicked()
{
    emit showLoginWidget();
    // 清空输入
    accountEdit->clear();
    usernameEdit->clear();
    passwordEdit->clear();
    phoneEdit->clear();
}

// 接收注册结果
void RegisterWidget::onRegisterResult(bool success, QString errMsg)
{
    registerBtn->setEnabled(true);
    if (success) {
        QMessageBox::information(this, "提示", errMsg);
        emit showLoginWidget(); // 注册成功返回登录页
        // 清空输入
        accountEdit->clear();
        usernameEdit->clear();
        passwordEdit->clear();
        phoneEdit->clear();
    } else {
        QMessageBox::warning(this, "提示", errMsg);
    }
}
