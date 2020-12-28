#ifndef CASHIERMAINPAGE_H
#define CASHIERMAINPAGE_H

#include <QMainWindow>

namespace Ui {
class CashierMainPage;
}

class CashierMainPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit CashierMainPage(QWidget *parent = nullptr);
    ~CashierMainPage();

private:
    Ui::CashierMainPage *ui;
};

#endif // CASHIERMAINPAGE_H
