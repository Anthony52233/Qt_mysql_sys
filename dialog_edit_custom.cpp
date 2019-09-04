#include "dialog_edit_custom.h"
#include "ui_dialog_edit_custom.h"
#include <qdebug.h>
#include <qsqlquery.h>
#include <QMessageBox>
#include "widget.h"
#include <QDateTime>

Dialog_edit_custom::Dialog_edit_custom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_edit_custom)
{
    ui->setupUi(this);
    ui->lineEdit_account->setReadOnly(true);
}

Dialog_edit_custom::~Dialog_edit_custom()
{
    delete ui;
}

void Dialog_edit_custom::on_pushButton_commit_clicked()
{
    QString account = ui->lineEdit_account->text();
    QString password = ui->lineEdit_password->text();
    double balance = ui->lineEdit_balance->text().toDouble();
    QString sex = ui->lineEdit_sex->text();
    QString phone = ui->lineEdit_phone->text();

    QString command = tr("update customs set user_password = \"%1\", balance = %2, sex = \"%3\", phone = \"%4\" where user_name = \"%5\";").arg(password).arg(balance).arg(sex).arg(phone).arg(account);
    qDebug() <<"edit custom:" <<command;

    QSqlQuery query(command);
    query.exec();

    //manage表中插入数据
    QString command_insert = tr("insert into update_user values(\"%1\", \"%2\", \"%3\", \"edit\");").arg(Widget::admin_name).arg(account).arg(QDateTime::currentDateTime().toTime_t());
    qDebug() << command_insert;
    QSqlQuery query_insert(command_insert);
    query_insert.exec();

    QMessageBox::about(this, "正确", "更新成功！");
    emit want_to_refresh_custom();
    this->close();
}

void Dialog_edit_custom::setAllInfo(QString account, QString password, double balance, QString sex, QString phone)
{
    ui->lineEdit_account->setText(account);
    ui->lineEdit_password->setText(password);
    ui->lineEdit_balance->setText(QString::number(balance));
    ui->lineEdit_sex->setText(sex);
    ui->lineEdit_phone->setText(phone);
}
