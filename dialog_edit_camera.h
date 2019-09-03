#ifndef DIALOG_EDIT_CAMERA_H
#define DIALOG_EDIT_CAMERA_H

#include <QDialog>

namespace Ui {
class Dialog_edit_camera;
}

class Dialog_edit_camera : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_edit_camera(QWidget *parent = nullptr);
    ~Dialog_edit_camera();

private:
    Ui::Dialog_edit_camera *ui;
};

#endif // DIALOG_EDIT_CAMERA_H
