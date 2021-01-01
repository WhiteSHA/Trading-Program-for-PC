#ifndef INSERTOREDITUSERSPAGE_H
#define INSERTOREDITUSERSPAGE_H

#include <QMainWindow>

namespace Ui {
class InsertOrEditUsersPage;
}

class InsertOrEditUsersPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit InsertOrEditUsersPage(QWidget *parent = nullptr);
    ~InsertOrEditUsersPage();

private slots:
    void on_previousPushButton_clicked();

    void on_savePushButton_clicked();

    void on_show_hidePushButton_clicked();

private:
    void initUI();

private:
    Ui::InsertOrEditUsersPage *ui;
};

#endif // INSERTOREDITUSERSPAGE_H
