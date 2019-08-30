#ifndef INDENT_SHOW_H
#define INDENT_SHOW_H

#include <QWidget>
#include <QDate>

namespace Ui {
class indent_show;
}

class indent_show : public QWidget
{
    Q_OBJECT

public:
    explicit indent_show(QWidget *parent = nullptr);
    ~indent_show();
    void setCameraNo(QString);//利用此公共函数，接受custom_show界面传过来的camera_no值设置indent_show界面的camera_no属性。
    void setOrderNo();//根据时间戳生成随机订单编号。
    void setUserName();
    void getRentDate();//获取归还时间，初始化变量year,month,day。这个函数放到提交按钮里。

public:
    QString year;
    QString month;
    QString day;
private:
    Ui::indent_show *ui;

};

#endif // INDENT_SHOW_H
