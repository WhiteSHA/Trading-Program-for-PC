#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_show_hideButton_clicked();

    void on_logInPushButton_clicked();

private:
    void initUi();

private:
    Ui::MainWindow *ui;

    QMovie *m_movie = nullptr;
};
#endif // MAINWINDOW_H
