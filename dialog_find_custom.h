#ifndef DIALOG_FIND_CUSTOM_H
#define DIALOG_FIND_CUSTOM_H

#include <QDialog>

namespace Ui {
class Dialog_find_custom;
}

class Dialog_find_custom : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_find_custom(QWidget *parent = nullptr);
    ~Dialog_find_custom();

private slots:
    void on_pushButton_find_clicked();

private:
    Ui::Dialog_find_custom *ui;
};

#endif // DIALOG_FIND_CUSTOM_H
