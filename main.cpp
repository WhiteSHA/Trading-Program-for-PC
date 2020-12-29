#include "MainWindow.h"

#include <QApplication>
#include <QTextCodec>
#include <QFont>
#include <QFontDatabase>
#include <QSettings>
#include <winsqlite/winsqlite3.h>

static void setupApplication(QApplication& a)
{
    // Setup fonts
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QFontDatabase::addApplicationFont(QString(":fonts/Assets/GHEAGrpalatReg.otf"));

    // Set icon
    a.setWindowIcon(QIcon(":/icons/Resources/icons/mainIcon.ico"));

    // Set application general info
    a.setOrganizationName("A&S");
    a.setOrganizationDomain("");
    a.setApplicationName("TradingProgram");

    // Set path to save settings
    QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, ".");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setupApplication(a);

    MainWindow w;
    w.show();

    return a.exec();
}
