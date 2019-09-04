#include "admin_show.h"
#include "ui_admin_show.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <qdebug.h>
#include <QMessageBox>
#include "widget.h"
#include "custom_show.h"
#include <QDateTime>

admin_show::admin_show(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_show)
{
    ui->setupUi(this);
    setWindowTitle("管理员界面");
    show_admin_info();//显示管理员信息
    show_custom_info();//显示客户信息
    show_indent_info();//显示订单信息
    show_camera_info();//显示相机信息

    ui->radioButton_manage_camera_no->setChecked(true);
    ui->radioButton_indent_no->setChecked(true);
    ui->radioButton_sort_rent_num->setChecked(true);

    //ui->tableWidget_indent->setAutoScroll(true);

    dialog_add_admin = new Dialog_add_admin (this);//先初始化指针，要不然下面connect函数调用时，程序会崩溃。
    dialog_edit_admin = new Dialog_edit_admin(this);
    dialog_find_admin = new Dialog_find_admin(this);
    dialog_add_custom = new Dialog_add_custom(this);
    dialog_edit_custom = new Dialog_edit_custom(this);
    dialog_find_custom = new Dialog_find_custom(this);
    dialog_edit_indent = new Dialog_edit_indent(this);
    dialog_add_camera = new Dialog_add_camera(this);

    connect(ui->pushButton_delete_admin, SIGNAL(clicked()), this, SLOT(delete_admin()));

    //接收到dialog_add_admin发送的want_to_refresh_admin_info()信号，就调用show_admin_info();
    connect(dialog_add_admin, &Dialog_add_admin::want_to_refresh_admin_info, this, &admin_show::show_admin_info);
    connect(dialog_edit_admin, &Dialog_edit_admin::want_to_refresh_admin_info, this, &admin_show::show_admin_info);
    connect(dialog_add_custom, &Dialog_add_custom::want_to_refresh_custom_info, this, &admin_show::show_custom_info);
    connect(dialog_edit_custom, &Dialog_edit_custom::want_to_refresh_custom, this, &admin_show::show_custom_info);
    connect(dialog_edit_indent, &Dialog_edit_indent::want_to_refresh_indent, this, &admin_show::show_indent_info);
    //这里的dialog_add_camera对象是增加功能的对象，修改功能的对象不是这个。
    connect(dialog_add_camera, &Dialog_add_camera::want_to_refresh_camera_info, this, &admin_show::show_camera_info);
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

void admin_show::show_custom_info()
{
    QString command = tr("select * from customs;");
    qDebug() <<"show_customs_info():" << command;
    QSqlQuery query(command);
    query.exec();
    int nRow = query.size();
    QSqlRecord sqlRecord = query.record();
    int nColumn = sqlRecord.count();
    ui->tableWidget_custom->setRowCount(nRow);
    ui->tableWidget_custom->setColumnCount(nColumn);
    int i=0;
    query.first();
    do{
        for(int j=0; j<nColumn; j++)
        {
            ui->tableWidget_custom->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        }
        i++;
    }while(query.next());
}

void admin_show::show_indent_info()
{
    QString command = tr("select * from my_indent;");
    QSqlQuery query(command);
    query.exec();
    int nRow = query.size();
    QSqlRecord sqlRecord = query.record();
    int nColumn = sqlRecord.count();
    ui->tableWidget_indent->setRowCount(nRow);
    ui->tableWidget_indent->setColumnCount(nColumn);
    int i=0;
    query.first();
    do{
        for(int j=0; j<nColumn; j++)
        {
            ui->tableWidget_indent->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        }
        i++;
    }while(query.next());
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

void admin_show::show_camera_info()
{
    QString command = tr("select * from cameras;");
    //qDebug() <<"show_admin_info():" << command;
    QSqlQuery query(command);
    query.exec();
    int nRow = query.size();
    QSqlRecord sqlRecord = query.record();
    int nColumn = sqlRecord.count();
    ui->tableWidget_camera->setRowCount(nRow);
    ui->tableWidget_camera->setColumnCount(nColumn);
    int i=0;
    query.first();
    do{
        for(int j=0; j<nColumn; j++)
        {
            ui->tableWidget_camera->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
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


//查找按钮被点击后
void admin_show::on_pushButton_find_admin_clicked()
{
    dialog_find_admin->setModal(true);
    dialog_find_admin->show();
}

void admin_show::on_pushButton_add_custom_clicked()
{
    dialog_add_custom->setModal(true);
    dialog_add_custom->show();
}

//删除用户
void admin_show::on_pushButton_delete_custom_clicked()
{
    int current_row = ui->tableWidget_custom->currentRow();//表格中选中的行数。
    if(current_row == -1)
    {
        QMessageBox::about(this, "错误", "没有选中任何一条记录！");
        return;
    }
    QString custom_name = ui->tableWidget_custom->item(current_row, 0)->text();
    QString command = tr("delete from customs where user_name = \"%1\";").arg(custom_name);
    qDebug() << "command:" << command;
    QSqlQuery query(command);
    query.exec();

    //manage表中插入数据
    QString command_insert = tr("insert into update_user values(\"%1\", \"%2\", \"%3\", \"del\");").arg(Widget::admin_name).arg(ui->tableWidget_camera->item(current_row, 0)->text()).arg(QDateTime::currentDateTime().toTime_t());
    qDebug() << command_insert;
    QSqlQuery query_insert(command_insert);
    query_insert.exec();
    show_custom_info();
}

void admin_show::on_pushButton_alter_custom_clicked()
{
    int current_row = ui->tableWidget_custom->currentRow();//表格中选中的行数。
    //qDebug() << "current_row:" << current_row;
    if(current_row == -1)
    {
        QMessageBox::about(this, "错误", "没有选中任何一条记录！");
        return;
    }
    QString account = ui->tableWidget_custom->item(current_row, 0)->text();
    QString password = ui->tableWidget_custom->item(current_row, 1)->text();
    double balance = ui->tableWidget_custom->item(current_row, 2)->text().toDouble();
    QString sex = ui->tableWidget_custom->item(current_row, 3)->text();
    QString phone = ui->tableWidget_custom->item(current_row, 4)->text();

    dialog_edit_custom->setAllInfo(account, password, balance, sex, phone);
    dialog_edit_custom->setModal(true);
    dialog_edit_custom->show();
}

void admin_show::on_pushButton_find_custom_clicked()
{
    dialog_find_custom->setModal(true);
    dialog_find_custom->show();
}

void admin_show::on_pushButton_alter_indent_clicked()
{
    int current_row = ui->tableWidget_indent->currentRow();//表格中选中的行数。
    if(current_row == -1)
    {
        QMessageBox::about(this, "错误", "没有选中任何一条记录！");
        return;
    }
    QString order_no = ui->tableWidget_indent->item(current_row, 0)->text();
    QString account = ui->tableWidget_indent->item(current_row, 1)->text();
    QString camera_no = ui->tableWidget_indent->item(current_row, 2)->text();
    int rent_num = ui->tableWidget_indent->item(current_row, 3)->text().toInt();
    int price = ui->tableWidget_indent->item(current_row, 4)->text().toInt();
    unsigned int start_time = ui->tableWidget_indent->item(current_row, 5)->text().toInt();
    unsigned int rent_time = ui->tableWidget_indent->item(current_row, 6)->text().toInt();
    double rent_days = ui->tableWidget_indent->item(current_row, 7)->text().toDouble();

    double rent_charge = ui->tableWidget_indent->item(current_row, 8)->text().toDouble();
    double extra_charge = ui->tableWidget_indent->item(current_row, 9)->text().toDouble();
    double final_charge = ui->tableWidget_indent->item(current_row, 10)->text().toDouble();
//    QString rent_charge = ui->tableWidget_indent->item(current_row, 0)->text();
//    QString extra_charge = ui->tableWidget_indent->item(current_row, 0)->text();
//    QString final_charge = ui->tableWidget_indent->item(current_row, 0)->text();
    qDebug() << "rent_charge:" << rent_charge << extra_charge << final_charge;


    dialog_edit_indent->setModal(true);
    dialog_edit_indent->setAllInfo(order_no, account, camera_no, rent_num, price, start_time, rent_time, rent_days, rent_charge, extra_charge, final_charge);
    dialog_edit_indent->show();
}

//查找订单按钮
void admin_show::on_pushButton_find_indent_clicked()
{
    bool isOrder = ui->radioButton_indent_no->isChecked();
    bool isName = ui->radioButton_name->isChecked();
    bool isCamera = ui->radioButton_camera_no->isChecked();

    QString find_content = ui->lineEdit_content->text();

    QString command;
    if(isOrder)
    {
        command = tr("select * from my_indent where order_no = \"%1\";").arg(find_content);
    }
    else if (isName) {
        command = tr("select * from my_indent where user_name = \"%1\";").arg(find_content);
    }
    else if(isCamera) {
        command = tr("select * from my_indent where camera_no = \"%1\";").arg(find_content);
    }
    QSqlQuery query(command);
    query.exec();

    int nRow = query.size();
    QSqlRecord sqlRecord = query.record();
    int nColumn = sqlRecord.count();
    ui->tableWidget_indent->setRowCount(nRow);
    ui->tableWidget_indent->setColumnCount(nColumn);
    int i=0;
    query.first();
    do{
        for(int j=0; j<nColumn; j++)
        {
            ui->tableWidget_indent->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        }
        i++;
    }while(query.next());
}

void admin_show::on_pushButton_login_clicked()
{
    QString account = ui->lineEdit_account->text();
    QString password = ui->lineEdit_password->text();
    QString command;
    bool isAdmin = false;
    if(password != "")
    {
        isAdmin = true;
    }

    if(isAdmin)
    {
        //查询admins表中数据
        command = QString("select admin_password from admins where admin_name = \"%1\"").arg(account);
    }
    else
    {
        //查看是否有该用户
        command = QString("select * from customs where user_name = \"%1\"").arg(account);
    }
    QSqlQuery query(command);
    query.exec();
    query.first();
    if(isAdmin)
    {
        if(password != query.value(0).toString())
        {
            QMessageBox::about(this,"登录失败", "账号密码错误！");
            return;
        }
        //管理员登录成功
        Widget::admin_name = account;//当前管理员名字
        admin_show *s1 = new admin_show();
        s1->show();
        this->close();
    }
    else {
        if(0 == query.size())//查不到该用户名
        {
            QMessageBox::about(this,"登录失败", "没有该用户名！");
            return;
        }
        //用户登录成功
        Widget::user_name = account;//当前用户名字
        custom_show *s2 = new custom_show();
        s2->show();
        this->close();
    }

    //登录成功
}

void admin_show::on_pushButton_sort_clicked()
{
    bool isOrder = false;
    bool isRentNum = false;
    bool isRentDays = false;
    bool isRentCharge = false;
    bool isExtraCharge = false;
    bool isFinalCharge = false;

    QString command;

    /*if(ui->radioButton_sort_order->isChecked())
    {
        isOrder = true;
        command = tr("select * from my_indent order by order_no;");
    }
    else */
    if(ui->radioButton_sort_rent_num->isChecked())
    {
        isRentNum = true;
        command = tr("select * from my_indent order by rent_num;");
    }
    else if(ui->radioButton_sort_rent_days->isChecked())
    {
        isRentDays = true;
        command = tr("select * from my_indent order by rent_days;");
    }
    else if(ui->radioButton_sort_rent_charge->isChecked())
    {
        isRentCharge = true;
        command = tr("select * from my_indent order by rent_charge;");
    }
    else if(ui->radioButton_sort_extra_charge->isChecked())
    {
        isExtraCharge = true;
        command = tr("select * from my_indent order by extra_charge;");
    }
    else if(ui->radioButton_sort_final_charge->isChecked())
    {
        isFinalCharge = true;
        command = tr("select * from my_indent order by final_charge;");
    }
    else {
        QMessageBox::about(this, "错误", "不知道根据什么排序！");
        return;
    }

    QSqlQuery query(command);
    query.exec();

    int nRow = query.size();
    QSqlRecord sqlRecord = query.record();
    int nColumn = sqlRecord.count();
    ui->tableWidget_indent->setRowCount(nRow);
    ui->tableWidget_indent->setColumnCount(nColumn);
    int i=0;
    query.first();
    do{
        for(int j=0; j<nColumn; j++)
        {
            ui->tableWidget_indent->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        }
        i++;
    }while(query.next());

}


void admin_show::on_pushButton_show_indent_clicked()
{
    show_indent_info();
}

void admin_show::on_pushButton_show_camera_clicked()
{
    show_camera_info();
}

void admin_show::on_pushButton_add_camera_clicked()
{
    dialog_add_camera->setModal(true);
    dialog_add_camera->show();
}

void admin_show::on_pushButton_delete_camera_clicked()
{
    int current_row = ui->tableWidget_camera->currentRow();//表格中选中的行数。
    if(current_row == -1)
    {
        QMessageBox::about(this, "错误", "没有选中任何一条记录！");
        return;
    }
    QString custom_name = ui->tableWidget_camera->item(current_row, 0)->text();
    QString command = tr("delete from cameras where camera_no = \"%1\";").arg(custom_name);
    qDebug() << "command:" << command;
    QSqlQuery query(command);
    query.exec();
    //manage表中插入数据
    QString command_insert = tr("insert into manage values(\"%1\", \"%2\", \"%3\", \"del\");").arg(Widget::admin_name).arg(ui->tableWidget_camera->item(current_row, 0)->text()).arg(QDateTime::currentDateTime().toTime_t());
    qDebug() << command_insert;
    QSqlQuery query_insert(command_insert);
    query_insert.exec();

    show_camera_info();
}

void admin_show::on_pushButton_edit_camera_clicked()
{
    int current_row = ui->tableWidget_camera->currentRow();//表格中选中的行数。
    //qDebug() << "current_row:" << current_row;
    if(current_row == -1)
    {
        QMessageBox::about(this, "错误", "没有选中任何一条记录！");
        return;
    }
    QString no = ui->tableWidget_camera->item(current_row, 0)->text();
    QString name = ui->tableWidget_camera->item(current_row, 1)->text();
    int total = ui->tableWidget_camera->item(current_row, 2)->text().toInt();
    int rent = ui->tableWidget_camera->item(current_row, 3)->text().toInt();
    int price = ui->tableWidget_camera->item(current_row, 4)->text().toInt();
    Dialog_add_camera::edit = true;
    Dialog_add_camera *s = new Dialog_add_camera();
    connect(s, &Dialog_add_camera::want_to_refresh_camera_info, this, &admin_show::show_camera_info);
    s->setAllInfo(no, name, total, rent, price);
    s->setModal(true);
    s->show();
}

void admin_show::on_pushButton_find_camera_clicked()
{
    bool isNo = false;
    bool isName = false;
    QString content = ui->lineEdit_find_camera_content->text();
    QString command;
    if(ui->radioButton_manage_camera_no->isChecked())
    {
        isNo = true;
        command = tr("select * from cameras where camera_no = \"%1\";").arg(content);
    }
    else if(ui->radioButton_manage_camera_name->isChecked())
    {
        isName = true;
        command = tr("select * from cameras where name = \"%1\";").arg(content);
    }
    QSqlQuery query(command);
    query.exec();
    int nRow = query.size();
    QSqlRecord sqlRecord = query.record();
    int nColumn = sqlRecord.count();
    ui->tableWidget_camera->setRowCount(nRow);
    ui->tableWidget_camera->setColumnCount(nColumn);
    QStringList headers;
    headers << QStringLiteral("相机编号")<< QStringLiteral("相机型号")<<
               QStringLiteral("总量")<< QStringLiteral("已借出量")<< QStringLiteral("租金/天");
    ui->tableWidget_camera->setHorizontalHeaderLabels(headers);
    int i=0;
    query.first();
    do{
        for(int j=0; j<nColumn; j++)
        {
            ui->tableWidget_camera->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        }
        i++;
    }while(query.next());
}
