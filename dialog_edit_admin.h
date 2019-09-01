#ifndef DIALOG_EDIT_ADMIN_H
#define DIALOG_EDIT_ADMIN_H

#include <QDialog>

namespace Ui {
class Dialog_edit_admin;
}

class Dialog_edit_admin : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_edit_admin(QWidget *parent = nullptr);
    ~Dialog_edit_admin();
    void setAccount(QString);
    void setPassword(QString);

private slots:
    void on_pushButton_commit_clicked();

private:
    Ui::Dialog_edit_admin *ui;

signals:
    void want_to_refresh_admin_info();
};

#endif // DIALOG_EDIT_ADMIN_H
