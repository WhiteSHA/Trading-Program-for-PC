#include "AdminMainPage.h"
#include "ui_AdminMainPage.h"

#include <MainWindow.h>
#include <Admin_pages/UsersPage.h>

AdminMainPage::AdminMainPage(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminMainPage)
{
    ui->setupUi(this);

    initUI();
}

void AdminMainPage::initUI()
{
    setPalette(QPalette(QColor(225, 225, 235)));
    setWindowTitle(QString::fromUtf8("Առևտրային ծրագիր"));
}

AdminMainPage::~AdminMainPage()
{
    delete ui;
}

void AdminMainPage::on_logInPushButton_clicked()
{
    MainWindow *main = new MainWindow();
    main->show();
    this->close();
    this->~AdminMainPage();
}

void AdminMainPage::on_usersPushButton_clicked()
{
    UsersPage *users = new UsersPage();
    users->show();
    this->close();
    this->~AdminMainPage();
}
