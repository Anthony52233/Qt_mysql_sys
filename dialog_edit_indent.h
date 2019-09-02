#ifndef DIALOG_EDIT_INDENT_H
#define DIALOG_EDIT_INDENT_H

#include <QDialog>

namespace Ui {
class Dialog_edit_indent;
}

class Dialog_edit_indent : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_edit_indent(QWidget *parent = nullptr);
    ~Dialog_edit_indent();
    void setAllInfo(QString, QString, QString, int, int, unsigned int, unsigned int, double, double, double, double);

private:
    Ui::Dialog_edit_indent *ui;
};

#endif // DIALOG_EDIT_INDENT_H
