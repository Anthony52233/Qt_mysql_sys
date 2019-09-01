#ifndef ADMIN_SHOW_H
#define ADMIN_SHOW_H

#include <QWidget>
#include "dialog_add_admin.h"
#include "dialog_edit_admin.h"

namespace Ui {
class admin_show;
}

class admin_show : public QWidget
{
    Q_OBJECT

public:
    explicit admin_show(QWidget *parent = nullptr);
    ~admin_show();
    void show_admin_info();//显示管理员信息


public slots:
    void delete_admin();//删除管理员

private:
    Ui::admin_show *ui;
    Dialog_add_admin *dialog_add_admin;//添加按钮被点击时弹出此对话框。
    Dialog_edit_admin *dialog_edit_admin;

signals:
    void want_to_refresh_admin();
private slots:
    void on_pushButton_add_admin_clicked();
    void on_pushButton_alter_admin_clicked();
};

#endif // ADMIN_SHOW_H
