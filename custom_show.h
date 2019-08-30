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
    void show_cam_info();//显示相机的信息。

public slots:
    void process_indent_info();//处理客户选择的订单信息。

private:
    Ui::custom_show *ui;

signals:
    void sendCameraNo(QString camera_no);
};

#endif // CUSTOM_SHOW_H
