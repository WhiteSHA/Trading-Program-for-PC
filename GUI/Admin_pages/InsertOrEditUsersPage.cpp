#include "InsertOrEditUsersPage.h"
#include "ui_InsertOrEditUsersPage.h"

#include <GuiGlobals.h>
#include <CoreGlobals.h>
#include <QMessageBox>
#include <QDebug>

#include <Admin_pages/UsersPage.h>

namespace
{
    bool isShowed = false;
}

InsertOrEditUsersPage::InsertOrEditUsersPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InsertOrEditUsersPage)
{
    ui->setupUi(this);

    initUI();
}

void InsertOrEditUsersPage::initUI()
{
    setPalette(QPalette(QColor(225, 225, 235)));
    setWindowTitle(QString::fromUtf8("Առևտրային ծրագիր"));

    if(GuiGlobals::action.actionType == ActionType::TO_EDIT)
    {
        ui->mainLabel->setText(QString::fromUtf8("Փոփոխել օգտվողի\nտվյալները"));

        User user;
        if(CoreGlobals::g_database->getUser(&user, GuiGlobals::action.id))
        {
            ui->usernameLineEdit->setText(user.username);
            ui->passwordLineEdit->setText(user.username);
            ui->typeComboBox->setCurrentIndex(user.isAdmin ? 0 : 1);
            ui->stateComboBox->setCurrentIndex(user.isActive ? 0 : 1);
            ui->nameLineEdit->setText(user.name);
            ui->surnameLineEdit->setText(user.surname);
            ui->addressLineEdit->setText(user.address);
        }
    }

    ui->show_hidePushButton->setIcon(QIcon(":/png/Resources/png/show.png"));
    ui->show_hidePushButton->setIconSize(QSize(50,50));

    ui->passwordLineEdit->setEchoMode(!isShowed ? QLineEdit::Password : QLineEdit::Normal);
}

InsertOrEditUsersPage::~InsertOrEditUsersPage()
{
    delete ui;
}

void InsertOrEditUsersPage::on_previousPushButton_clicked()
{
    if(ui->usernameLineEdit->text().length() > 0 || ui->passwordLineEdit->text().length() > 0
            || ui->nameLineEdit->text().length() > 0 || ui->surnameLineEdit->text().length() > 0
            || ui->addressLineEdit->text().length() > 0)
    {
        if(QMessageBox::question(this, "ՈՒշադրություն", QString::fromUtf8("Ցանկանում ե՞ք չեղարկել կատարված փոփոխությունները"))
                == QMessageBox::Yes)
        {
            UsersPage *usersPage = new UsersPage();
            usersPage->show();
            this->close();
            this->~InsertOrEditUsersPage();
        }
    }
    else
    {
        UsersPage *usersPage = new UsersPage();
        usersPage->show();
        this->close();
        this->~InsertOrEditUsersPage();
    }
}

void InsertOrEditUsersPage::on_savePushButton_clicked()
{
    if(ui->usernameLineEdit->text().length() < 1)
        QMessageBox::warning(this, "Սխալ", QString::fromUtf8("Օգտանուն դաշտը լրացված չէ"));
    else if(ui->passwordLineEdit->text().length() < 1)
        QMessageBox::warning(this, "Սխալ", QString::fromUtf8("Գաղտնաբառ դաշտը լրացված չէ"));
    else if(ui->nameLineEdit->text().length() < 1)
        QMessageBox::warning(this, "Սխալ", QString::fromUtf8("Անուն դաշտը լրացված չէ"));
    else
    {
        User user;

        if(GuiGlobals::action.actionType == ActionType::TO_INSERT)
        {
            int lastId = 0;
            CoreGlobals::g_database->getLastUserId(lastId);
            qDebug() << "Last id from DB = " << lastId;
            user.id = ++lastId;
        }
        else
            user.id = GuiGlobals::action.id;

        user.username = ui->usernameLineEdit->text();
        user.password = ui->usernameLineEdit->text();
        user.isAdmin = ui->typeComboBox->currentIndex() ? 0 : 1;
        user.isActive = ui->stateComboBox->currentIndex() ? 0 : 1;
        user.name = ui->nameLineEdit->text();
        user.surname = ui->surnameLineEdit->text();
        user.address = ui->addressLineEdit->text();

        bool res = false;
        if(GuiGlobals::action.actionType == ActionType::TO_EDIT)
            res = CoreGlobals::g_database->updateUser(&user);
        else
            res = CoreGlobals::g_database->insertUser(&user);

        if(res)
        {
            UsersPage *usersPage = new UsersPage();
            usersPage->show();
            this->close();
            this->~InsertOrEditUsersPage();
        }
        else
            QMessageBox::critical(this, "Սխալ", QString::fromUtf8("Տվյալների բազայի սխալ"));
    }
}

void InsertOrEditUsersPage::on_show_hidePushButton_clicked()
{
    if(isShowed)
    {
        ui->show_hidePushButton->setIcon(QIcon(":/png/Resources/png/hide.png"));
        ui->show_hidePushButton->setIconSize(QSize(50,50));
    }
    else
    {
        ui->show_hidePushButton->setIcon(QIcon(":/png/Resources/png/show.png"));
        ui->show_hidePushButton->setIconSize(QSize(50,50));
    }
    isShowed = !isShowed;
    ui->passwordLineEdit->setEchoMode(isShowed ? QLineEdit::Password : QLineEdit::Normal);
}
