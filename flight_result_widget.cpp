#include "flight_result_widget.h"
#include <QMessageBox>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QDialog>
#include <QPointer>

FlightResultWidget::FlightResultWidget(QWidget *parent) :
    QWidget(parent)
{
    initUI();
}

FlightResultWidget::~FlightResultWidget(){
    // 断开所有网络连接
    disconnect(NetworkManager::getInstance(), nullptr, this, nullptr);
}

void FlightResultWidget::initUI()
{
    // 1. 设置整体样式
    setStyleSheet("background-color: #F8FAFC;");
    setMinimumSize(1200, 700);

    // 2. 创建返回按钮
    QPushButton *backBtn = new QPushButton("← 返回查询", this);
    backBtn->setStyleSheet(R"(
        QPushButton {
            background-color: white;
            color: #0078D7;
            border: 1px solid #0078D7;
            border-radius: 8px;
            padding: 8px 15px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #F0F7FF;
        }
    )");
    connect(backBtn, &QPushButton::clicked, this, &FlightResultWidget::onBackClicked);

    // 3. 创建搜索条件区域
    QWidget *searchSection = new QWidget(this);
    searchSection->setStyleSheet("background: white; border-radius: 8px; padding: 15px;");
    QHBoxLayout *searchLayout = new QHBoxLayout(searchSection);
    searchLayout->setContentsMargins(20, 10, 20, 10);

    // 修复：正确获取搜索条件标签
    QLabel *searchLabel = new QLabel("搜索条件：");
    searchLabel->setObjectName("searchConditionLabel");
    searchLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #333;");

    QLabel *dateLabel = new QLabel("出行日期：");
    dateLabel->setStyleSheet("font-size: 14px; color: #666;");

    dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setDisplayFormat("yyyy年MM月dd日");
    dateEdit->setCalendarPopup(true);
    dateEdit->setMinimumDate(QDate::currentDate());
    dateEdit->setMaximumDate(QDate::currentDate().addYears(1));
    dateEdit->setStyleSheet(R"(
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
    )");

    //日期变化时触发新查询 - 修复连接问题
    connect(dateEdit, &QDateEdit::dateChanged, this, [=](const QDate &newDate) {
        qDebug() << "日期变化：" << newDate.toString("yyyy-MM-dd");
        // 1. 更新当前查询日期
        travelDate = newDate;
        // 2. 显示加载提示
        flightTable->setRowCount(0);
        int row = flightTable->rowCount();
        flightTable->insertRow(row);
        QTableWidgetItem *loadingItem = new QTableWidgetItem("正在查询航班...");
        loadingItem->setFlags(loadingItem->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
        loadingItem->setTextAlignment(Qt::AlignCenter);
        loadingItem->setForeground(QBrush(QColor("#0078D7")));
        loadingItem->setFont(QFont("Microsoft YaHei", 11, QFont::Bold));
        flightTable->setItem(row, 0, loadingItem);
        flightTable->setSpan(row, 0, 1, 8);
        flightTable->setRowHeight(row, 60);

        // 3. 发起新的航班查询（使用最新的出发地、目的地、新日期）
        if (!fromCity.isEmpty() && !toCity.isEmpty()) {
            qDebug() << "发起查询: " << fromCity << "->" << toCity << "日期:" << newDate.toString("yyyy-MM-dd");
            NetworkManager::getInstance()->searchFlights(fromCity, toCity, newDate);
        } else {
            qDebug() << "出发地或目的地为空，无法查询";
            // 如果没有城市信息，显示错误提示
            flightTable->setRowCount(0);
            int errorRow = flightTable->rowCount();
            flightTable->insertRow(errorRow);
            QTableWidgetItem *errorItem = new QTableWidgetItem("查询参数错误，请返回重新选择出发地和目的地");
            errorItem->setFlags(errorItem->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
            errorItem->setTextAlignment(Qt::AlignCenter);
            errorItem->setForeground(QBrush(QColor("#E74C3C")));
            flightTable->setItem(errorRow, 0, errorItem);
            flightTable->setSpan(errorRow, 0, 1, 8);
        }
    });

    QLabel *passengerLabel = new QLabel("乘客类型：");
    passengerLabel->setStyleSheet("font-size: 14px; color: #666;");

    passengerTypeCombo = new QComboBox();
    passengerTypeCombo->addItems({"成人", "儿童", "学生"});
    passengerTypeCombo->setStyleSheet(R"(
        QComboBox {
            padding: 8px 12px;
            border: 1px solid #DCDFE6;
            border-radius: 6px;
            background: white;
            min-width: 100px;
            color: #333;
        }
    )");

    searchLayout->addWidget(searchLabel);
    searchLayout->addStretch();
    searchLayout->addWidget(dateLabel);
    searchLayout->addWidget(dateEdit);
    searchLayout->addSpacing(20);
    searchLayout->addWidget(passengerLabel);
    searchLayout->addWidget(passengerTypeCombo);

    // 4. 创建航班表格
    flightTable = new QTableWidget(this);
    flightTable->setColumnCount(8);
    flightTable->setHorizontalHeaderLabels({
        "航班号", "出发地", "目的地", "出发时间",
        "到达时间", "时长", "价格", "操作"
    });

    // 设置列宽
    flightTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    flightTable->setColumnWidth(0, 150);
    flightTable->setColumnWidth(1, 120);
    flightTable->setColumnWidth(2, 120);
    flightTable->setColumnWidth(3, 120);
    flightTable->setColumnWidth(4, 120);
    flightTable->setColumnWidth(5, 150);
    flightTable->setColumnWidth(6, 150);
    flightTable->setColumnWidth(7, 150);

    // 设置表格属性
    flightTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    flightTable->setSelectionMode(QAbstractItemView::NoSelection);
    flightTable->setFocusPolicy(Qt::NoFocus);
    flightTable->setAlternatingRowColors(true);

    flightTable->setStyleSheet(R"(
        QTableWidget {
            background-color: white;
            border: 1px solid #E1E8ED;
            border-radius: 8px;
            padding: 5px;
            gridline-color: #E1E8ED;
        }
        QHeaderView::section {
            background-color: #F0F7FF;
            padding: 12px 8px;
            border: 1px solid #E1E8ED;
            font-weight: bold;
            color: #333;
        }
        QTableWidget::item {
            border: 1px solid #E1E8ED;
            padding: 8px;
            color: #333;
        }
        QTableWidget::item:alternate {
            background-color: #F8FAFC;
        }
        QTableWidget::item:hover {
            background-color: #F0F7FF;
        }
    )");

    // 5. 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 20, 30, 20);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(backBtn, 0, Qt::AlignLeft);
    mainLayout->addWidget(searchSection);
    mainLayout->addWidget(flightTable);
}

void FlightResultWidget::setSearchConditions(const QString &from, const QString &to, const QDate &date)
{
    fromCity = from;
    toCity = to;
    travelDate = date;

    // 设置日期控件的初始值
    if (dateEdit) {
        dateEdit->setDate(date);
    }

    // 修复：正确更新搜索条件标签文本
    // 使用对象名或直接访问标签
    QLabel *searchLabel = findChild<QLabel*>("searchConditionLabel");
    if (searchLabel) {
        searchLabel->setText(QString("搜索条件：从 %1 到 %2").arg(from).arg(to));
    }

    setWindowTitle(QString("从 %1 到 %2 的航班").arg(from).arg(to));
}

void FlightResultWidget::updateFlightList(const QList<FlightInfo> &flights)
{
    currentFlights = flights;

    // 先清除所有行（包括可能存在的加载提示）
    flightTable->setRowCount(0);

    qDebug() << "更新航班列表，找到" << flights.size() << "个航班";

    // 如果有航班数据
    if (!flights.isEmpty()) {
        for (int i = 0; i < flights.size(); ++i) {
            const FlightInfo &flight = flights[i];

            int row = flightTable->rowCount();
            flightTable->insertRow(row);

            // 航班基本信息
            flightTable->setItem(row, 0, new QTableWidgetItem(flight.flightNumber));
            flightTable->setItem(row, 1, new QTableWidgetItem(flight.departureCity));
            flightTable->setItem(row, 2, new QTableWidgetItem(flight.arrivalCity));
            flightTable->setItem(row, 3, new QTableWidgetItem(flight.departureTime.toString("HH:mm")));
            flightTable->setItem(row, 4, new QTableWidgetItem(flight.arrivalTime.toString("HH:mm")));

            // 计算时长显示
            int hours = flight.duration / 60;
            int mins = flight.duration % 60;
            flightTable->setItem(row, 5, new QTableWidgetItem(QString("%1时%2分").arg(hours).arg(mins)));

            // 显示价格范围
            QString priceRange = QString("¥%1-¥%2")
                                     .arg(flight.economyPrice, 0, 'f', 0)
                                     .arg(flight.firstClassPrice, 0, 'f', 0);
            flightTable->setItem(row, 6, new QTableWidgetItem(priceRange));

            // 购票按钮
            QPushButton *bookBtn = new QPushButton("选择购票");
            bookBtn->setEnabled(flight.economySeats > 0 || flight.businessSeats > 0 || flight.firstClassSeats > 0);
            bookBtn->setStyleSheet(R"(
                QPushButton {
                    background-color: #0078D7;
                    color: white;
                    border: none;
                    border-radius: 4px;
                    padding: 8px 15px;
                    font-size: 12px;
                }
                QPushButton:hover {
                    background-color: #005A9E;
                }
                QPushButton:disabled {
                    background-color: #CCCCCC;
                    color: #666666;
                }
            )");

            bookBtn->setProperty("flightIndex", i);
            connect(bookBtn, &QPushButton::clicked, this, &FlightResultWidget::onBookClicked);

            flightTable->setCellWidget(row, 7, bookBtn);

            // 设置整行不可编辑和不可选择
            for (int col = 0; col < 7; ++col) {
                QTableWidgetItem *item = flightTable->item(row, col);
                if (item) {
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
                    item->setTextAlignment(Qt::AlignCenter);
                }
            }
        }

        // 调整行高
        for (int i = 0; i < flightTable->rowCount(); ++i) {
            flightTable->setRowHeight(i, 50);
        }
    } else {
        // 只有没有航班数据时才显示提示
        int row = flightTable->rowCount();
        flightTable->insertRow(row);
        QTableWidgetItem *emptyItem = new QTableWidgetItem(
            QString("未找到从 %1 到 %2 在 %3 的航班")
                .arg(fromCity)
                .arg(toCity)
                .arg(travelDate.toString("yyyy年MM月dd日"))
            );
        emptyItem->setFlags(emptyItem->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
        emptyItem->setTextAlignment(Qt::AlignCenter);
        emptyItem->setForeground(QBrush(QColor("#666666")));
        emptyItem->setBackground(QBrush(QColor("#F8FAFC")));
        emptyItem->setFont(QFont("Microsoft YaHei", 11));
        flightTable->setItem(row, 0, emptyItem);
        flightTable->setSpan(row, 0, 1, 8); // 跨8列显示
        flightTable->setRowHeight(row, 60);

        // 禁用所有操作列
        for (int col = 0; col < 8; ++col) {
            QTableWidgetItem *item = flightTable->item(row, col);
            if (!item && col > 0) {
                item = new QTableWidgetItem();
                flightTable->setItem(row, col, item);
            }
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
            }
        }
    }
}


void FlightResultWidget::onBookClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        int flightIndex = btn->property("flightIndex").toInt();
        QString passengerType = passengerTypeCombo->currentText();

        if (flightIndex >= 0 && flightIndex < currentFlights.size()) {
            const FlightInfo &flight = currentFlights[flightIndex];

            // 创建舱位类型选择对话框
            QDialog seatDialog(this);
            seatDialog.setWindowTitle("选择舱位类型");
            seatDialog.setFixedSize(450, 350);
            seatDialog.setStyleSheet(R"(
                QDialog {
                    background-color: white;
                    border-radius: 10px;
                }
            )");

            QVBoxLayout *dialogLayout = new QVBoxLayout(&seatDialog);
            dialogLayout->setContentsMargins(20, 20, 20, 20);
            dialogLayout->setSpacing(15);

            // 标题
            QLabel *titleLabel = new QLabel(QString("为 %1 航班选择舱位").arg(flight.flightNumber));
            titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #333; margin-bottom: 10px;");
            titleLabel->setAlignment(Qt::AlignCenter);

            // 显示乘客类型
            QLabel *passengerInfoLabel = new QLabel(QString("乘客类型：%1").arg(passengerType));
            passengerInfoLabel->setStyleSheet("font-size: 14px; color: #666;");
            passengerInfoLabel->setAlignment(Qt::AlignCenter);

            // 舱位类型选择
            QButtonGroup *seatGroup = new QButtonGroup(&seatDialog);
            seatGroup->setExclusive(true);

            // 存储选择数量的变量
            int economyCount = 1, businessCount = 1, firstClassCount = 1;

            // 创建舱位选项
            // 创建舱位选项（修改 createSeatOption 函数）
            QWidget *economyWidget = createSeatOption("经济舱", flight.economyPrice, flight.economySeats, passengerType, seatGroup);
            QWidget *businessWidget = createSeatOption("商务舱", flight.businessPrice, flight.businessSeats, passengerType, seatGroup);
            QWidget *firstClassWidget = createSeatOption("头等舱", flight.firstClassPrice, flight.firstClassSeats, passengerType,seatGroup);

            // 布局数量选择
            dialogLayout->addWidget(titleLabel);
            dialogLayout->addWidget(passengerInfoLabel);
            dialogLayout->addSpacing(10);
            dialogLayout->addWidget(economyWidget);
            dialogLayout->addWidget(businessWidget);
            dialogLayout->addWidget(firstClassWidget);
            dialogLayout->addStretch();

            // 确认按钮
            QPushButton *confirmBtn = new QPushButton("确认购票");
            confirmBtn->setEnabled(false);
            confirmBtn->setStyleSheet(R"(
                QPushButton {
                    background-color: #0078D7;
                    color: white;
                    border: none;
                    border-radius: 6px;
                    padding: 12px 25px;
                    font-size: 14px;
                    font-weight: bold;
                    min-width: 120px;
                }
                QPushButton:hover {
                    background-color: #005A9E;
                }
                QPushButton:disabled {
                    background-color: #CCCCCC;
                }
            )");

            // 按钮布局
            QHBoxLayout *buttonLayout = new QHBoxLayout();
            buttonLayout->addStretch();
            buttonLayout->addWidget(confirmBtn);
            buttonLayout->addStretch();

            dialogLayout->addLayout(buttonLayout);

            // 存储用户选择的变量
            QString selectedSeatClass;

            // 当选择舱位时，启用确认按钮
            connect(seatGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
                    this, [&](QAbstractButton *button) {
                        selectedSeatClass = button->property("seatClass").toString();
                        confirmBtn->setEnabled(true);
                    });

            // 连接确认按钮
            connect(confirmBtn, &QPushButton::clicked, &seatDialog, [&]() {
                QAbstractButton *selectedSeat = seatGroup->checkedButton();
                if (selectedSeat) {
                    selectedSeatClass = selectedSeat->property("seatClass").toString();

                    // 检查余票
                    int availableSeats = 0;
                    if (selectedSeatClass == "经济舱") availableSeats = flight.economySeats;
                    else if (selectedSeatClass == "商务舱") availableSeats = flight.businessSeats;
                    else if (selectedSeatClass == "头等舱") availableSeats = flight.firstClassSeats;

                    if (availableSeats <= 0) {
                        QMessageBox::warning(&seatDialog, "提示", "该舱位已无余票");
                        return;
                    }

                    seatDialog.accept();
                } else {
                    QMessageBox::warning(&seatDialog, "提示", "请选择舱位类型");
                }
            });

            // 显示对话框
            if (seatDialog.exec() == QDialog::Accepted && !selectedSeatClass.isEmpty()) {
                qDebug() << "用户选择: 舱位=" << selectedSeatClass << "乘客类型=" << passengerType;

                // 发出信号，票数固定为1
                emit bookTicketSignal(flight, selectedSeatClass, passengerType, 1);
            }
        }
    }
}

QWidget* FlightResultWidget::createSeatOption(const QString &seatClass, double price,
                                              int seats, const QString &passengerType,
                                              QButtonGroup *buttonGroup)
{
    QWidget *widget = new QWidget();
    widget->setFixedHeight(60);
    widget->setMinimumWidth(350);
    widget->setStyleSheet(R"(
        QWidget {
            border: 2px solid #E1E8ED;
            border-radius: 8px;
            margin: 5px;
            background-color: #FAFBFC;
        }
        QWidget:hover {
            border-color: #0078D7;
            background-color: #F0F7FF;
        }
    )");

    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setContentsMargins(15, 10, 15, 10);
    layout->setSpacing(15);

    QRadioButton *radioBtn = new QRadioButton();
    radioBtn->setProperty("seatClass", seatClass);
    radioBtn->setEnabled(seats > 0);
    radioBtn->setFixedSize(24, 24);
    buttonGroup->addButton(radioBtn);

    QLabel *seatLabel = new QLabel(seatClass);
    seatLabel->setStyleSheet("font-weight: bold; color: #333; font-size: 14px; min-width: 60px;");

    // 计算最终价格
    double finalPrice = price;
    if (passengerType == "儿童") {
        finalPrice *= 0.5;
    } else if (passengerType == "学生") {
        finalPrice *= 0.8;
    }

    QLabel *priceLabel = new QLabel(QString("¥%1").arg(finalPrice, 0, 'f', 2));
    priceLabel->setStyleSheet("color: #E74C3C; font-weight: bold; font-size: 14px; min-width: 80px;");

    QLabel *seatInfoLabel = new QLabel(QString("余票: %1张").arg(seats));
    if (seats > 0) {
        seatInfoLabel->setStyleSheet("color: #27AE60; font-size: 12px;");
    } else {
        seatInfoLabel->setStyleSheet("color: #E74C3C; font-size: 12px;");
    }

    layout->addWidget(radioBtn);
    layout->addWidget(seatLabel);
    layout->addStretch();
    layout->addWidget(priceLabel);
    layout->addSpacing(10);
    layout->addWidget(seatInfoLabel);
    layout->addSpacing(10);

    return widget;
}

void FlightResultWidget::onBackClicked()
{
    emit backToSearchSignal();
}
