#ifndef VIEW_H
#define VIEW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>
#include "qgifimage.h"

#include "../controller/controller.h"
#include "scene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class view;
}
QT_END_NAMESPACE

namespace s21 {
class view : public QMainWindow {
  Q_OBJECT

 public:
  view(QWidget *parent = nullptr);
  void ConnectController(Controller *c);
  Scene *GetScene();
  void SetObjInfo(int vertexes, int facets);
  void ResetViewParams();
  void SaveSettings();
  void LoadSettings();
  ~view();
private:
  void gif_saving();
  void create_screen();

 private slots:
  void on_openFile_clicked();
  void on_X_movement_SpinBox_valueChanged(double arg1);
  void on_Y_movement_SpinBox_valueChanged(double arg1);
  void on_Y_rotation_SpinBox_valueChanged(double arg1);
  void on_Z_movement_SpinBox_valueChanged(double arg1);
  void on_X_rotation_SpinBox_valueChanged(double arg1);
  void on_Z_rotation_SpinBox_valueChanged(double arg1);
  void on_Model_Zoom_spinBox_valueChanged(int arg1);
  void on_BGColorChange_pushButton_clicked();
  void on_LinesColorChange_pushButton_clicked();
  void on_PointsColorChange_pushButton_clicked();
  void on_comboBox_projection_type_activated(int index);
  void on_comboBox_vertices_type_activated(int index);
  void on_spinBox_edges_thickness_valueChanged(int arg1);
  void on_spinBox_vertices_thickness_valueChanged(int arg1);
  void on_comboBox_edges_type_activated(int index);
  void on_SaveSettings_clicked();
  void on_LoadSettings_clicked();

  void on_SaveImage_clicked();

  void on_SaveGif_clicked();

private:
  Ui::view *ui;
  Controller *control;
  double moving_x = 0, moving_y = 0, moving_z = 0, rotating_x = 0,
         rotating_y = 0, rotating_z = 0;
  int zooming = 100;
  QString settingsFile;
  QSettings *settings;
  QVector<QImage> images_arr;
  QTimer *gif_timer;
  double time_val = 0;

};
}  // namespace s21

#endif  // VIEW_H
