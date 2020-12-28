#include "AdminMainPage.h"
#include "ui_AdminMainPage.h"

AdminMainPage::AdminMainPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminMainPage)
{
    ui->setupUi(this);
}

AdminMainPage::~AdminMainPage()
{
    delete ui;
}
