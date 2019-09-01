#include "dialog_add_admin.h"
#include "ui_dialog_add_admin.h"
#include <QSqlQuery>
#include <QMessageBox>

Dialog_add_admin::Dialog_add_admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_add_admin)
{
    ui->setupUi(this);
}

Dialog_add_admin::~Dialog_add_admin()
{
    delete ui;
}

//对话框提交按钮
void Dialog_add_admin::on_pushButton_commit_clicked()
{
    QString admin_account = ui->lineEdit_account->text();
    QString admin_password = ui->lineEdit_password->text();
    QString commamd = tr("insert into admins values(%1, %2);").arg(admin_account).arg(admin_password);
    QSqlQuery query(commamd);
//    if(!query.exec());//该语句总是返回false，有待解决
//        QMessageBox::about(this, "错误", "sql语句执行失败！");
    emit want_to_refresh_admin_info();
    this->close();
}

