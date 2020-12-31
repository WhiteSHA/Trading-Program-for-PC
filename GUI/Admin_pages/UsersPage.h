#ifndef USERSPAGE_H
#define USERSPAGE_H

#include <QMainWindow>

namespace Ui {
class UsersPage;
}

class UsersPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit UsersPage(QWidget *parent = nullptr);
    ~UsersPage();

private:
    Ui::UsersPage *ui;
};

#endif // USERSPAGE_H
