#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMovie>
#include <QTimer>
#include <QMessageBox>

#include <Admin_pages/AdminMainPage.h>
#include <CoreGlobals.h>
#include "Starter.h"

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

    initStarter();
}

void MainWindow::initStarter() const
{
    Starter::runStarter(QThread::currentThread());
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
    delete temp;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_show_hideButton_clicked()
{
    if(m_movie != nullptr)
        m_movie->deleteLater();

    if(isChecked)
        m_movie = new QMovie(":/gifs/Resources/Gifs/show.gif");
    else
        m_movie = new QMovie(":/gifs/Resources/Gifs/hide.gif");

    m_movie->setScaledSize(QSize(60, 45));
    QLabel *processLabel = ui->gifLabel;
    m_movie->stop();
    processLabel->setMovie(m_movie);
    m_movie->start();

    QTimer::singleShot(1200, m_movie, SLOT(stop()));

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
        User user;
        bool res = CoreGlobals::g_database->getUserByUsername(&user, ui->usernameLineEdit->text());

        if(!res)
        {
            QMessageBox::warning(this, "Մուտքի սխալ", QString::fromUtf8("Տվյալ օգտանունով օգտատեր չի գտնվել"));
            return;
        }

        if(user.password != ui->passwordLineEdit->text())
        {
            QMessageBox::warning(this, "Մուտքի սխալ", QString::fromUtf8("Գաղտնաբառը սխալ է"));
            return;
        }

        if(!user.isActive)
        {
            QMessageBox::warning(this, "Մուտքի սխալ", QString::fromUtf8("Տվյալ օգտատերը ակտիվ չէ"));
            return;
        }

        if(user.isAdmin)
        {
            AdminMainPage *adminPage = new AdminMainPage();
            adminPage->show();
            this->close();
            this->~MainWindow();
        }
        else
        {
            // navigate to cashier main page
        }
    }
}
