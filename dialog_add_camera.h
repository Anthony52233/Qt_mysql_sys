#ifndef DIALOG_ADD_CAMERA_H
#define DIALOG_ADD_CAMERA_H

#include <QDialog>

namespace Ui {
class Dialog_add_camera;
}

class Dialog_add_camera : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_add_camera(QWidget *parent = nullptr);
    ~Dialog_add_camera();
    void setAllInfo(QString, QString, int, int, int);
    static bool edit;//为真，edit作用，默认假

private slots:
    void on_pushButto_add_camera_clicked();

private:
    Ui::Dialog_add_camera *ui;

signals:
    void want_to_refresh_camera_info();
};

#endif // DIALOG_ADD_CAMERA_H
