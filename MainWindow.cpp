#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMovie>
#include <QTimer>
#include <QMessageBox>

namespace
{
    bool isChecked = true;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(this->geometry().width(), this->geometry().height());

    initUi();
}

void MainWindow::initUi()
{
    setPalette(QPalette(QColor(225, 225, 235)));
    setWindowTitle(QString::fromUtf8("Առևտրային ծրագիր"));
    setWindowIcon(QIcon(":/icons/Resources/icons/mainIcon.ico"));

    ui->passwordLineEdit->setEchoMode(isChecked ? QLineEdit::Password : QLineEdit::Normal);

    QPixmap *temp = new QPixmap(":/gifs/Resources/Gifs/show.gif");
    *temp = temp->scaled(60, 45);
    ui->gifLabel->setPixmap(*temp);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_show_hideButton_clicked()
{
    QMovie *movie = nullptr;
    if(isChecked)
        movie = new QMovie(":/gifs/Resources/Gifs/show.gif");
    else
        movie = new QMovie(":/gifs/Resources/Gifs/hide.gif");

    movie->setScaledSize(QSize(60, 45));
    QLabel *processLabel = ui->gifLabel;
    movie->stop();
    processLabel->setMovie(movie);
    movie->start();

    QTimer::singleShot(1200, movie, SLOT(stop()));

    isChecked = !isChecked;
    ui->passwordLineEdit->setEchoMode(isChecked ? QLineEdit::Password : QLineEdit::Normal);
}

void MainWindow::on_logInPushButton_clicked()
{
    if(ui->usernameLineEdit->text().length() < 1)
    {
        QMessageBox::warning(this, "Մուտքի սխալ", QString::fromUtf8("Օգտանունը մուտքագրված չէ"));
    }
    else if(ui->passwordLineEdit->text().length() < 1)
    {
        QMessageBox::warning(this, "Մուտքի սխալ", QString::fromUtf8("Գաղտնաբառը մուտքագրված չէ"));
    }
    else
    {

    }
}
