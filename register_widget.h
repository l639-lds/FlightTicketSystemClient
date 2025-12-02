#ifndef REGISTER_WIDGET_H
#define REGISTER_WIDGET_H
#include <QCalendarWidget>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QMessageBox>
#include <QComboBox>
#include <QDateEdit>
#include "network_manager.h"

class RegisterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterWidget(QWidget *parent = nullptr);

signals:
    void showLoginWidget();  // 返回登录页

private slots:
    void onRegisterClicked();  // 注册按钮点击
    void onBackLoginClicked(); // 返回登录按钮点击
    void onRegisterResult(bool success, QString errMsg); // 接收注册结果

private:
    QLineEdit *accountEdit;    // 账号输入框
    QLineEdit *usernameEdit;   // 用户名输入框
    QLineEdit *passwordEdit;   // 密码输入框
    QLineEdit *confirmPwdEdit; // 确认密码输入框（新增）
    QLineEdit *phoneEdit;      // 手机号输入框
    QComboBox *idTypeCombo;    // 证件类型选择框（新增）
    QLineEdit *idNumberEdit;   // 证件号输入框（新增）
    QComboBox *genderCombo;    // 性别选择框
    QDateEdit *birthDateEdit;  // 出生年月选择框
    QPushButton *registerBtn;
    QPushButton *backLoginBtn;
};

#endif // REGISTER_WIDGET_H
