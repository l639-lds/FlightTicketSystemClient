#include "personal_center_widget.h"
#include <QSettings>
#include <QFile>
#include <QCalendarWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QGroupBox>
#include <QPainterPath>

PersonalCenterWidget::PersonalCenterWidget(QWidget *parent) : QWidget(parent)
{
    // 整体背景和滚动区域
    setStyleSheet("background-color: #F8FAFC;");

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; }");

    QWidget *container = new QWidget();
    container->setStyleSheet("background-color: #F8FAFC;");
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30, 20, 30, 20);
    containerLayout->setSpacing(25);

    // 初始化各个区域
    initAvatarSection();
    initPersonalInfoSection();
    initButtonSection();

    // 添加到容器布局
    containerLayout->addWidget(avatarSection);
    containerLayout->addWidget(infoGroup);
    containerLayout->addStretch();
    containerLayout->addWidget(buttonSection);

    scrollArea->setWidget(container);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(scrollArea);

    // 信号连接
    connect(backBtn, &QPushButton::clicked, this, &PersonalCenterWidget::onBackClicked);
    connect(saveBtn, &QPushButton::clicked, this, &PersonalCenterWidget::onSaveClicked);
    connect(logoutBtn, &QPushButton::clicked, this, &PersonalCenterWidget::onLogoutClicked);
    connect(NetworkManager::getInstance(), &NetworkManager::updateUserInfoResult, this, &PersonalCenterWidget::onUpdateResult);
}

PersonalCenterWidget::~PersonalCenterWidget() {}

void PersonalCenterWidget::initAvatarSection()
{
    avatarSection = new QWidget(this);
    avatarSection->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #0078D7, stop:1 #1E90FF); border-radius: 12px;");
    avatarSection->setFixedHeight(180);

    QHBoxLayout *avatarLayout = new QHBoxLayout(avatarSection);
    avatarLayout->setContentsMargins(40, 20, 40, 20);

    // 头像容器
    QWidget *avatarContainer = new QWidget();
    avatarContainer->setStyleSheet("background: transparent;");
    QVBoxLayout *avatarContainerLayout = new QVBoxLayout(avatarContainer);
    avatarContainerLayout->setAlignment(Qt::AlignCenter);
    avatarContainerLayout->setSpacing(10);

    // 圆形头像
    avatarLabel = new QLabel();
    avatarLabel->setFixedSize(100, 100);
    avatarLabel->setStyleSheet("background-color: #EEEEEE; border-radius: 50px; border: 3px solid white;");
    avatarLabel->setCursor(Qt::PointingHandCursor);
    avatarLabel->installEventFilter(this);

    // 头像提示文字
    avatarHintLabel = new QLabel("点击更换头像");
    avatarHintLabel->setStyleSheet("color: white; font-size: 13px; background: transparent;");
    avatarHintLabel->setAlignment(Qt::AlignCenter);

    avatarContainerLayout->addWidget(avatarLabel, 0, Qt::AlignCenter);
    avatarContainerLayout->addWidget(avatarHintLabel);

    // 用户名显示
    QWidget *userInfoContainer = new QWidget();
    userInfoContainer->setStyleSheet("background: transparent;");
    QVBoxLayout *userInfoLayout = new QVBoxLayout(userInfoContainer);
    userInfoLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    userInfoLayout->setSpacing(8);

    QLabel *welcomeLabel = new QLabel("个人信息");
    welcomeLabel->setStyleSheet("color: white; font-size: 24px; font-weight: bold; background: transparent;");

    QLabel *userNameLabel = new QLabel();
    userNameLabel->setStyleSheet("color: rgba(255,255,255,0.9); font-size: 16px; background: transparent;");
    userNameLabel->setObjectName("userNameDisplay");

    userInfoLayout->addWidget(welcomeLabel);
    userInfoLayout->addWidget(userNameLabel);
    userInfoLayout->addStretch();

    avatarLayout->addWidget(avatarContainer);
    avatarLayout->addSpacing(30);
    avatarLayout->addWidget(userInfoContainer);
    avatarLayout->addStretch();
}

void PersonalCenterWidget::initPersonalInfoSection()
{
    infoGroup = new QGroupBox("个人信息详情");
    infoGroup->setStyleSheet(R"(
        QGroupBox {
            background: white;
            border: 1px solid #E1E8ED;
            border-radius: 12px;
            margin-top: 10px;
            padding-top: 15px;
            font-weight: bold;
            color: #2C3E50;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 15px;
            padding: 0 10px 0 10px;
            background: white;
        }
    )");

    QGridLayout *infoLayout = new QGridLayout(infoGroup);
    infoLayout->setVerticalSpacing(20);
    infoLayout->setHorizontalSpacing(30);
    infoLayout->setContentsMargins(25, 25, 25, 25);

    // 账号信息
    QLabel *accountTitle = new QLabel("账号：");
    accountTitle->setStyleSheet("font-weight: bold; color: #555; font-size: 14px;");
    accountLabel = new QLabel();
    accountLabel->setStyleSheet("color: #333; font-size: 14px; padding: 8px 0;");
    infoLayout->addWidget(accountTitle, 1, 0, Qt::AlignRight);
    infoLayout->addWidget(accountLabel, 1, 1, Qt::AlignLeft);

    // 用户名
    QLabel *usernameTitle = new QLabel("用户名：");
    usernameTitle->setStyleSheet("font-weight: bold; color: #555; font-size: 14px;");
    usernameLabel = new QLabel();
    usernameLabel->setStyleSheet("color: #333; font-size: 14px; padding: 8px 0;");
    infoLayout->addWidget(usernameTitle, 0, 0, Qt::AlignRight);
    infoLayout->addWidget(usernameLabel, 0, 1, Qt::AlignLeft);

    // 手机号
    QLabel *phoneTitle = new QLabel("手机号：");
    phoneTitle->setStyleSheet("font-weight: bold; color: #555; font-size: 14px;");
    phoneLabel = new QLabel();
    phoneLabel->setStyleSheet("color: #333; font-size: 14px; padding: 8px 0;");
    infoLayout->addWidget(phoneTitle, 2, 0, Qt::AlignRight);
    infoLayout->addWidget(phoneLabel, 2, 1, Qt::AlignLeft);

    // 证件类型
    QLabel *idTypeTitle = new QLabel("证件类型：");
    idTypeTitle->setStyleSheet("font-weight: bold; color: #555; font-size: 14px;");
    idTypeLabel = new QLabel();
    idTypeLabel->setStyleSheet("color: #333; font-size: 14px; padding: 8px 0;");
    infoLayout->addWidget(idTypeTitle, 2, 2, Qt::AlignRight);
    infoLayout->addWidget(idTypeLabel, 2, 3, Qt::AlignLeft);

    // 证件号
    QLabel *idNumberTitle = new QLabel("证件号：");
    idNumberTitle->setStyleSheet("font-weight: bold; color: #555; font-size: 14px;");
    idNumberLabel = new QLabel();
    idNumberLabel->setStyleSheet("color: #333; font-size: 14px; padding: 8px 0;");
    infoLayout->addWidget(idNumberTitle, 3, 0, Qt::AlignRight);
    infoLayout->addWidget(idNumberLabel, 3, 1, Qt::AlignLeft);

    // 性别
    QLabel *genderTitle = new QLabel("性别：");
    genderTitle->setStyleSheet("font-weight: bold; color: #555; font-size: 14px;");
    genderCombo = new QComboBox();
    genderCombo->addItems({"男", "女"});
    genderCombo->setStyleSheet(R"(
        QComboBox {
            padding: 8px 12px;
            border: 1px solid #DCDFE6;
            border-radius: 6px;
            background: white;
            min-width: 120px;
            color: #333;
        }
        QComboBox::drop-down {
            subcontrol-origin: padding;
            subcontrol-position: top right;
            width: 20px;
            border-left: 1px solid #DCDFE6;
        }
        QComboBox QAbstractItemView {
            background: white;
            border: 1px solid #DCDFE6;
            color: #333;
        }
    )");
    infoLayout->addWidget(genderTitle, 0, 2, Qt::AlignRight);
    infoLayout->addWidget(genderCombo, 0, 3, Qt::AlignLeft);

    // 生日 - 修复显示问题
    QLabel *birthTitle = new QLabel("生日：");
    birthTitle->setStyleSheet("font-weight: bold; color: #555; font-size: 14px;");
    birthDateEdit = new QDateEdit();
    birthDateEdit->setDisplayFormat("yyyy年MM月dd日");
    birthDateEdit->setCalendarPopup(true);
    birthDateEdit->setStyleSheet(R"(
        QDateEdit {
            padding: 8px 12px;
            border: 1px solid #DCDFE6;
            border-radius: 6px;
            background: white;
            min-width: 150px;
            color: #333;
        }
        QDateEdit::drop-down {
            subcontrol-origin: padding;
            subcontrol-position: top right;
            width: 20px;
            border-left: 1px solid #DCDFE6;
        }
        QCalendarWidget QWidget {
            alternate-background-color: #F5F7FA;
            background: white;
            color: #333;
        }
        QCalendarWidget QToolButton {
            background: #0078D7;
            color: white;
            border: none;
            border-radius: 4px;
            padding: 5px;
        }
        QCalendarWidget QMenu {
            background: white;
            color: #333;
        }
        QCalendarWidget QSpinBox {
            background: white;
            color: #333;
            padding: 5px;
        }
    )");
    infoLayout->addWidget(birthTitle, 1, 2, Qt::AlignRight);
    infoLayout->addWidget(birthDateEdit, 1, 3, Qt::AlignLeft);

    // 个性签名
    QLabel *signatureTitle = new QLabel("个性签名：");
    signatureTitle->setStyleSheet("font-weight: bold; color: #555; font-size: 14px;");
    signatureEdit = new QLineEdit();
    signatureEdit->setPlaceholderText("分享你的个性签名...");
    signatureEdit->setMaxLength(50);
    signatureEdit->setStyleSheet(R"(
        QLineEdit {
            padding: 8px 12px;
            border: 1px solid #DCDFE6;
            border-radius: 6px;
            background: white;
            color: #333;
        }
    )");
    infoLayout->addWidget(signatureTitle, 4, 0, Qt::AlignRight | Qt::AlignTop);
    infoLayout->addWidget(signatureEdit, 4, 1, 1, 3);
}

// 手机号脱敏：中间4位用*代替
QString PersonalCenterWidget::maskPhoneNumber(const QString &phone)
{
    if (phone.length() == 11) {
        return phone.left(3) + "****" + phone.right(4);
    }
    return phone;
}

// 证件号脱敏：保留前6位和后4位，中间用*代替
QString PersonalCenterWidget::maskIdNumber(const QString &idNumber)
{
    if (idNumber.length() >= 10) {
        return idNumber.left(6) + QString(idNumber.length() - 10, '*') + idNumber.right(4);
    }
    return idNumber;
}

void PersonalCenterWidget::initButtonSection()
{
    buttonSection = new QWidget();
    buttonSection->setStyleSheet("background: transparent;");
    QHBoxLayout *btnLayout = new QHBoxLayout(buttonSection);
    btnLayout->setSpacing(15);

    backBtn = new QPushButton("← 返回首页");
    backBtn->setStyleSheet(R"(
        QPushButton {
            background-color: white;
            color: #0078D7;
            border: 1px solid #0078D7;
            border-radius: 8px;
            padding: 10px 25px;
            font-size: 14px;
            font-weight: 500;
        }
        QPushButton:hover {
            background-color: #F0F7FF;
            border-color: #005A9E;
        }
    )");

    saveBtn = new QPushButton("保存修改");
    saveBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #0078D7;
            color: white;
            border: none;
            border-radius: 8px;
            padding: 10px 25px;
            font-size: 14px;
            font-weight: 500;
        }
        QPushButton:hover {
            background-color: #005A9E;
        }
        QPushButton:pressed {
            background-color: #004578;
        }
    )");

    logoutBtn = new QPushButton("退出登录");
    logoutBtn->setStyleSheet(R"(
        QPushButton {
            background-color: white;
            color: #D93025;
            border: 1px solid #D93025;
            border-radius: 8px;
            padding: 10px 25px;
            font-size: 14px;
            font-weight: 500;
        }
        QPushButton:hover {
            background-color: #FFF5F5;
            border-color: #C1351A;
        }
    )");

    btnLayout->addStretch();
    btnLayout->addWidget(backBtn);
    btnLayout->addWidget(saveBtn);
    btnLayout->addWidget(logoutBtn);
}

void PersonalCenterWidget::setUserInfo(UserInfo userInfo)
{
    currentUser = userInfo;

    // 加载头像
    QString avatarPath = NetworkManager::getInstance()->loadAvatarPath(userInfo.account);
    if (!avatarPath.isEmpty()) {
        currentUser.avatarPath = avatarPath;
        loadAvatarFromPath(avatarPath);
    } else {
        // 设置默认头像
        avatarLabel->setStyleSheet(avatarLabel->styleSheet() + " background-color: #E0E0E0;");
    }

    // 加载个性签名
    QString signature = NetworkManager::getInstance()->loadSignature(userInfo.account);
    signatureEdit->setText(signature.isEmpty() ? "这个人很懒，什么都没有写～" : signature);

    // 显示用户信息
    QLabel *userNameDisplay = avatarSection->findChild<QLabel*>("userNameDisplay");
    if (userNameDisplay) {
        userNameDisplay->setText(currentUser.username);
    }

    usernameLabel->setText(userInfo.username);
    accountLabel->setText(userInfo.account);
    phoneLabel->setText(maskPhoneNumber(userInfo.phone));
    idTypeLabel->setText(userInfo.idType);
    idNumberLabel->setText(maskIdNumber(userInfo.idNumber));
    genderCombo->setCurrentText(userInfo.gender);
    birthDateEdit->setDate(userInfo.birthDate);
}

QPixmap PersonalCenterWidget::createCircularPixmap(const QPixmap &source, int size)
{
    if (source.isNull()) {
        return QPixmap();
    }

    QPixmap scaledPixmap = source.scaled(size, size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPixmap circularPixmap(size, size);
    circularPixmap.fill(Qt::transparent);

    QPainter painter(&circularPixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addEllipse(0, 0, size, size);
    painter.setClipPath(path);

    painter.drawPixmap(0, 0, scaledPixmap);

    return circularPixmap;
}

void PersonalCenterWidget::loadAvatarFromPath(const QString &path)
{
    if (path.isEmpty() || !QFile::exists(path)) {
        return;
    }

    QPixmap pixmap(path);
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "错误", "无法加载头像图片");
        return;
    }

    QPixmap circularPixmap = createCircularPixmap(pixmap, 100);
    avatarLabel->setPixmap(circularPixmap);
}

void PersonalCenterWidget::onSaveClicked()
{
    QString newGender = genderCombo->currentText();
    QDate newBirth = birthDateEdit->date();
    QString newSign = signatureEdit->text().trimmed();

    NetworkManager::getInstance()->updateUserInfo(
        currentUser.account, newGender, newBirth,
        currentAvatarPath, newSign
        );
}

void PersonalCenterWidget::onAvatarClicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this, "选择头像", QDir::homePath(),
        "图片文件 (*.png *.jpg *.jpeg *.bmp);;所有文件 (*)"
        );
    if (!filePath.isEmpty()) {
        loadAvatarFromPath(filePath);
        currentAvatarPath = filePath;
    }
}

void PersonalCenterWidget::onBackClicked()
{
    emit backToFunctionSignal();
}

void PersonalCenterWidget::onLogoutClicked()
{
    if (QMessageBox::question(this, "确认退出",
                              "确定要退出登录吗？",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        emit logoutSignal();
    }
}

void PersonalCenterWidget::onUpdateResult(bool success)
{
    if (success) {
        QMessageBox::information(this, "成功", "个人信息已更新！");
        // 更新当前用户信息
        currentUser.gender = genderCombo->currentText();
        currentUser.birthDate = birthDateEdit->date();
        currentUser.signature = signatureEdit->text().trimmed();
        if (!currentAvatarPath.isEmpty()) {
            currentUser.avatarPath = currentAvatarPath;
        }
    } else {
        QMessageBox::warning(this, "错误", "更新失败，请重试！");
    }
}

bool PersonalCenterWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == avatarLabel && event->type() == QEvent::MouseButtonPress) {
        onAvatarClicked();
        return true;
    }
    return QWidget::eventFilter(watched, event);
}
