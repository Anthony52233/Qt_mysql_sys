#include "dialog_edit_indent.h"
#include "ui_dialog_edit_indent.h"

Dialog_edit_indent::Dialog_edit_indent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_edit_indent)
{
    ui->setupUi(this);
}

Dialog_edit_indent::~Dialog_edit_indent()
{
    delete ui;
}

void Dialog_edit_indent::setAllInfo(QString order_no, QString account, QString camera_no,
                                    int rent_num, int price, unsigned int start_time, unsigned int rent_time,
                                    double rent_days, double rent_charge, double extra_charge, double final_charge)
{
    ui->lineEdit_order_no->setText(order_no);
    ui->lineEdit_account->setText(account);
    ui->lineEdit_camera_no->setText(camera_no);
    ui->lineEdit_rent_num->setText(QString::number(rent_num));
    ui->lineEdit_price->setText(QString::number(price));
    ui->lineEdit_start_time->setText(QString::number(start_time));
    ui->lineEdit_rent_time->setText(QString::number(rent_time));
    ui->lineEdit_rent_days->setText(QString::number(rent_days));
    ui->lineEdit_rent_charge->setText(QString::number(rent_charge,10,4));
    ui->lineEdit_extra_charge->setText(QString::number(extra_charge,10,4));
    ui->lineEdit_final_charge->setText(QString::number(final_charge,10,4));
}
