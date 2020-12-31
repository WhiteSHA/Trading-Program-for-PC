#include "UsersPage.h"
#include "ui_UsersPage.h"

UsersPage::UsersPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UsersPage)
{
    ui->setupUi(this);
}

UsersPage::~UsersPage()
{
    delete ui;
}
