#ifndef ADMINMAINPAGE_H
#define ADMINMAINPAGE_H

#include <QMainWindow>

namespace Ui {
class AdminMainPage;
}

class AdminMainPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminMainPage(QMainWindow *parent = nullptr);
    ~AdminMainPage();

private slots:
    void on_logInPushButton_clicked();

    void on_usersPushButton_clicked();

private:
    void initUI();

private:
    Ui::AdminMainPage *ui;
};

#endif // ADMINMAINPAGE_H
