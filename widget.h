#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    int login();//连接数据库
    static QString user_name;
    static QString admin_name;


public slots:
    void process_login_info();//处理登录信息，验证账户密码。

private:
    Ui::Widget *ui;

signals:
    //void success_to_login();//账号密码正确，登录成功触发此信号
};

#endif // WIDGET_H
