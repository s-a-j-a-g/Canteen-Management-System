#include "addcustomeroption.h"
#include "ui_addcustomeroption.h"

#include "studentcustomeroption.h"

AddCustomerOption::AddCustomerOption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCustomerOption)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint,false);
}

AddCustomerOption::~AddCustomerOption()
{
    delete ui;
}

void AddCustomerOption::on_pushButton_student_clicked()
{
    this->hide();
    StudentCustomerOption student;
    student.setModal(true);
    student.exec();
}
