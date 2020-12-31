#include "UsersPage.h"
#include "ui_UsersPage.h"

#include <QDebug>

#include <CoreGlobals.h>
#include <Admin_pages/AdminMainPage.h>

UsersPage::UsersPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UsersPage)
{
    ui->setupUi(this);

    initUI();
}

void UsersPage::initUI()
{
    setPalette(QPalette(QColor(225, 225, 235)));
    setWindowTitle(QString::fromUtf8("Առևտրային ծրագիր"));

    QStringList headers;
    headers.append("Օգտանուն");
    headers.append("Տեսակ");
    headers.append("Գործող");
    headers.append("Անուն");
    headers.append("Ազգանուն");
    headers.append("Հասցե");
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStyleSheet("font: bold 12px;");

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    initUsersFromDB();
}

void UsersPage::initUsersFromDB()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    int count = 0;
    CoreGlobals::g_database->getUsersCount(count);

    ui->tableWidget->setRowCount(count);
    for(int i = 1; i <= count; i++)
    {
        User user;
        CoreGlobals::g_database->getUser(&user, i);

        ui->tableWidget->setCellWidget(i - 1, 0, createLabelsForTable(user.username));
        ui->tableWidget->setCellWidget(i - 1, 1, createComboboxOfTypes(user.isAdmin));
        ui->tableWidget->setCellWidget(i - 1, 2, createStateCheckBox(user.isActiv));
        ui->tableWidget->setCellWidget(i - 1, 3, createLabelsForTable(user.name));
        ui->tableWidget->setCellWidget(i - 1, 4, createLabelsForTable(user.surname));
        ui->tableWidget->setCellWidget(i - 1, 5, createLabelsForTable(user.address));
    }
}

UsersPage::~UsersPage()
{
    delete ui;
}

void UsersPage::on_logInPushButton_clicked()
{
    AdminMainPage *adminMain = new AdminMainPage();
    adminMain->show();
    this->close();
    this->~UsersPage();
}

QComboBox* UsersPage::createComboboxOfTypes(bool isAdmin)
{
    QComboBox *combo = new QComboBox;

    QStringList types;
    types.append("Ադմինիստրատոր");
    types.append("Գանձապահ");

    combo->addItems(types);

    combo->setCurrentIndex(isAdmin ? 0 : 1);

    return combo;
}

QLabel* UsersPage::createLabelsForTable(QString text)
{
    QLabel *label = new QLabel();
    label->setText(text);
    label->setAlignment(Qt::AlignCenter);
    return label;
}

QCheckBox* UsersPage::createStateCheckBox(bool isActive)
{
    QCheckBox *checkBox = new QCheckBox();

    checkBox->setChecked(isActive);

    checkBox->setStyleSheet("margin-left:60%; margin-right:50%;");

    return checkBox;
}
