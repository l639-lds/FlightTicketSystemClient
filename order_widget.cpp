#include "order_widget.h"
#include <QTimer>
#include <QGroupBox>
#include <QGridLayout>
#include <QRandomGenerator>

OrderWidget::OrderWidget(QWidget *parent)
    : QWidget(parent)
{
    initUI();

    // 连接信号
    connect(NetworkManager::getInstance(), &NetworkManager::orderListResult,
            this, &OrderWidget::onOrderListResult);
    connect(NetworkManager::getInstance(), &NetworkManager::cancelOrderResult,
            this, &OrderWidget::onCancelOrderResult);
    connect(NetworkManager::getInstance(), &NetworkManager::changeOrderResult,
            this, &OrderWidget::onChangeOrderResult);
}

void OrderWidget::initUI()
{
    setStyleSheet("background-color: #F8FAFC;");
    setMinimumSize(1200, 700);

    // 主容器
    QWidget *mainContainer = new QWidget(this);
    mainContainer->setStyleSheet("background: white; border-radius: 10px; margin: 0px;");

    QVBoxLayout *containerLayout = new QVBoxLayout(mainContainer);
    containerLayout->setContentsMargins(20, 20, 20, 20);
    containerLayout->setSpacing(15);

    // 顶部标题区域
    QWidget *topWidget = new QWidget();
    topWidget->setStyleSheet("background: transparent;");
    QHBoxLayout *topLayout = new QHBoxLayout(topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *iconLabel = new QLabel("📋");
    iconLabel->setStyleSheet("font-size: 24px;");

    titleLabel = new QLabel("我的订单");
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #1A237E;");

    topLayout->addWidget(iconLabel);
    topLayout->addWidget(titleLabel);
    topLayout->addStretch();

    // 按钮区域
    QWidget *buttonWidget = new QWidget();
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->setSpacing(10);

    refreshBtn = new QPushButton("🔄 刷新");
    refreshBtn->setFixedSize(120, 50);
    refreshBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 4px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #45a049;
        }
    )");

    backBtn = new QPushButton("← 返回");
    backBtn->setFixedSize(120,50);
    backBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #f8f9fa;
            color: #333;
            border: 1px solid #dee2e6;
            border-radius: 4px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #e9ecef;
            border-color: #adb5bd;
        }
    )");

    buttonLayout->addStretch();
    buttonLayout->addWidget(refreshBtn);
    buttonLayout->addWidget(backBtn);

    topLayout->addWidget(buttonWidget);

    // 订单表格
    orderTable = new QTableWidget();
    orderTable->setColumnCount(10);
    QStringList headers = {
        "航班号", "行程", "出发时间", "行程时间","舱位类型",
        "乘客类型", "价格", "状态", "下单时间", "操作"
    };
    orderTable->setHorizontalHeaderLabels(headers);

    // 设置表格属性
    orderTable->horizontalHeader()->setVisible(true);
    orderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    orderTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    orderTable->setAlternatingRowColors(true);
    orderTable->setShowGrid(true);
    orderTable->verticalHeader()->setVisible(false);

    // 设置列宽
    QHeaderView *header = orderTable->horizontalHeader();
    header->setFixedHeight(65);
    header->setStretchLastSection(false);
    header->setSectionResizeMode(QHeaderView::Interactive);
    orderTable->setColumnWidth(0, 100);  // 航班号
    orderTable->setColumnWidth(1, 120);  // 行程
    orderTable->setColumnWidth(2, 120);  // 出发时间
    orderTable->setColumnWidth(3, 80);  // 行程时间
    orderTable->setColumnWidth(4, 80);   // 舱位类型
    orderTable->setColumnWidth(5, 80);   // 乘客类型
    orderTable->setColumnWidth(6, 90);  // 价格
    orderTable->setColumnWidth(7, 80);   // 状态
    orderTable->setColumnWidth(8, 150);  // 下单时间
    orderTable->setColumnWidth(9, 150);  // 操作

    // 表格样式
    orderTable->setStyleSheet(R"(
        QTableWidget {
            border: 1px solid #e0e0e0;
            border-radius: 4px;
            background-color: white;
            gridline-color: #f0f0f0;
        }
        QHeaderView::section {
            background-color: #f8f9fa;
            padding: 12px 8px;
            border: 1px solid #e0e0e0;
            font-weight: bold;
            color: #333;
        }
        QTableWidget::item {
            padding: 0px;
            border: 1px solid #e0e0e0;
            border-bottom: 1px solid #f0f0f0;
        }
        QTableWidget::item:selected {
            background-color: #e3f2fd;
            color: #333;
        }
        QTableWidget::item:hover {
            background-color: #f5f5f5;
        }
    )");

    // 添加到容器
    containerLayout->addWidget(topWidget);
    containerLayout->addWidget(orderTable,1);

    // 设置主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(mainContainer);

    // 信号连接
    connect(backBtn, &QPushButton::clicked, this, &OrderWidget::onBackClicked);
    connect(refreshBtn, &QPushButton::clicked, this, &OrderWidget::onRefreshClicked);
    connect(NetworkManager::getInstance(), &NetworkManager::orderListResult, this, &OrderWidget::onOrderListResult);
}

void OrderWidget::setUserId(const QString &userId)
{
    currentUserId = userId;
    refreshOrders();
}

void OrderWidget::refreshOrders()
{
    if (!currentUserId.isEmpty()) {
        NetworkManager::getInstance()->getUserOrders(currentUserId);
        titleLabel->setText(QString("我的订单（用户：%1）").arg(currentUserId));
    }
}

void OrderWidget::updateOrderTable(const QList<OrderInfo> &orders)
{
    // 清空表格
    orderTable->setRowCount(0);
    currentOrders = orders;

    if (orders.isEmpty()) {
        // 如果没有订单，显示空提示
        QMessageBox::information(this, "提示", "暂无订单记录");
        return;
    }

    // 按创建时间降序排序
    QList<OrderInfo> sortedOrders = orders;
    std::sort(sortedOrders.begin(), sortedOrders.end(),
              [](const OrderInfo &a, const OrderInfo &b) {
                  return a.createTime > b.createTime;
              });

    for (int i = 0; i < sortedOrders.size(); ++i) {
        const OrderInfo &order = sortedOrders[i];

        int row = orderTable->rowCount();
        orderTable->insertRow(row);

        // 设置每列数据
        // 1. 订单号
        // QTableWidgetItem *orderIdItem = new QTableWidgetItem(order.orderId);
        // orderIdItem->setTextAlignment(Qt::AlignCenter);
        // orderTable->setItem(row, 0, orderIdItem);

        // 1. 航班号
        QTableWidgetItem *flightItem = new QTableWidgetItem(order.flightNumber);
        flightItem->setTextAlignment(Qt::AlignCenter);
        orderTable->setItem(row, 0, flightItem);

        // 2. 行程
        QString route = QString("%1 → %2").arg(order.departureCity).arg(order.arrivalCity);
        QTableWidgetItem *routeItem = new QTableWidgetItem(route);
        routeItem->setTextAlignment(Qt::AlignCenter);
        orderTable->setItem(row, 1, routeItem);

        // 3. 出发时间
        QString timeStr = QString("%1 %2").arg(order.date.toString("MM/dd")).arg(order.departureTime.toString("HH:mm"));
        QTableWidgetItem *timeItem = new QTableWidgetItem(timeStr);
        timeItem->setTextAlignment(Qt::AlignCenter);
        orderTable->setItem(row, 2, timeItem);

        // 4. 航班行驶时间
        QString durationStr;
        if (order.flightDuration > 0) {
            int hours = order.flightDuration / 60;
            int minutes = order.flightDuration % 60;
            if (hours > 0) {
                durationStr = QString("%1小时%2分钟").arg(hours).arg(minutes);
            } else {
                durationStr = QString("%1分钟").arg(minutes);
            }
        } else {
            durationStr = "未知";  // 如果flightDuration为0或未设置
        }
        QTableWidgetItem *durationItem = new QTableWidgetItem(durationStr);
        durationItem->setTextAlignment(Qt::AlignCenter);
        orderTable->setItem(row, 3, durationItem);

        // 5. 舱位类型
        QTableWidgetItem *seatItem = new QTableWidgetItem(order.seatClass);
        seatItem->setTextAlignment(Qt::AlignCenter);
        seatItem->setForeground(QColor(getSeatClassColor(order.seatClass)));
        orderTable->setItem(row, 4, seatItem);

        // 6. 乘客类型
        QTableWidgetItem *passengerItem = new QTableWidgetItem(order.passengerType);
        passengerItem->setTextAlignment(Qt::AlignCenter);
        orderTable->setItem(row, 5, passengerItem);

        // 7. 价格
        QTableWidgetItem *priceItem = new QTableWidgetItem(QString("¥%1").arg(order.price, 0, 'f', 2));
        priceItem->setTextAlignment(Qt::AlignCenter);
        orderTable->setItem(row, 6, priceItem);

        // 8. 状态
        QTableWidgetItem *statusItem = new QTableWidgetItem(order.status);
        statusItem->setTextAlignment(Qt::AlignCenter);
        statusItem->setForeground(QColor(getStatusColor(order.status)));
        orderTable->setItem(row, 7, statusItem);

        // 9. 下单时间
        QTableWidgetItem *createTimeItem = new QTableWidgetItem(order.createTime.toString("yyyy-MM-dd HH:mm"));
        createTimeItem->setTextAlignment(Qt::AlignCenter);
        orderTable->setItem(row, 8, createTimeItem);

        // 10. 操作按钮
        QWidget *buttonWidget = new QWidget();

        // 取消按钮
        QPushButton *cancelBtn = new QPushButton("取消");
        cancelBtn->setFixedHeight(40); // 只设置高度，宽度自动适应
        cancelBtn->setMinimumWidth(60); // 设置最小宽度
        cancelBtn->setProperty("orderId", order.orderId);
        cancelBtn->setProperty("row", row); // 添加这行，设置行属性
        cancelBtn->setEnabled(order.status == "已支付" && order.remainingTime > 0);
        cancelBtn->setStyleSheet(R"(
            QPushButton {
                background-color: #ff6b6b;
                color: white;
                border: none;
                border-radius: 4px;
                font-size: 12px;
                padding: 6px 8px;
                margin: 2px;
            }
            QPushButton:hover {
                background-color: #ff5252;
            }
            QPushButton:disabled {
                background-color: #cccccc;
                color: #666666;
            }
        )");
        connect(cancelBtn, &QPushButton::clicked, this, &OrderWidget::onCancelClicked);

        // 改签按钮
        QPushButton *changeBtn = new QPushButton("改签");
        changeBtn->setFixedHeight(40); // 只设置高度，宽度自动适应
        changeBtn->setMinimumWidth(60); // 设置最小宽度
        changeBtn->setProperty("orderId", order.orderId);
        changeBtn->setProperty("row", row); // 添加这行，设置行属性
        changeBtn->setEnabled(order.status == "已支付");
        changeBtn->setStyleSheet(R"(
            QPushButton {
                background-color: #4ecdc4;
                color: white;
                border: none;
                border-radius: 4px;
                font-size: 12px;
                padding: 6px 8px;
                margin: 2px;
            }
            QPushButton:hover {
                background-color: #3dbbb3;
            }
            QPushButton:disabled {
                background-color: #cccccc;
                color: #666666;
            }
        )");
        connect(changeBtn, &QPushButton::clicked, this, &OrderWidget::onChangeClicked);

        QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);
        buttonLayout->setContentsMargins(2, 5, 2, 5);
        buttonLayout->setSpacing(5);
        buttonLayout->setAlignment(Qt::AlignCenter);
        buttonLayout->addWidget(cancelBtn);
        buttonLayout->addWidget(changeBtn);

        orderTable->setCellWidget(row, 9, buttonWidget);

        // 设置行高
        orderTable->setRowHeight(row, 65);
    }

    // 刷新表格显示
    orderTable->viewport()->update();
}

QString OrderWidget::getStatusColor(const QString &status)
{
    if (status == "已支付") return "#27AE60";
    if (status == "已取消") return "#E74C3C";
    if (status == "已改签") return "#3498DB";
    if (status == "已完成") return "#9B59B6";
    return "#333333";
}

QString OrderWidget::getSeatClassColor(const QString &seatClass)
{
    if (seatClass == "头等舱") return "#E74C3C";
    if (seatClass == "商务舱") return "#3498DB";
    if (seatClass == "经济舱") return "#27AE60";
    return "#333333";
}

void OrderWidget::onBackClicked()
{
    emit backToFunctionSignal();
}

void OrderWidget::onRefreshClicked()
{
    refreshOrders();
    QMessageBox::information(this, "提示", "订单列表已刷新");
}

void OrderWidget::onCancelClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        QString orderId = btn->property("orderId").toString();
        int row = btn->property("row").toInt();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认取消",QString("确定要取消订单 %1 吗？").arg(orderId),QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            NetworkManager::getInstance()->cancelOrder(orderId);
        }
    }
}

void OrderWidget::onChangeClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        QString orderId = btn->property("orderId").toString();
        showChangeFlightDialog(orderId);
    }
}

void OrderWidget::showChangeFlightDialog(const QString &orderId)
{
    // 查找订单
    OrderInfo *targetOrder = nullptr;
    for (int i = 0; i < currentOrders.size(); ++i) {
        if (currentOrders[i].orderId == orderId) {
            targetOrder = &currentOrders[i];
            break;
        }
    }

    if (!targetOrder) {
        QMessageBox::warning(this, "错误", "订单信息无效");
        return;
    }

    // 创建改签对话框
    QDialog dialog(this);
    dialog.setWindowTitle(QString("改签订单 %1").arg(orderId));
    dialog.setFixedSize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    // 原订单信息
    QGroupBox *originalGroup = new QGroupBox("原订单信息");
    originalGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
    QGridLayout *originalLayout = new QGridLayout(originalGroup);

    originalLayout->addWidget(new QLabel("航班号:"), 0, 0);
    originalLayout->addWidget(new QLabel(targetOrder->flightNumber), 0, 1);
    originalLayout->addWidget(new QLabel("行程:"), 1, 0);
    originalLayout->addWidget(new QLabel(QString("%1 → %2").arg(targetOrder->departureCity).arg(targetOrder->arrivalCity)), 1, 1);
    originalLayout->addWidget(new QLabel("出发时间:"), 2, 0);
    originalLayout->addWidget(new QLabel(targetOrder->date.toString("yyyy年MM月dd日") + " " + targetOrder->departureTime.toString("HH:mm")), 2, 1);
    originalLayout->addWidget(new QLabel("舱位类型:"), 3, 0);
    originalLayout->addWidget(new QLabel(targetOrder->seatClass), 3, 1);

    layout->addWidget(originalGroup);

    // TODO: 这里可以添加选择新航班的界面
    // 由于时间关系，这里简化为直接选择新舱位

    QLabel *noticeLabel = new QLabel("改签功能开发中，请稍后...");
    noticeLabel->setStyleSheet("font-size: 16px; color: #E74C3C; font-weight: bold;");
    noticeLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(noticeLabel);
    layout->addStretch();

    // 按钮
    QPushButton *confirmBtn = new QPushButton("确认改签");
    QPushButton *cancelBtn = new QPushButton("取消");

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(confirmBtn);
    buttonLayout->addWidget(cancelBtn);

    layout->addLayout(buttonLayout);

    connect(confirmBtn, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "提示", "改签功能开发中，敬请期待！");
    }
}

void OrderWidget::onOrderListResult(const QList<OrderInfo> &orders)
{
    updateOrderTable(orders);
}

void OrderWidget::onCancelOrderResult(bool success, QString errMsg)
{
    if (success) {
        QMessageBox::information(this, "成功", errMsg);
        refreshOrders();
    } else {
        QMessageBox::warning(this, "失败", errMsg);
    }
}

void OrderWidget::onChangeOrderResult(bool success, QString errMsg, QString newOrderId)
{
    if (success) {
        QMessageBox::information(this, "成功", QString("%1\n新订单号：%2").arg(errMsg).arg(newOrderId));
        refreshOrders();
    } else {
        QMessageBox::warning(this, "失败", errMsg);
    }
}
