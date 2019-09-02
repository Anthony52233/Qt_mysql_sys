#include "dialog_find_custom.h"
#include "ui_dialog_find_custom.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>

Dialog_find_custom::Dialog_find_custom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_find_custom)
{
    ui->setupUi(this);
    setWindowTitle("查找用户");
    ui->radioButton_name->setChecked(true);//默认用户名被选中。
}

Dialog_find_custom::~Dialog_find_custom()
{
    delete ui;
}

void Dialog_find_custom::on_pushButton_find_clicked()
{
    //根据输入框和单选框确定要搜索内容。
    bool isName = ui->radioButton_name->isChecked();
    bool isSex = ui->radioButton_sex->isChecked();
    bool isPhone = ui->radioButton_phone->isChecked();

    QString find_content = ui->lineEdit_find->text();
    QString command;
    if(isName)
    {
        command = tr("select * from customs where user_name = \"%1\";").arg(find_content);
    }
    else if (isSex) {
        command = tr("select * from customs where sex = \"%1\";").arg(find_content);
    }
    else if(isPhone) {
        command = tr("select * from customs where phone = \"%1\";").arg(find_content);
    }
    QSqlQuery query(command);
    query.exec();
    int nRow = query.size();
    if(nRow == 0)
    {
        QMessageBox::about(this, "错误", "没有查到该信息，请确认属性选择正确！");
        return;
    }
    QSqlRecord sqlRecord = query.record();
    int nColumn = sqlRecord.count();
    ui->tableWidget_show->setRowCount(nRow);
    ui->tableWidget_show->setColumnCount(nColumn);
    query.first();
    int i = 0;
    do{
        for (int j=0; j<nColumn; j++)
        {
            ui->tableWidget_show->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        }
        i++;
    }while(query.next());


}
