#ifndef CHANGEFLIGHTDIALOG_H
#define CHANGEFLIGHTDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QButtonGroup>
#include <QDateEdit>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include "network_manager.h"

class ChangeFlightDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeFlightDialog(const OrderInfo &orderInfo, QWidget *parent = nullptr);
    ~ChangeFlightDialog();

signals:
    void changeRequested(const QString &orderId, const FlightInfo &newFlight, const QString &newSeatClass);

private slots:
    void onSearchClicked();
    void onConfirmClicked();
    void onFlightSearchResult(const QList<FlightInfo> &flights);
    void onSeatButtonClicked();

private:
    void initUI();
    void setupConnections();
    void updateFlightTable(const QList<FlightInfo> &flights);
    void clearFlightSelection();
    void enableConfirmButton();
    bool validateChangeConditions() const;
    // QWidget* createFlightRow(int row, const FlightInfo &flight);
    QDialog* createSeatSelectionDialog(const FlightInfo &flight);

    // UI 组件
    QTableWidget *flightTable;
    QDateEdit *newDateEdit;
    QLineEdit *fromEdit;
    QLineEdit *toEdit;
    QPushButton *searchBtn;
    QPushButton *confirmBtn;
    QPushButton *cancelBtn;
    QButtonGroup *seatButtonGroup;
    QButtonGroup *flightButtonGroup;

    // 数据
    OrderInfo originalOrder;
    QList<FlightInfo> availableFlights;
    FlightInfo selectedFlight;
    QString selectedSeatClass;
    int selectedFlightIndex;
};

#endif // CHANGEFLIGHTDIALOG_H
