#include "dialog_edit_indent.h"
#include "ui_dialog_edit_indent.h"
#include <QDateTime>
#include <QSqlQuery>
#include <qdebug.h>

Dialog_edit_indent::Dialog_edit_indent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_edit_indent)
{
    ui->setupUi(this);
    //设置租借时间的显示格式
    ui->dateEdit_rent_time->setDisplayFormat("yyyy/MM/dd");
    ui->dateEdit_rent_time->setCalendarPopup(true);
    ui->dateEdit_start_time->setDisplayFormat("yyyy/MM/dd");
    ui->dateEdit_start_time->setCalendarPopup(true);
    //将下列lineEdit设为不可编辑
    ui->lineEdit_order_no->setReadOnly(true);
    ui->lineEdit_account->setReadOnly(true);
    //ui->lineEdit_camera_no->setReadOnly(true);
    //ui->lineEdit_rent_num->setReadOnly(true);
    //ui->lineEdit_price->setReadOnly(true);
    //ui->dateEdit_start_time->setReadOnly(true);
    ui->lineEdit_rent_days->setReadOnly(true);
    ui->lineEdit_rent_charge->setReadOnly(true);
    ui->lineEdit_final_charge->setReadOnly(true);
}

Dialog_edit_indent::~Dialog_edit_indent()
{
    delete ui;
}

void Dialog_edit_indent::setAllInfo(QString order_no, QString account, QString camera_no,
                                    int rent_num, int price, unsigned int start_time, unsigned int rent_time,
                                    double rent_days, double rent_charge, double extra_charge, double final_charge)
{
    /*
代码2.0，修改了开始和归还日期的显示
*/
    QDateTime rent_date = QDateTime::fromTime_t(rent_time);
    QDateTime start_date = QDateTime::fromTime_t(start_time);

    ui->lineEdit_order_no->setText(order_no);
    ui->lineEdit_account->setText(account);
    ui->lineEdit_camera_no->setText(camera_no);
    ui->lineEdit_rent_num->setText(QString::number(rent_num));
    ui->lineEdit_price->setText(QString::number(price));
//    ui->lineEdit_start_time->setText(QString::number(start_time));
//    ui->lineEdit_rent_time->setText(QString::number(rent_time));
    ui->dateEdit_start_time->setDateTime(start_date);
    ui->dateEdit_rent_time->setDateTime(rent_date);
    ui->lineEdit_rent_days->setText(QString::number(rent_days));
    ui->lineEdit_rent_charge->setText(QString::number(rent_charge,10,4));
    ui->lineEdit_extra_charge->setText(QString::number(extra_charge,10,4));
    ui->lineEdit_final_charge->setText(QString::number(final_charge,10,4));
}

void Dialog_edit_indent::on_pushButton_commit_clicked()
{
    //获取控件信息，update
    QString order_no = ui->lineEdit_order_no->text();
    QString account = ui->lineEdit_account->text();
    QString camera_no = ui->lineEdit_camera_no->text();
    int rent_num = ui->lineEdit_rent_num->text().toInt();
    int price = ui->lineEdit_price->text().toInt();
    QDateTime start_date = ui->dateEdit_start_time->dateTime();
    QDateTime rent_date = ui->dateEdit_rent_time->dateTime();
    double rent_days = ui->lineEdit_rent_days->text().toDouble();
    double rent_charge = ui->lineEdit_rent_charge->text().toDouble();
    double extra_charge = ui->lineEdit_extra_charge->text().toDouble();
    double final_charge = ui->lineEdit_final_charge->text().toDouble();

    QString start_time = QString::number(start_date.toTime_t());
    QString rent_time = QString::number(rent_date.toTime_t());

    QString command = tr("update indents set user_name = \"%1\", "
                          "camera_no = \"%2\", rent_num = %3, "
                          "start_time = \"%4\", rent_time = \"%5\", "
                          "extra_charge = %6 where order_no = \"%7\";").arg(account).arg(camera_no).arg(rent_num).arg(start_time).arg(rent_time).arg(extra_charge).arg(order_no);
    QSqlQuery query(command);
    qDebug() <<"update indent:" <<command;
    emit want_to_refresh_indent();
    this->close();
}
