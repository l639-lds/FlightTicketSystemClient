#ifndef LOGIN_WIDGET_H
#define LOGIN_WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QMessageBox>
#include "network_manager.h"

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);

signals:
    void loginSuccess(UserInfo userInfo);  // 登录成功，传递完整用户信息
    void showRegisterWidget();             // 跳转到注册页

private slots:
    void onLoginClicked();                 // 登录按钮点击
    void onRegisterClicked();              // 注册按钮点击
    void onLoginResult(bool success, UserInfo userInfo); // 接收登录结果

private:
    QLineEdit *accountOrUsernameEdit;  // 账号/用户名输入框
    QLineEdit *passwordEdit;           // 密码输入框
    QPushButton *loginBtn;
    QPushButton *registerBtn;
};

#endif // LOGIN_WIDGET_H
