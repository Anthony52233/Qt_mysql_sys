#ifndef DIALOG_FIND_ADMIN_H
#define DIALOG_FIND_ADMIN_H

#include <QDialog>

namespace Ui {
class Dialog_find_admin;
}

class Dialog_find_admin : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_find_admin(QWidget *parent = nullptr);
    ~Dialog_find_admin();

private slots:
    void on_pushButton_find_clicked();

private:
    Ui::Dialog_find_admin *ui;
};

#endif // DIALOG_FIND_ADMIN_H
