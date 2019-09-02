#ifndef DIALOG_EDIT_CUSTOM_H
#define DIALOG_EDIT_CUSTOM_H

#include <QDialog>

namespace Ui {
class Dialog_edit_custom;
}

class Dialog_edit_custom : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_edit_custom(QWidget *parent = nullptr);
    ~Dialog_edit_custom();
    void setAllInfo(QString, QString, double, QString, QString);//初始化所有信息

private slots:
    void on_pushButton_commit_clicked();

private:
    Ui::Dialog_edit_custom *ui;

signals:
    void want_to_refresh_custom();
};

#endif // DIALOG_EDIT_CUSTOM_H
