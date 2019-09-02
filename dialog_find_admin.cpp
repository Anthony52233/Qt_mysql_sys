#include "dialog_find_admin.h"
#include "ui_dialog_find_admin.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>

Dialog_find_admin::Dialog_find_admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_find_admin)
{
    ui->setupUi(this);
}

Dialog_find_admin::~Dialog_find_admin()
{
    delete ui;
}

//find对话框中查找按钮被点击
void Dialog_find_admin::on_pushButton_find_clicked()
{
    QString find_account = ui->lineEdit->text();
    if(find_account == "")
    {
        QMessageBox::about(this, "错误", "你还没有输入要查找的用户");
        return;
    }
    QString command = tr("select * from admins where admin_name = \"%1\";").arg(find_account);
    QSqlQuery query(command);
    query.exec();
    int nRow = query.size();
    if(nRow == 0)
    {
        QMessageBox::about(this, "错误", "没有查到该用户！");
        return;
    }
    QSqlRecord sqlRecord = query.record();
    int nColumn = sqlRecord.count();
    ui->tableWidget_show_find_result->setRowCount(nRow);
    ui->tableWidget_show_find_result->setColumnCount(nColumn);
    query.first();
    //就一列数据
    for(int j=0; j<nColumn; j++)
    {
        ui->tableWidget_show_find_result->setItem(0, j, new QTableWidgetItem(query.value(j).toString()));
    }

}
