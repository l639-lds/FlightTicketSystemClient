#include <QApplication>
#include "mainwindow.h"
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("FlightTicketSystem");
    a.setApplicationName("FlightTicketApp");

    MainWindow w;
    w.show();
    return a.exec();
}
