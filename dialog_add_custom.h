#ifndef DIALOG_ADD_CUSTOM_H
#define DIALOG_ADD_CUSTOM_H

#include <QDialog>

namespace Ui {
class Dialog_add_custom;
}

class Dialog_add_custom : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_add_custom(QWidget *parent = nullptr);
    ~Dialog_add_custom();

private slots:
    void on_pushButton_commit_clicked();

private:
    Ui::Dialog_add_custom *ui;

signals:
    void want_to_refresh_custom_info();
};

#endif // DIALOG_ADD_CUSTOM_H
