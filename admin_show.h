#ifndef ADMIN_SHOW_H
#define ADMIN_SHOW_H

#include <QWidget>
#include "dialog_add_admin.h"
#include "dialog_edit_admin.h"
#include "dialog_find_admin.h"
#include "dialog_add_custom.h"
#include "dialog_edit_custom.h"
#include "dialog_find_custom.h"
#include "dialog_edit_indent.h"


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
    void show_custom_info();//显示用户信息
    void show_indent_info();//显示订单信息


public slots:
    void delete_admin();//删除管理员

private:
    Ui::admin_show *ui;
    Dialog_add_admin *dialog_add_admin;//添加按钮被点击时弹出此对话框。
    Dialog_edit_admin *dialog_edit_admin;
    Dialog_find_admin *dialog_find_admin;
    Dialog_add_custom *dialog_add_custom;
    Dialog_edit_custom *dialog_edit_custom;
    Dialog_find_custom *dialog_find_custom;
    Dialog_edit_indent *dialog_edit_indent;

signals:
    void want_to_refresh_admin();
private slots:
    void on_pushButton_add_admin_clicked();
    void on_pushButton_alter_admin_clicked();
    void on_pushButton_find_admin_clicked();
    void on_pushButton_add_custom_clicked();
    void on_pushButton_delete_custom_clicked();
    void on_pushButton_alter_custom_clicked();
    void on_pushButton_find_custom_clicked();
    void on_pushButton_alter_indent_clicked();
};

#endif // ADMIN_SHOW_H
