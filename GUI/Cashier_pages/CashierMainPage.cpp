#include "CashierMainPage.h"
#include "ui_CashierMainPage.h"

CashierMainPage::CashierMainPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CashierMainPage)
{
    ui->setupUi(this);
}

CashierMainPage::~CashierMainPage()
{
    delete ui;
}
