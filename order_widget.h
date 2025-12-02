#ifndef ORDER_WIDGET_H
#define ORDER_WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QDateEdit>
#include <QDialog>
#include "network_manager.h"

class OrderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderWidget(QWidget *parent = nullptr);
    void setUserId(const QString &userId);
    void refreshOrders();

signals:
    void backToFunctionSignal();

private slots:
    void onBackClicked();
    void onRefreshClicked();
    void onCancelClicked();
    void onChangeClicked();
    void onOrderListResult(const QList<OrderInfo> &orders);
    void onCancelOrderResult(bool success, QString errMsg);
    void onChangeOrderResult(bool success, QString errMsg, QString newOrderId);
    void showChangeFlightDialog(const QString &orderId);

private:
    void initUI();
    void updateOrderTable(const QList<OrderInfo> &orders);
    QString getStatusColor(const QString &status);
    QString getSeatClassColor(const QString &seatClass);

    QTableWidget *orderTable;
    QPushButton *backBtn;
    QPushButton *refreshBtn;
    QLabel *titleLabel;

    QList<OrderInfo> currentOrders;
    QString currentUserId;
};

#endif // ORDER_WIDGET_H
