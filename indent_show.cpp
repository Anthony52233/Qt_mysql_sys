#include "indent_show.h"
#include "ui_indent_show.h"
#include "custom_show.h"
#include <qdebug.h>
#include <QDateTime>
#include "widget.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRecord>


indent_show::indent_show(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::indent_show)
{
    ui->setupUi(this);
    //setWindowModality(Qt::ApplicationModal);//定义为模式界面，当有此界面时，阻塞其他界面的响应。
    setOrderNo();
    setUserName();

    //设置默认归还时间属性
    ui->dateTimeEdit_rent_time->setMinimumDate(QDate::currentDate().addDays(1));
    ui->dateTimeEdit_rent_time->setDisplayFormat("yyyy/MM/dd");
    ui->dateTimeEdit_rent_time->setCalendarPopup(true);
    getRentDate();//使用这个函数为了初始化year这几个成员变量。

    //为租借数量设默认值
    ui->spinBox_num->setValue(1);

    ui->lineEdit_order_no->setReadOnly(true);
    ui->lineEdit_user_name->setReadOnly(true);
    ui->lineEdit_camera_no->setReadOnly(true);

   setWindowTitle("下单界面");

    //创建custom_show实例对象
    //custom_show* custom = new custom_show;//这里的custom对象不是发送sendCameraNo信号的对象，所以不触发。
    //connect(custom, SIGNAL(sendCameraNo(QString)), this, SLOT(setCameraNo(QString)));//custom发送操作正确信号，indent界面处理。
    connect(ui->pushButton_cancle, &QPushButton::clicked, this, &indent_show::close);
    //绑定提交按钮点击事件
    connect(ui->pushButton_cancle, SIGNAL(clicked()), this, SLOT(on_pushButton_submit_clicked()));
}

indent_show::~indent_show()
{
    delete ui;
}

void indent_show::on_pushButton_submit_clicked()
{
    //获取信息，打包成mysql语句，发送给mysql
    QString order_no = ui->lineEdit_order_no->text();
    QString user_name = Widget::user_name;
    int rent_num = ui->spinBox_num->value();
    QString cameras_no = ui->lineEdit_camera_no->text();
    //这里有一个问题，如果还的时间为当天，那么start_time比rent_time晚。。。
    QString start_time = QString::number(QDateTime::currentDateTime().toTime_t());
    QString rent_time = QString::number(ui->dateTimeEdit_rent_time->dateTime().toTime_t());
    int extra_charge = 0;
    //数值获取完毕
    //打包mysql语句
    //更新camereas表中的rent_num属性，先获取该相机已租量
    QString command_search_rent_num = tr("select rent_num, total_num from cameras where camera_no = \"%1\";").arg(cameras_no);
    QSqlQuery query_search_rent_num(command_search_rent_num);
    query_search_rent_num.exec();
    query_search_rent_num.first();
    int last_rent_num = query_search_rent_num.value(0).toInt();//查询到的已租量
    int last_total_num = query_search_rent_num.value(1).toInt();//查询到总量，一般为定值
    if(last_rent_num + rent_num > last_total_num)//已租赁的超过存货
    {
        QMessageBox::about(this, "错误", "该相机余量不足！");
        return;
    }
    //余量足，更新cameras表中的rent_num属性
    last_rent_num += rent_num;
    QString command_update_camera_num = tr("update cameras set rent_num = %1 where camera_no = \"%2\";").arg(last_rent_num).arg(cameras_no);
    qDebug() <<"command_update_camera_num:" << command_update_camera_num << "rent_num" << last_rent_num <<", total_num:" << last_total_num;
    QSqlQuery query_update_camera_num(command_update_camera_num);
    query_update_camera_num.exec();
    //余量更新完毕

    QString command = QString("insert into indents values(\"%1\", \"%2\", %3, \"%4\", \"%5\", \"%6\", %7);").arg(order_no).arg(user_name).arg(rent_num).arg(cameras_no).arg(start_time).arg(rent_time).arg(extra_charge);
    qDebug() << command;
    QSqlQuery query(command);
    //query.exec();
    if(0 == query.exec())
    {
        QMessageBox::about(this,"成功", "订单提交成功！");
    }

    //往brower表中插入记录
    QString command_insert = tr("insert into browse values(\"%1\", \"%2\", \"%3\");").arg(user_name).arg(cameras_no).arg(order_no);
    QSqlQuery query_insert(command_insert);
    query_insert.exec();

    emit want_to_refresh_indent();//触发一个刷新我的订单的信号。在custom_show界面处理该信号
    emit want_to_refresh_camera();//因为rent_num量改变，刷新下相机信息。
    this->close();
}

void indent_show::getRentDate()
{
    qDebug() << ui->dateTimeEdit_rent_time->date();
    year = QString::number(ui->dateTimeEdit_rent_time->date().year(),10);
    month = QString::number(ui->dateTimeEdit_rent_time->date().month(),10);
    day = QString::number(ui->dateTimeEdit_rent_time->date().day(),10);
}

void indent_show::setUserName()
{
    qDebug() << Widget::user_name;
    QString user_name = Widget::user_name;
    ui->lineEdit_user_name->setText(user_name);
}

void indent_show::setOrderNo()
{
    QDateTime time = QDateTime::currentDateTime();
    unsigned int timeT = time.toTime_t();
    QString t = QString::number(timeT, 10);
    ui->lineEdit_order_no->setText(t);
}

void indent_show::setCameraNo(QString camera_no)
{
    qDebug() << camera_no;
    ui->lineEdit_camera_no->setText(camera_no);
}
