#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include "login_widget.h"
#include "register_widget.h"
#include "personal_center_widget.h"
#include "order_widget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginSuccess(UserInfo userInfo); // 登录成功
    void onLogout();                        // 退出登录
    void showLoginWidget();                 // 显示登录页
    void showRegisterWidget();              // 显示注册页
    void backToFunction();                  // 返回功能区
    void toPersonalCenter();                // 进入个人中心
    void showOrderWidget();              // 显示订单页

private:
    QLabel *userInfoLabel;
    PersonalCenterWidget *personalCenter;
    QWidget *functionWidget;
    LoginWidget *loginWidget;
    RegisterWidget *registerWidget;
    UserInfo currentUser; // 当前登录用户信息
    OrderWidget *orderWidget;            // 订单页面

    void initUI();
    void initFunctionWidget();
    QPushButton* createFunctionBtn(const QString &text, const QString &iconPath);
};

#endif // MAINWINDOW_H
