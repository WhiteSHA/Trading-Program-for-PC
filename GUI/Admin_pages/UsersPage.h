#ifndef USERSPAGE_H
#define USERSPAGE_H

#include <QMainWindow>
#include <QtWidgets/QComboBox>
#include <QLabel>
#include <QtWidgets/QCheckBox>

namespace Ui {
class UsersPage;
}

class UsersPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit UsersPage(QWidget *parent = nullptr);
    ~UsersPage();

private slots:
    void on_logInPushButton_clicked();

    void on_changeUserPushButton_clicked();

    void on_newUserPushButton_clicked();

    void on_deleteUserPusButton_clicked();

private:
    void initUI();

    void initUsersFromDB();

    QComboBox* createComboboxOfTypes(bool);

    QLabel* createLabelsForTable(QString);

    QCheckBox *createStateCheckBox(bool);

private:
    Ui::UsersPage *ui;
};

#endif // USERSPAGE_H
