#include "dialog_edit_camera.h"
#include "ui_dialog_edit_camera.h"

Dialog_edit_camera::Dialog_edit_camera(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_edit_camera)
{
    ui->setupUi(this);
}

Dialog_edit_camera::~Dialog_edit_camera()
{
    delete ui;
}
