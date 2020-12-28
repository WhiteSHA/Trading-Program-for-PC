#include "AdminMainPage.h"
#include "ui_AdminMainPage.h"

#include <MainWindow.h>

AdminMainPage::AdminMainPage(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminMainPage)
{
    ui->setupUi(this);
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
