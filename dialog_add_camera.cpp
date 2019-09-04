#include "dialog_add_camera.h"
#include "ui_dialog_add_camera.h"
#include <QSqlQuery>
#include <qdebug.h>
#include "widget.h"
#include <QDateTime>

bool Dialog_add_camera::edit = false;//初始化为假

Dialog_add_camera::Dialog_add_camera(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_add_camera)
{
    ui->setupUi(this);

    if(edit)//edit调用
    {
        //把rent_num显示出来
        ui->label_4->setVisible(true);
        ui->lineEdit_add_camera_rent_num->setVisible(true);
        ui->lineEdit_add_camera_no->setReadOnly(true);
        ui->lineEdit_add_camera_name->setReadOnly(true);
    }
    else {//add使用，rent_num没必要显示出来
        ui->label_4->setVisible(false);
        ui->lineEdit_add_camera_rent_num->setVisible(false);
    }
    //edit = false;
}

Dialog_add_camera::~Dialog_add_camera()
{
    delete ui;
}

void Dialog_add_camera::on_pushButto_add_camera_clicked()
{
    QString no = ui->lineEdit_add_camera_no->text();
    QString name = ui->lineEdit_add_camera_name->text();
    int total = ui->lineEdit_add_camera_total_num->text().toInt();
    int rent = ui->lineEdit_add_camera_rent_num->text().toInt();
    int price = ui->lineEdit_add_camera_price->text().toInt();

    QString command;
    if(edit)
    {
        command = tr("update cameras set name = \"%2\", total_num = %3, rent_num = %4, price = %5 where camera_no = \"%1\";").arg(no).arg(name).arg(total).arg(rent).arg(price);
        //manage表中插入数据
        QString command_insert = tr("insert into manage values(\"%1\", \"%2\", \"%3\", \"edit\");").arg(Widget::admin_name).arg(no).arg(QDateTime::currentDateTime().toTime_t());
        qDebug() << command_insert;
        QSqlQuery query_insert(command_insert);
        query_insert.exec();
    }
    else {

        command = tr("insert into cameras values(\"%1\", \"%2\", %3, 0, %4);").arg(no).arg(name).arg(total).arg(price);
    }
    qDebug() << "add&edit command" << command;
    QSqlQuery query(command);
//    //manage表中插入数据
//    QString command_insert = tr("insert into manage values(\"%1\", \"%2\", \"%3\", \"add\");").arg(Widget::admin_name).arg(no).arg(QDateTime::currentDateTime().toTime_t());
//    qDebug() << command_insert;
//    QSqlQuery query_insert(command);

    emit want_to_refresh_camera_info();
    this->close();

}

void Dialog_add_camera::setAllInfo(QString no, QString name, int total, int rent, int price )
{
    ui->lineEdit_add_camera_no->setText(no);
    ui->lineEdit_add_camera_name->setText(name);
    ui->lineEdit_add_camera_total_num->setText(QString::number(total));
    ui->lineEdit_add_camera_rent_num->setText(QString::number(rent));
    ui->lineEdit_add_camera_price->setText(QString::number(price));
}
