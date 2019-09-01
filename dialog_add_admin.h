#ifndef DIALOG_ADD_ADMIN_H
#define DIALOG_ADD_ADMIN_H

#include <QDialog>

namespace Ui {
class Dialog_add_admin;
}

class Dialog_add_admin : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_add_admin(QWidget *parent = nullptr);
    ~Dialog_add_admin();

private slots:
    void on_pushButton_commit_clicked();

private:
    Ui::Dialog_add_admin *ui;

signals:
    void want_to_refresh_admin_info();
};

#endif // DIALOG_ADD_ADMIN_H
