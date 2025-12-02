#include "change_flight_dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QHeaderView>
#include <QMessageBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QDialogButtonBox>

ChangeFlightDialog::ChangeFlightDialog(const OrderInfo &orderInfo, QWidget *parent)
    : QDialog(parent)
    , originalOrder(orderInfo)
    , selectedFlightIndex(-1)
{
    initUI();
    setupConnections();

    // 设置初始值
    fromEdit->setText(orderInfo.departureCity);
    toEdit->setText(orderInfo.arrivalCity);
    newDateEdit->setDate(QDate::currentDate().addDays(1));

    // 默认选择原舱位
    selectedSeatClass = orderInfo.seatClass;

    setWindowTitle(QString("改签订单 %1").arg(orderInfo.orderId));
    setFixedSize(900, 650);

    connect(NetworkManager::getInstance(), &NetworkManager::flightSearchResult,this, &ChangeFlightDialog::onFlightSearchResult, Qt::UniqueConnection);
}

ChangeFlightDialog::~ChangeFlightDialog()
{
}

void ChangeFlightDialog::initUI()
{
    setStyleSheet(R"(
        QDialog {
            background-color: #F8FAFC;
        }
    )");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);

    // === 原订单信息 ===
    QGroupBox *originalGroup = new QGroupBox("原订单信息");
    originalGroup->setStyleSheet(R"(
        QGroupBox {
            font-weight: bold;
            font-size: 14px;
            border: 2px solid #E1E8ED;
            border-radius: 8px;
            margin-top: 10px;
            padding-top: 15px;
            background: white;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 15px;
            padding: 0 10px;
            background: white;
            color: #2C3E50;
        }
    )");

    QGridLayout *originalLayout = new QGridLayout(originalGroup);
    originalLayout->setSpacing(10);
    originalLayout->setContentsMargins(15, 25, 15, 15);

    originalLayout->addWidget(new QLabel("航班号:"), 0, 0);
    originalLayout->addWidget(new QLabel(originalOrder.flightNumber), 0, 1);
    originalLayout->addWidget(new QLabel("行程:"), 0, 2);
    originalLayout->addWidget(new QLabel(QString("%1 → %2").arg(originalOrder.departureCity).arg(originalOrder.arrivalCity)), 0, 3);
    originalLayout->addWidget(new QLabel("出发时间:"), 1, 0);
    originalLayout->addWidget(new QLabel(originalOrder.date.toString("yyyy-MM-dd") + " " + originalOrder.departureTime.toString("HH:mm")), 1, 1);
    originalLayout->addWidget(new QLabel("舱位类型:"), 1, 2);
    originalLayout->addWidget(new QLabel(originalOrder.seatClass), 1, 3);
    originalLayout->addWidget(new QLabel("价格:"), 2, 0);
    originalLayout->addWidget(new QLabel(QString("¥%1").arg(originalOrder.price, 0, 'f', 2)), 2, 1);
    originalLayout->addWidget(new QLabel("状态:"), 2, 2);
    originalLayout->addWidget(new QLabel(originalOrder.status), 2, 3);

    mainLayout->addWidget(originalGroup);

    // === 新航班查询区域 ===
    QGroupBox *searchGroup = new QGroupBox("查询新航班");
    searchGroup->setStyleSheet(originalGroup->styleSheet());

    QGridLayout *searchLayout = new QGridLayout(searchGroup);
    searchLayout->setSpacing(10);
    searchLayout->setContentsMargins(15, 25, 15, 15);

    QLabel *fromLabel = new QLabel("出发地:");
    fromEdit = new QLineEdit();
    fromEdit->setReadOnly(true);
    fromEdit->setStyleSheet("background-color: #F5F7FA; color: #666;");

    QLabel *toLabel = new QLabel("目的地:");
    toEdit = new QLineEdit();
    toEdit->setReadOnly(true);
    toEdit->setStyleSheet("background-color: #F5F7FA; color: #666;");

    QLabel *dateLabel = new QLabel("新的出行日期:");
    newDateEdit = new QDateEdit();
    newDateEdit->setDisplayFormat("yyyy-MM-dd");
    newDateEdit->setCalendarPopup(true);
    newDateEdit->setMinimumDate(QDate::currentDate().addDays(1));
    newDateEdit->setMaximumDate(QDate::currentDate().addYears(1));
    newDateEdit->setStyleSheet(R"(
        QDateEdit {
            padding: 8px 12px;
            border: 1px solid #DCDFE6;
            border-radius: 6px;
            background: white;
        }
    )");

    searchBtn = new QPushButton("🔍 查询新航班");
    searchBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #0078D7;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 10px 20px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #005A9E;
        }
    )");

    searchLayout->addWidget(fromLabel, 0, 0);
    searchLayout->addWidget(fromEdit, 0, 1);
    searchLayout->addWidget(toLabel, 0, 2);
    searchLayout->addWidget(toEdit, 0, 3);
    searchLayout->addWidget(dateLabel, 1, 0);
    searchLayout->addWidget(newDateEdit, 1, 1);
    searchLayout->addWidget(searchBtn, 1, 3);

    mainLayout->addWidget(searchGroup);

    // === 新航班选择区域 ===
    QGroupBox *flightGroup = new QGroupBox("可选航班");
    flightGroup->setStyleSheet(originalGroup->styleSheet());

    QVBoxLayout *flightLayout = new QVBoxLayout(flightGroup);
    flightLayout->setContentsMargins(15, 25, 15, 15);

    flightTable = new QTableWidget();
    flightTable->setColumnCount(5);
    flightTable->setHorizontalHeaderLabels({"选择", "航班号", "出发时间", "到达时间", "时长"});
    flightTable->horizontalHeader()->setStretchLastSection(true);
    flightTable->verticalHeader()->setVisible(false);
    flightTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    flightTable->setSelectionMode(QAbstractItemView::SingleSelection);
    flightTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    flightTable->setStyleSheet(R"(
        QTableWidget {
            border: 1px solid #E1E8ED;
            border-radius: 4px;
            background-color: white;
            gridline-color: #E1E8ED;
        }
        QHeaderView::section {
            background-color: #F0F7FF;
            padding: 8px;
            border: 1px solid #E1E8ED;
            font-weight: bold;
            color: #333;
        }
        QTableWidget::item {
            padding: 8px;
        }
        QTableWidget::item:selected {
            background-color: #E3F2FD;
        }
    )");

    flightTable->setColumnWidth(0, 60);
    flightTable->setColumnWidth(1, 100);
    flightTable->setColumnWidth(2, 80);
    flightTable->setColumnWidth(3, 80);

    flightLayout->addWidget(flightTable);

    mainLayout->addWidget(flightGroup);

    // === 新舱位选择区域 ===
    // QGroupBox *seatGroup = new QGroupBox("选择新舱位");
    // seatGroup->setStyleSheet(originalGroup->styleSheet());

    // QHBoxLayout *seatLayout = new QHBoxLayout(seatGroup);
    // seatLayout->setContentsMargins(15, 25, 15, 15);
    // seatLayout->setSpacing(15);

    // seatButtonGroup = new QButtonGroup(this);
    // seatButtonGroup->setExclusive(true);

    // QStringList seatClasses = {"经济舱", "商务舱", "头等舱"};
    // foreach (const QString &seatClass, seatClasses) {
    //     QRadioButton *radioBtn = new QRadioButton(seatClass);
    //     radioBtn->setProperty("seatClass", seatClass);
    //     radioBtn->setStyleSheet(R"(
    //         QRadioButton {
    //             font-size: 13px;
    //             padding: 8px;
    //         }
    //         QRadioButton::indicator {
    //             width: 20px;
    //             height: 20px;
    //         }
    //     )");
    //     seatButtonGroup->addButton(radioBtn);
    //     seatLayout->addWidget(radioBtn);

    //     if (seatClass == originalOrder.seatClass) {
    //         radioBtn->setChecked(true);
    //     }
    // }
    // seatLayout->addStretch();

    // mainLayout->addWidget(seatGroup);

    // === 底部按钮 ===
    QDialogButtonBox *buttonBox = new QDialogButtonBox();
    confirmBtn = buttonBox->addButton("确认改签", QDialogButtonBox::AcceptRole);
    cancelBtn = buttonBox->addButton("取消", QDialogButtonBox::RejectRole);

    confirmBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 12px 30px;
            font-size: 14px;
            font-weight: bold;
            min-width: 120px;
        }
        QPushButton:hover {
            background-color: #45a049;
        }
        QPushButton:disabled {
            background-color: #cccccc;
            color: #666666;
        }
    )");

    cancelBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #f8f9fa;
            color: #333;
            border: 1px solid #dee2e6;
            border-radius: 6px;
            padding: 12px 30px;
            font-size: 14px;
            font-weight: bold;
            min-width: 120px;
        }
        QPushButton:hover {
            background-color: #e9ecef;
            border-color: #adb5bd;
        }
    )");

    confirmBtn->setEnabled(false); // 初始禁用

    mainLayout->addWidget(buttonBox);
}

void ChangeFlightDialog::setupConnections()
{
    connect(searchBtn, &QPushButton::clicked, this, &ChangeFlightDialog::onSearchClicked);
    connect(confirmBtn, &QPushButton::clicked, this, &ChangeFlightDialog::onConfirmClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    // connect(seatButtonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
    //         this, [=](QAbstractButton *button) {
    //             selectedSeatClass = button->property("seatClass").toString();
    //             enableConfirmButton();
    //         });
}

void ChangeFlightDialog::onSearchClicked()
{
    QString from = originalOrder.departureCity;
    QString to = originalOrder.arrivalCity;
    QDate newDate = newDateEdit->date();

    if (newDate < QDate::currentDate()) {
        QMessageBox::warning(this, "提示", "出发日期不能早于今天");
        return;
    }

    // 清空表格
    flightTable->setRowCount(0);
    clearFlightSelection();
    confirmBtn->setEnabled(false);

    // 显示加载提示
    int row = flightTable->rowCount();
    flightTable->insertRow(row);
    QTableWidgetItem *loadingItem = new QTableWidgetItem("正在查询航班...");
    loadingItem->setFlags(loadingItem->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
    loadingItem->setTextAlignment(Qt::AlignCenter);
    flightTable->setItem(row, 0, loadingItem);
    flightTable->setSpan(row, 0, 1, 5);
    flightTable->setRowHeight(row, 50);

    disconnect(NetworkManager::getInstance(), &NetworkManager::flightSearchResult,this, &ChangeFlightDialog::onFlightSearchResult);
    connect(NetworkManager::getInstance(), &NetworkManager::flightSearchResult,this, &ChangeFlightDialog::onFlightSearchResult, Qt::UniqueConnection);

    // 发起查询 - 确保参数正确
    qDebug() << "发起改签查询：" << from << "->" << to << "日期:" << newDate.toString("yyyy-MM-dd");
    NetworkManager::getInstance()->searchFlights(from, to, newDate);
}

void ChangeFlightDialog::onFlightSearchResult(const QList<FlightInfo> &flights)
{
    availableFlights = flights;
    updateFlightTable(flights);
}

void ChangeFlightDialog::updateFlightTable(const QList<FlightInfo> &flights)
{
    flightTable->setRowCount(0);

    if (flights.isEmpty()) {
        int row = flightTable->rowCount();
        flightTable->insertRow(row);
        QTableWidgetItem *emptyItem = new QTableWidgetItem("未找到符合条件的航班");
        emptyItem->setFlags(emptyItem->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
        emptyItem->setTextAlignment(Qt::AlignCenter);
        flightTable->setItem(row, 0, emptyItem);
        flightTable->setSpan(row, 0, 1, 5);
        confirmBtn->setEnabled(false);
        return;
    }

    flightButtonGroup = new QButtonGroup(this);
    flightButtonGroup->setExclusive(true);

    for (int i = 0; i < flights.size(); ++i) {
        const FlightInfo &flight = flights[i];
        int row = flightTable->rowCount();
        flightTable->insertRow(row);

        // 选择列（单选按钮）
        QWidget *radioWidget = new QWidget();
        QHBoxLayout *radioLayout = new QHBoxLayout(radioWidget);
        radioLayout->setContentsMargins(0, 0, 0, 0);
        radioLayout->setAlignment(Qt::AlignCenter);
        QRadioButton *radioBtn = new QRadioButton();
        radioBtn->setProperty("flightIndex", i);
        radioLayout->addWidget(radioBtn);
        flightTable->setCellWidget(row, 0, radioWidget);

        // 航班信息
        flightTable->setItem(row, 1, new QTableWidgetItem(flight.flightNumber));
        flightTable->setItem(row, 2, new QTableWidgetItem(flight.departureTime.toString("HH:mm")));
        flightTable->setItem(row, 3, new QTableWidgetItem(flight.arrivalTime.toString("HH:mm")));

        // 时长
        int hours = flight.duration / 60;
        int mins = flight.duration % 60;
        QString durationStr = QString("%1时%2分").arg(hours).arg(mins);
        flightTable->setItem(row, 4, new QTableWidgetItem(durationStr));

        // 连接单选按钮
        flightButtonGroup->addButton(radioBtn, i);
        connect(radioBtn, &QRadioButton::toggled, this, [=](bool checked) {
            if (checked) {
                selectedFlightIndex = i;
                selectedFlight = flight;
                // 当选择航班时，立即弹出舱位选择对话框
                QDialog *seatDialog = createSeatSelectionDialog(flight);
                if (seatDialog->exec() == QDialog::Accepted) {
                    enableConfirmButton();  // 舱位选择完成后才启用确认按钮
                } else {
                    // 如果取消选择舱位，清除航班选择
                    radioBtn->setChecked(false);
                    selectedFlightIndex = -1;
                    selectedFlight = FlightInfo();
                }
            }
        });
    }

    // 设置行高
    for (int i = 0; i < flightTable->rowCount(); ++i) {
        flightTable->setRowHeight(i, 40);
    }
}

void ChangeFlightDialog::onSeatButtonClicked()
{
    if (selectedFlightIndex >= 0 && selectedFlightIndex < availableFlights.size()) {
        const FlightInfo &flight = availableFlights[selectedFlightIndex];

        QDialog *seatDialog = createSeatSelectionDialog(flight);
        if (seatDialog->exec() == QDialog::Accepted) {
            enableConfirmButton();
        }
    }
}

QDialog* ChangeFlightDialog::createSeatSelectionDialog(const FlightInfo &flight)
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("选择舱位");
    dialog->setFixedSize(350, 300);

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->setContentsMargins(20, 20, 20, 20);

    QLabel *titleLabel = new QLabel(QString("为航班 %1 选择舱位").arg(flight.flightNumber));
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; margin-bottom: 20px;");
    layout->addWidget(titleLabel);

    QButtonGroup *seatGroup = new QButtonGroup(dialog);

    QStringList seatTypes = {"经济舱", "商务舱", "头等舱"};
    double prices[] = {flight.economyPrice, flight.businessPrice, flight.firstClassPrice};
    int seats[] = {flight.economySeats, flight.businessSeats, flight.firstClassSeats};

    for (int i = 0; i < seatTypes.size(); ++i) {
        QWidget *seatWidget = new QWidget();
        QHBoxLayout *hLayout = new QHBoxLayout(seatWidget);

        QRadioButton *radioBtn = new QRadioButton(seatTypes[i]);
        radioBtn->setProperty("seatClass", seatTypes[i]);
        radioBtn->setEnabled(seats[i] > 0);

        QLabel *priceLabel = new QLabel(QString("¥%1").arg(prices[i], 0, 'f', 2));
        priceLabel->setStyleSheet("color: #E74C3C; font-weight: bold;");

        QLabel *seatLabel = new QLabel(QString("余票: %1").arg(seats[i]));
        seatLabel->setStyleSheet(seats[i] > 0 ? "color: #27AE60;" : "color: #E74C3C;");

        hLayout->addWidget(radioBtn);
        hLayout->addWidget(priceLabel);
        hLayout->addStretch();
        hLayout->addWidget(seatLabel);

        layout->addWidget(seatWidget);
        seatGroup->addButton(radioBtn);

        if (seatTypes[i] == selectedSeatClass && seats[i] > 0) {
            radioBtn->setChecked(true);
        }
    }

    layout->addStretch();

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);

    connect(dialog, &QDialog::accepted, this, [=]() {
        QAbstractButton *selected = seatGroup->checkedButton();
        if (selected) {
            selectedSeatClass = selected->property("seatClass").toString();
        }
    });

    return dialog;
}

void ChangeFlightDialog::clearFlightSelection()
{
    selectedFlightIndex = -1;
    selectedFlight = FlightInfo();
}

void ChangeFlightDialog::enableConfirmButton()
{
    confirmBtn->setEnabled(selectedFlightIndex >= 0 && !selectedSeatClass.isEmpty());
}

bool ChangeFlightDialog::validateChangeConditions() const
{
    if (selectedFlight.flightNumber.isEmpty()) {
        QMessageBox::warning(const_cast<ChangeFlightDialog*>(this), "错误", "请选择新的航班");
        return false;
    }

    if (selectedSeatClass.isEmpty()) {
        QMessageBox::warning(const_cast<ChangeFlightDialog*>(this), "错误", "请选择舱位");
        return false;
    }

    // 检查是否和原订单相同
    if (selectedFlight.flightNumber == originalOrder.flightNumber &&
        selectedFlight.date == originalOrder.date &&
        selectedSeatClass == originalOrder.seatClass) {
        QMessageBox::information(const_cast<ChangeFlightDialog*>(this), "提示", "选择的航班和舱位与原订单相同，无需改签");
        return false;
    }

    return true;
}

void ChangeFlightDialog::onConfirmClicked()
{
    if (!validateChangeConditions()) {
        return;
    }

    // 检查是否有选中的航班和舱位
    if (selectedFlight.flightNumber.isEmpty() || selectedSeatClass.isEmpty()) {
        QMessageBox::warning(this, "错误", "请先选择航班和舱位");
        return;
    }

    // 构建确认消息 - 使用更安全的格式化方式
    QString message = QString("确认将订单 [%1] 改签为：\n\n"
                              "   新航班：%2\n"
                              "   新出发时间：%3 %4\n"
                              "   新舱位：%5\n\n"
                              "改签后原订单将变为'已改签'状态，"
                              "原支付金额将用于抵扣新订单。")
                          .arg(originalOrder.orderId)
                          .arg(selectedFlight.flightNumber)
                          .arg(selectedFlight.date.toString("yyyy-MM-dd"))
                          .arg(selectedFlight.departureTime.toString("HH:mm"))
                          .arg(selectedSeatClass);

    // 使用更标准的按钮
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("确认改签");
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    // 设置消息框大小
    msgBox.setMinimumWidth(500);
    msgBox.setMinimumHeight(200);

    // 设置字体，确保中文显示正常
    QFont font = msgBox.font();
    font.setPointSize(10);
    msgBox.setFont(font);

    if (msgBox.exec() == QMessageBox::Yes) {
        emit changeRequested(originalOrder.orderId, selectedFlight, selectedSeatClass);
        accept();
    }
}
