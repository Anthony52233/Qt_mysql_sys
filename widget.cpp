#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QtDebug>
#include "custom_show.h"
#include "admin_show.h"

QString Widget::user_name = "null";
QString Widget::admin_name = "null";

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    if(login() != 1)
    {
        QMessageBox::about(this,"数据库无法打开", "数据库的配置信息出错或没有该数据库！");
        return;
    }
    //数据库连接成功。
    //连接信号和槽
    connect(ui->pushButton_login, SIGNAL(clicked()), this, SLOT(process_login_info()));
    //connect(this, SIGNAL(success_to_login()))
}

Widget::~Widget()
{
    delete ui;
}

void Widget::process_login_info()
{
    //获取用户的信息
    QString user_name = ui->lineEdit_account->text();
    QString user_passwd = ui->lineEdit_password->text();
    QString command;
    bool isAdmin = false;
    qDebug() << "check box:" << ui->checkBox_admin->isChecked();
    if(ui->checkBox_admin->isChecked() == true)
    {
        isAdmin = true;
    }

    if(isAdmin)
    {
        //查询admins表中数据
        command = QString("select admin_password from admins where admin_name = \"%1\"").arg(user_name);
    }
    else
    {
        //进入数据库验证
        command = QString("select user_password from customs where user_name = \"%1\"").arg(user_name);
    }

    //qDebug() << command;
    QSqlQuery query(command);
    query.exec();
    QSqlRecord sqlRecord = query.record();
    //qDebug() << "行数：" << query.size() << "列数：" << sqlRecord.count();
    query.first();//指向第一条数据，应该只有一条
    if(user_passwd != query.value(0).toString())//这条记录的第一列。
    {
        //登录失败
        QMessageBox::about(this,"登录失败", "账号密码错误！");
        return;
    }
    //登录成功
    if(isAdmin)
    {
        Widget::admin_name = user_name;
    }
    else {
        Widget::user_name = user_name;
    }

    //这里触发一个登录成功信号
    //emit success_to_login();
    this->hide();
    if(isAdmin)//是管理员用户，跳转到管理员界面
    {
        admin_show *s = new admin_show();
        s->show();
    }
    else {//否则跳转到用户界面
        custom_show *s = new custom_show();
        s->show();
    }
}

int Widget::login()
{
    QSqlDatabase dataBase;
    if(QSqlDatabase::contains("czs"))
    {
        dataBase = QSqlDatabase::database("czs");
        //QMessageBox::about(this,"连接数据库失败", "没有数据库：czs！");
        return 0;//登录失败
    }
    else
    {
        dataBase = QSqlDatabase::addDatabase("QMYSQL");
        dataBase.setHostName("localhost");
        dataBase.setPort(3306);
        dataBase.setDatabaseName("czs");
        dataBase.setUserName("root");
        dataBase.setPassword("mysql666");
    }

    if(!dataBase.open())
    {
        //QMessageBox::about(this,"数据库无法打开", "可能是数据库的配置信息出错！");
        return 0;
    }
    return 1;
}
