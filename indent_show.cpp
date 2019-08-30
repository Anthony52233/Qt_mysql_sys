#include "indent_show.h"
#include "ui_indent_show.h"
#include "custom_show.h"
#include <qdebug.h>
#include <QDateTime>
#include "widget.h"


indent_show::indent_show(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::indent_show)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);//定义为模式界面，当有此界面时，阻塞其他界面的响应。
    setOrderNo();
    setUserName();

    //设置默认归还时间属性
    ui->dateTimeEdit_rent_time->setMinimumDate(QDate::currentDate());
    ui->dateTimeEdit_rent_time->setDisplayFormat("yyyy/MM/dd");
    ui->dateTimeEdit_rent_time->setCalendarPopup(true);
    getRentDate();//使用这个函数为了初始化year这几个成员变量。


    //创建custom_show实例对象
    //custom_show* custom = new custom_show;//这里的custom对象不是发送sendCameraNo信号的对象，所以不触发。
    //connect(custom, SIGNAL(sendCameraNo(QString)), this, SLOT(setCameraNo(QString)));//custom发送操作正确信号，indent界面处理。
    connect(ui->pushButton_cancle, &QPushButton::clicked, this, &indent_show::close);
}

indent_show::~indent_show()
{
    delete ui;
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
