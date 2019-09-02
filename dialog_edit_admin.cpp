#include "dialog_edit_admin.h"
#include "ui_dialog_edit_admin.h"
#include <qdebug.h>
#include <qsqlquery.h>

Dialog_edit_admin::Dialog_edit_admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_edit_admin)
{
    ui->setupUi(this);
    ui->lineEdit_account->setReadOnly(true);//设置账户信息不可编辑
}

Dialog_edit_admin::~Dialog_edit_admin()
{
    delete ui;
}

void Dialog_edit_admin::setAccount(QString account)
{
    qDebug() << "account:" << account;
    ui->lineEdit_account->setText(account);
}

void Dialog_edit_admin::setPassword(QString passwd)
{
    qDebug() << "passwd:" << passwd;
    ui->lineEdit_password->setText(passwd);
}

void Dialog_edit_admin::on_pushButton_commit_clicked()
{
    QString name = ui->lineEdit_account->text();
    QString passwd = ui->lineEdit_password->text();
    QString command = tr("update admins set admin_password = \"%1\" where admin_name = \"%2\";").arg(passwd).arg(name);
    qDebug() <<"edit:" << command;
    QSqlQuery query(command);
    query.exec();
    emit want_to_refresh_admin_info();
    this->close();
}
