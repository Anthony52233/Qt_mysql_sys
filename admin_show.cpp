#include "admin_show.h"
#include "ui_admin_show.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <qdebug.h>
#include <QMessageBox>

admin_show::admin_show(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_show)
{
    ui->setupUi(this);
    show_admin_info();

    dialog_add_admin = new Dialog_add_admin (this);//先初始化指针，要不然下面connect函数调用时，程序会崩溃。
    dialog_edit_admin = new Dialog_edit_admin(this);

    connect(ui->pushButton_delete_admin, SIGNAL(clicked()), this, SLOT(delete_admin()));

    //接收到dialog_add_admin发送的want_to_refresh_admin_info()信号，就调用show_admin_info();
    connect(dialog_add_admin, &Dialog_add_admin::want_to_refresh_admin_info, this, &admin_show::show_admin_info);
    connect(dialog_edit_admin, &Dialog_edit_admin::want_to_refresh_admin_info, this, &admin_show::show_admin_info);
}

admin_show::~admin_show()
{
    delete ui;
}

void admin_show::delete_admin()
{
    int current_row = ui->tableWidget_admin->currentRow();//表格中选中的行数。
    if(current_row == -1)
    {
        QMessageBox::about(this, "错误", "没有选中任何一条记录！");
        return;
    }
    QString admin_name = ui->tableWidget_admin->item(current_row, 0)->text();
    QString command = tr("delete from admins where admin_name = \"%1\";").arg(admin_name);
    qDebug() << "command:" << command;
    QSqlQuery query(command);
    query.exec();

    show_admin_info();
}

void admin_show::show_admin_info()
{
    QString command = tr("select * from admins;");
    qDebug() <<"show_admin_info():" << command;
    QSqlQuery query(command);
    query.exec();
    int nRow = query.size();
    QSqlRecord sqlRecord = query.record();
    int nColumn = sqlRecord.count();
    ui->tableWidget_admin->setRowCount(nRow);
    ui->tableWidget_admin->setColumnCount(nColumn);
    int i=0;
    query.first();
    do{
        for(int j=0; j<nColumn; j++)
        {
            ui->tableWidget_admin->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        }
        i++;
    }while(query.next());
}

//添加管理员按钮被点击事件
//显示对话框
void admin_show::on_pushButton_add_admin_clicked()
{

    dialog_add_admin->setModal(true);
    dialog_add_admin->show();
}

void admin_show::on_pushButton_alter_admin_clicked()
{
    //弹出界面，设置初值，修改，写回。
    //为dialog_edit_admin设置初值
    //获取账户密码
    int current_row = ui->tableWidget_admin->currentRow();//表格中选中的行数。
    if(current_row == -1)
    {
        QMessageBox::about(this, "错误", "没有选中任何一条记录！");
        return;
    }
    QString account = ui->tableWidget_admin->item(current_row, 0)->text();
    QString password = ui->tableWidget_admin->item(current_row, 1)->text();

    dialog_edit_admin->setAccount(account);
    dialog_edit_admin->setPassword(password);
    dialog_edit_admin->setModal(true);
    dialog_edit_admin->show();
}
