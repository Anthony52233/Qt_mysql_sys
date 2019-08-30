#include "custom_show.h"
#include "ui_custom_show.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include "indent_show.h"
#include <QMessageBox>

custom_show::custom_show(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::custom_show)
{
    ui->setupUi(this);
    show_cam_info();//在创建该页面时就更新表格中的数据
    connect(ui->pushButton_place_order, &QPushButton::clicked, this, &custom_show::process_indent_info);
    //按下下单按钮，就出现indent_show界面
    //indent_show* s = new indent_show;
    //connect(ui->pushButton_place_order, SIGNAL(clicked()));
}

custom_show::~custom_show()
{
    delete ui;
}

void custom_show::process_indent_info()
{
    //获取客户选中的相机信息
    //先默认一次只能下单一个相机吧。
    QList<QTableWidgetItem*> items = ui->tableWidget_browse->selectedItems();
    if(items.size() == 0)
    {
        QMessageBox::about(this, "错误！", "你没有选中相机编号！");
        return;
    }
    QTableWidgetItem* item = items.at(0);
    QString camera_no = item->text();//这里获得相机编号
    qDebug() << camera_no;
    //触发相机编号信号，好让indent_show界面接收到相机编号信息，用于其界面提交按钮发送命令到数据库。

    //显示订单界面，也可以说成跳转到订单界面，不过是非模式界面。
    indent_show* s = new indent_show;
    s->setCameraNo(camera_no);
    s->show();
}


void custom_show::show_cam_info()
{
    QString command = "select * from cameras";
    QSqlQuery query(command);
    int nRow = query.size();
    QSqlRecord sqlRecord = query.record();
    int nColumn = sqlRecord.count();
    ui->tableWidget_browse->setColumnCount(nColumn);
    ui->tableWidget_browse->setRowCount(nRow);
    QStringList headers;
    headers << QStringLiteral("相机编号")<< QStringLiteral("相机型号")<< QStringLiteral("总量")<< QStringLiteral("已借出量")<< QStringLiteral("租金/天");
    ui->tableWidget_browse->setHorizontalHeaderLabels(headers);
    int i = 0;
    query.first();
    do{
        for (int j=0; j<nColumn; j++)
            ui->tableWidget_browse->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        i++;
    }while(query.next());
}
