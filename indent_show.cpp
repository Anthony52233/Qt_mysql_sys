#include "indent_show.h"
#include "ui_indent_show.h"
#include "custom_show.h"
#include <qdebug.h>
#include <QDateTime>
#include "widget.h"
#include <QSqlQuery>
#include <QMessageBox>


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
    QString command = QString("insert into indents values(\"%1\", \"%2\", %3, \"%4\", \"%5\", \"%6\", %7);").arg(order_no).arg(user_name).arg(rent_num).arg(cameras_no).arg(start_time).arg(rent_time).arg(extra_charge);
    qDebug() << command;
    QSqlQuery query(command);
    //query.exec();
    if(0 == query.exec())
    {
        QMessageBox::about(this,"成功", "订单提交成功！");
    }
    emit want_to_refresh_indent();//触发一个刷新我的订单的信号。在custom_show界面处理该信号
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
