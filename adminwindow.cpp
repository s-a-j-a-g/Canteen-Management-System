#include "adminwindow.h"
#include "ui_adminwindow.h"

#include "studentstaffoption.h"
#include "showcustomerdataoption.h"
#include "admintodaysspecial.h"
#include "logout.h"
#include "showbalance.h"
#include "showfoodmenu.h"
#include "deletecustomer.h"
#include "admincustomerlogin.h"
#include "adminaccountsettings.h"
#include "discountoffer.h"

#include <QDebug>
#include <QTimer>
#include <QDateTime>

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);

    setWindowState(Qt::WindowMaximized);

    timer_1s = new QTimer(this);
    QObject::connect(timer_1s, SIGNAL(timeout()), this, SLOT(showTime()));
    timer_1s->start(1000);

    ui->stackedWidget->setCurrentIndex(0);
}

void AdminWindow::showTime()
{
    ui->label_showTime->setText(QTime::currentTime().toString("h:mm a"));
    ui->label_showDate->setText(QDate::currentDate().toString("ddd, MMMM dd, yyyy"));
}

void AdminWindow::receive_admin(QString username, QString password)
{
    MainWindow connect_database;

    if (!connect_database.sqlOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }

    connect_database.sqlOpen();

    QSqlQuery qry;

    qry.prepare("SELECT * FROM Admin WHERE Username = '"+username+"' AND Password = '"+password+"'");

    if (qry.exec())
    {
        while(qry.next())
        {
            ui->label_username->setText(username);
            ui->label_showName->setText(qry.value(1).toString());
        }
        connect_database.sqlClose();
    }
}

void AdminWindow::on_pushButton_showcustomerdata_clicked()
{
    ShowCustomerDataOption showDataOption;
    showDataOption.setModal(true);
    showDataOption.exec();
}

void AdminWindow::on_pushButton_todays_special_clicked()
{
    AdminTodaysSpecial todayspecial;
    todayspecial.setModal(true);
    todayspecial.exec();
}

void AdminWindow::on_pushButton_add_customer_clicked()
{
    StudentStaffOption option;
    option.setModal(true);
    option.exec();
}

void AdminWindow::on_pushButton_logout_clicked()
{
    this->hide();
    parentWidget()->show();
//    Logout logout_dialog;
//    logout_dialog.setModal(true);
//    logout_dialog.exec();
}

void AdminWindow::on_pushButton_showBalance_clicked()
{
    ShowBalance balance;
    balance.setModal(true);
    balance.exec();
}

void AdminWindow::on_pushButton_foodMenu_clicked()
{
    ShowFoodMenu menu;
    menu.setModal(true);
    menu.exec();
}

void AdminWindow::on_pushButton_discountOffer_clicked()
{
    DiscountOffer discount;
    discount.setModal(true);
    discount.exec();
}

void AdminWindow::on_pushButton_addBalance_clicked()
{
    QString data = "addbalance";
    AdminCustomerLogin *login = new AdminCustomerLogin();
    login->setModal(true);
    login->show();

    connect(this, SIGNAL(send(const QString)), login, SLOT(receive(const QString)));
    emit send(data);
}

void AdminWindow::on_pushButton_deleteCustomer_clicked()
{
    QString data = "deletecustomer";
    AdminCustomerLogin *login = new AdminCustomerLogin();
    login->setModal(true);
    login->show();

    connect(this, SIGNAL(send(const QString)), login, SLOT(receive(const QString)));
    emit send(data);
}

void AdminWindow::on_pushButton_account_settings_clicked()
{
    AdminAccountSettings settings;
    settings.setModal(true);
    settings.exec();
}

void AdminWindow::on_pushButton_side_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void AdminWindow::on_pushButton_side_close_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}
