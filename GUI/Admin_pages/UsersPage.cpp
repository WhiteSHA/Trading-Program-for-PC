#include "UsersPage.h"
#include "ui_UsersPage.h"

#include <QDebug>

#include <CoreGlobals.h>
#include <GuiGlobals.h>
#include <QMessageBox>
#include <Admin_pages/AdminMainPage.h>
#include <Admin_pages/InsertOrEditUsersPage.h>

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

    ui->tableWidget->setRowCount(count - 1);
    for(int i = 2; i <= count; i++)
    {
        User user;
        CoreGlobals::g_database->getUser(&user, i);

        QLabel *label = createLabelsForTable(user.username);
        label->setObjectName(QString::number(user.id));
        ui->tableWidget->setCellWidget(i - 2, 0, label);
        ui->tableWidget->setCellWidget(i - 2, 1, createComboboxOfTypes(user.isAdmin));
        ui->tableWidget->setCellWidget(i - 2, 2, createStateCheckBox(user.isActiv));
        ui->tableWidget->setCellWidget(i - 2, 3, createLabelsForTable(user.name));
        ui->tableWidget->setCellWidget(i - 2, 4, createLabelsForTable(user.surname));
        ui->tableWidget->setCellWidget(i - 2, 5, createLabelsForTable(user.address));
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

void UsersPage::on_changeUserPushButton_clicked()
{
    if(!ui->tableWidget->selectionModel()->selectedRows().isEmpty())
    {
        if(ui->tableWidget->selectionModel()->selectedRows().count() != 1)
        {
            QMessageBox::warning(this, "Սխալ", "Անհրաժեշտ է ընտրել ճիշտ մեկ տող");
        }
        else
        {
            int selectedRow = ui->tableWidget->selectionModel()->selectedRows().at(0).row();

            GuiGlobals::action.actionType = ActionType::TO_EDIT;
            GuiGlobals::action.id = ui->tableWidget->cellWidget(selectedRow, 0)->objectName().toInt();

            InsertOrEditUsersPage *insertOrAddPage = new InsertOrEditUsersPage();
            insertOrAddPage->show();
            this->close();
            this->~UsersPage();
        }
    }
    else
    {
        QMessageBox::warning(this, "Սխալ", "Անհրաժեշտ է նշել խմբագրվող օգտվողի տողը");
    }
}

void UsersPage::on_newUserPushButton_clicked()
{
    GuiGlobals::action.actionType = ActionType::TO_INSERT;
    GuiGlobals::action.id = -1;

    InsertOrEditUsersPage *insertOrAddPage = new InsertOrEditUsersPage();
    insertOrAddPage->show();
    this->close();
    this->~UsersPage();
}

void UsersPage::on_deleteUserPusButton_clicked()
{
    if(!ui->tableWidget->selectionModel()->selectedRows().isEmpty())
    {
        if(ui->tableWidget->selectionModel()->selectedRows().count() != 1)
        {
            QMessageBox::warning(this, "Սխալ", "Անհրաժեշտ է ընտրել ճիշտ մեկ տող");
        }
        else
        {
            if(QMessageBox::question(this, "ՈՒշադրություն", QString::fromUtf8("Հեռացնե՞լ նշված օգտվողին"))
                    == QMessageBox::Yes)
            {
                int selectedRow = ui->tableWidget->selectionModel()->selectedRows().at(0).row();

                int userId = ui->tableWidget->cellWidget(selectedRow, 0)->objectName().toInt();

                CoreGlobals::g_database->deleteUser(userId);

                initUsersFromDB();
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "Սխալ", "Օգտվողին հեռացնելու համար անհրաժեշտ է ընտրել տողը");
    }
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
