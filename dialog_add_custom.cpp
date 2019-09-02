#include "dialog_add_custom.h"
#include "ui_dialog_add_custom.h"
#include <QSqlQuery>
#include <qdebug.h>

Dialog_add_custom::Dialog_add_custom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_add_custom)
{
    ui->setupUi(this);
}

Dialog_add_custom::~Dialog_add_custom()
{
    delete ui;
}

void Dialog_add_custom::on_pushButton_commit_clicked()
{
    QString account = ui->lineEdit_account->text();
    QString password = ui->lineEdit_password->text();
    double balance = ui->lineEdit_account->text().toDouble();
    QString sex = ui->lineEdit_sex->text();
    QString phone = ui->lineEdit_phone->text();

    QString command = tr("insert into customs values(\"%1\", \"%2\", %3, \"%4\", \"%5\");").arg(account).arg(password).arg(balance).arg(sex).arg(phone);
    qDebug() << "add custom" << command;
    QSqlQuery query(command);
    emit want_to_refresh_custom_info();
    this->close();
}
