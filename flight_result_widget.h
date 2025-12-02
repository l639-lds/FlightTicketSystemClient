#ifndef FLIGHTRESULTWIDGET_H
#define FLIGHTRESULTWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QDateEdit>
#include <QComboBox>
#include <QButtonGroup>
#include <QDialog>
#include <QRadioButton>
#include <QDebug>
#include <QBrush>
#include <QFont>
#include <QColor>
#include "network_manager.h"

class FlightResultWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FlightResultWidget(QWidget *parent = nullptr);
    ~FlightResultWidget();
    void setSearchConditions(const QString &from, const QString &to, const QDate &date);
    void updateFlightList(const QList<FlightInfo> &flights);

signals:
    void backToSearchSignal();
    void bookTicketSignal(const FlightInfo &flight, const QString &seatClass, const QString &passengerType);

private slots:
    void onBookClicked();
    void onBackClicked();

private:
    QTableWidget *flightTable;
    QList<FlightInfo> currentFlights;
    QString fromCity;
    QString toCity;
    QDate travelDate;

    // 新增：日期选择控件
    QDateEdit *dateEdit;
    QComboBox *passengerTypeCombo;

    void initUI();
    void initSearchSection();
    QWidget* createSeatOption(const QString &seatClass, double price,int seats, const QString &passengerType,QButtonGroup *buttonGroup);
};

#endif
