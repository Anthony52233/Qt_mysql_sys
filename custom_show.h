#ifndef CUSTOM_SHOW_H
#define CUSTOM_SHOW_H

#include <QWidget>

namespace Ui {
class custom_show;
}

class custom_show : public QWidget
{
    Q_OBJECT

public:
    explicit custom_show(QWidget *parent = nullptr);
    ~custom_show();


public slots:
    void process_indent_info();//处理客户选择的订单信息。
    //void on_tableWidget_indent_clicked();//当我的订单页面被选中时调用此函数。（废）
    void show_indent_info();//显示客户订单信息。
    void show_cam_info();//显示相机的信息。
    void process_clearing();
    void show_balance();//显示当前用户的余额

private:
    Ui::custom_show *ui;

signals:
    void sendCameraNo(QString camera_no);
    void want_to_refresh_indent();
private slots:
    void on_pushButton_login_clicked();
    void on_pushButton_sort_clicked();
    void on_pushButton_find_clicked();
    void on_pushButton_show_clicked();
    void on_pushButton_place_order_clicked();
};

#endif // CUSTOM_SHOW_H
