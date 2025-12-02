#ifndef PERSONAL_CENTER_WIDGET_H
#define PERSONAL_CENTER_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QDateEdit>
#include <QFileDialog>
#include <QPainter>
#include <QBitmap>
#include <QEvent>
#include <QDir>
#include <QLineEdit>
#include <QScrollArea>
#include <QGroupBox>
#include "network_manager.h"

class PersonalCenterWidget : public QWidget
{
    Q_OBJECT
public:
    PersonalCenterWidget(QWidget *parent = nullptr);
    ~PersonalCenterWidget();
    void setUserInfo(UserInfo userInfo);

signals:
    void logoutSignal();
    void backToFunctionSignal();

private slots:
    void onLogoutClicked();
    void onBackClicked();
    void onSaveClicked();
    void onUpdateResult(bool success);
    void onAvatarClicked();

private:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void loadAvatarFromPath(const QString &path);
    QPixmap createCircularPixmap(const QPixmap &source, int size);
    void initAvatarSection();
    void initPersonalInfoSection();
    void initButtonSection();
    QString maskPhoneNumber(const QString &phone);    // 手机号脱敏
    QString maskIdNumber(const QString &idNumber);    // 证件号脱敏

    // 头像区域
    QWidget *avatarSection;
    QLabel *avatarLabel;
    QLabel *avatarHintLabel;

    // 个人信息区域
    QGroupBox *infoGroup;
    QLabel *usernameLabel;
    QLabel *accountLabel;
    QLabel *phoneLabel;
    QLabel *idTypeLabel;
    QLabel *idNumberLabel;
    QComboBox *genderCombo;
    QDateEdit *birthDateEdit;
    QLineEdit *signatureEdit;

    // 按钮区域
    QWidget *buttonSection;
    QPushButton *logoutBtn;
    QPushButton *backBtn;
    QPushButton *saveBtn;

    UserInfo currentUser;
    QString currentAvatarPath;
};

#endif // PERSONAL_CENTER_WIDGET_H
