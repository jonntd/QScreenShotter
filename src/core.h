#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "mainwindow.h"
#include <QApplication>
#include "system.h"
#include <map>
#include <QString>
#include <QWidget>
#include <QScreen>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QRect>
#include <QSettings>
#include <QSignalMapper>
#include <QStandardPaths>
#include "aboutdialog.h"
#include <QString>
//#include "xwindowrectangle.h"
#include "screenshot.h"
#include <QTimer>
#include "webexport.h"
#include "exportdialog.h"
#include "exportresult.h"

#if defined(HAVE_X11) || defined(WIN32)
    #include "neweventfilter.h"    
#endif
#include "x11info.h"
#define getWindow(winID,cast_type)({static_cast<cast_type>(system::getCore()->windows[winID]);})

class core : public QApplication
{
    Q_OBJECT

public:
    screenshot *sc;
    QRect screen;
    WEBExport exp;

    std::map < QString, QWidget* > windows;
    QTimer timer;

    MainWindow::actions action;

    explicit core ( int &argc, char *argv[] );
    virtual ~core();
    int exec();
    void setPixmap ( QPixmap &pixmap );
    void defaultSettings();

    bool isVisible;

    // Settings
    QSettings *settings;

    // tray
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QAction *hideAction;
    QAction *quitAction;

    QPixmap picture;

    //XWindowRectangle rect;

private:
    void initTray();
    std::map < QString, QRect > windowGeometry;

signals:

public slots:
    void trayClick ( QSystemTrayIcon::ActivationReason reason );
    void mainAction ( MainWindow::actions action = MainWindow::DEFAULT );
    void toggleVisability();
    void showAbout();
    void exportToWEB();
    void showExportResult ( QString, QString, QString );
    void openSettingsDialog ( int tabIndex = -1 );

    void trayShotDisplay();
    void trayShotWindow();
    void trayShotRect();
};

#endif // CORE_H
