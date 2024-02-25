#include "view.h"

using s21::Scene;
#include "ui_view.h"

using namespace s21;

view::view(QWidget* parent) : QMainWindow(parent), ui(new Ui::view) {
  ui->setupUi(this);
  settingsFile = QApplication::applicationDirPath() + "/3DViewer.ini";
  settings = new QSettings(settingsFile, QSettings::IniFormat);
  gif_timer = new QTimer(0);
  connect(gif_timer, &QTimer::timeout, this, &view::create_screen);
}

view::~view() { delete ui; }

void view::ConnectController(Controller* c) { control = c; }

Scene* view::GetScene() { return ui->sceneWidget; }

void view::on_openFile_clicked() {
  ResetViewParams();
  QString file =
      QFileDialog::getOpenFileName(this, "Выберите файл", ".", tr(" (*.obj)"));
  std::string fileStr = file.toStdString();
  control->LoadObjFromFile(fileStr);
  ui->file_name_2->setText(QFileInfo(file).fileName());
}

void view::SetObjInfo(int vertexes, int facets) {
  ui->count_vertexes_2->setText(QString::number(vertexes));
  ui->count_facets_2->setText(QString::number(facets));
}

void view::on_X_movement_SpinBox_valueChanged(double arg1) {
  control->MoveModel(arg1 - moving_x, 0);
  moving_x = arg1;
}

void view::on_Y_movement_SpinBox_valueChanged(double arg1) {
  control->MoveModel(arg1 - moving_y, 1);
  moving_y = arg1;
}

void view::on_Z_movement_SpinBox_valueChanged(double arg1) {
  control->MoveModel(arg1 - moving_z, 2);
  moving_z = arg1;
}

void view::on_X_rotation_SpinBox_valueChanged(double arg1) {
  control->RotateModel(arg1 - rotating_x, 0);
  rotating_x = arg1;
}

void view::on_Y_rotation_SpinBox_valueChanged(double arg1) {
  control->RotateModel(arg1 - rotating_y, 1);
  rotating_y = arg1;
}

void view::on_Z_rotation_SpinBox_valueChanged(double arg1) {
  control->RotateModel(arg1 - rotating_z, 2);
  rotating_z = arg1;
}

void view::on_Model_Zoom_spinBox_valueChanged(int arg1) {
  double mult = arg1 / (float)zooming;
  control->ScaleModel(mult);
  zooming = arg1;
}

void view::on_BGColorChange_pushButton_clicked() {
  control->SetParameter("backColor", QColorDialog::getColor(Qt::gray));
}

void view::on_LinesColorChange_pushButton_clicked() {
  control->SetParameter("lineColor", QColorDialog::getColor(Qt::gray));
}

void view::on_PointsColorChange_pushButton_clicked() {
  control->SetParameter("pointColor", QColorDialog::getColor(Qt::gray));
}

void view::on_comboBox_projection_type_activated(int index) {
  control->SetParameter("projType", index);
}

void view::on_comboBox_edges_type_activated(int index) {
  control->SetParameter("lineType", index);
}

void view::on_comboBox_vertices_type_activated(int index) {
  control->SetParameter("pointType", index);
}

void view::on_spinBox_edges_thickness_valueChanged(int arg1) {
  control->SetParameter("lineThickness", arg1);
}

void view::on_spinBox_vertices_thickness_valueChanged(int arg1) {
  control->SetParameter("pointThickness", arg1);
}

void view::on_SaveSettings_clicked() { SaveSettings(); }

void view::SaveSettings() {
  settings->setValue("projType", control->GetParameter("projType").toInt());
  settings->setValue("lineType", control->GetParameter("lineType").toInt());
  settings->setValue("lineThickness",
                     control->GetParameter("lineThickness").toInt());
  settings->setValue("pointType", control->GetParameter("pointType").toInt());
  settings->setValue("pointThickness",
                     control->GetParameter("pointThickness").toInt());
  settings->setValue("backColor",
                     control->GetParameter("backColor").value<QColor>());
  settings->setValue("lineColor",
                     control->GetParameter("lineColor").value<QColor>());
  settings->setValue("pointColor",
                     control->GetParameter("pointColor").value<QColor>());
}

void view::LoadSettings() {
  control->SetParameter("projType", settings->value("projType").toInt());
  control->SetParameter("lineType", settings->value("lineType").toInt());
  control->SetParameter("lineThickness",
                        settings->value("lineThickness").toInt());
  control->SetParameter("pointType", settings->value("pointType").toInt());
  control->SetParameter("pointThickness",
                        settings->value("pointThickness").toInt());
  control->SetParameter("backColor",
                        settings->value("backColor").value<QColor>());
  control->SetParameter("lineColor",
                        settings->value("lineColor").value<QColor>());
  control->SetParameter("pointColor",
                        settings->value("pointColor").value<QColor>());

  ui->comboBox_edges_type->setCurrentIndex(settings->value("lineType").toInt());
  ui->comboBox_projection_type->setCurrentIndex(
      settings->value("projType").toInt());
  ui->comboBox_vertices_type->setCurrentIndex(
      settings->value("pointType").toInt());
  ui->spinBox_vertices_thickness->setValue(
      settings->value("pointThickness").toInt());
  ui->spinBox_edges_thickness->setValue(
      settings->value("lineThickness").toInt());
}

void view::ResetViewParams() {
  moving_x = moving_y = moving_z = rotating_x = rotating_y = rotating_z = 0;
  ui->X_movement_SpinBox->setValue(0);
  ui->Y_movement_SpinBox->setValue(0);
  ui->Z_movement_SpinBox->setValue(0);
  ui->X_rotation_SpinBox->setValue(0);
  ui->Y_rotation_SpinBox->setValue(0);
  ui->Z_rotation_SpinBox->setValue(0);
  ui->Model_Zoom_spinBox->setValue(100);
}

void view::on_LoadSettings_clicked() { LoadSettings(); }

void view::on_SaveImage_clicked() {
  QFileDialog file_dialog_photo(this);
  QString f_name_photo = file_dialog_photo.getSaveFileName(
      this, "Save as...", QDir::currentPath(), "BMP (*.bmp);; JPEG (*.jpeg)");
  QFile file(f_name_photo);
  file.open(QIODevice::WriteOnly);
  QRect rect(0, 0, ui->sceneWidget->width(), ui->sceneWidget->height());
  QPixmap pixmap = ui->sceneWidget->grab(rect);
  pixmap.copy(rect);
  pixmap.toImage().save(&file, "jpg");
  QString q_command_line = "open " + f_name_photo;
  QByteArray temp = q_command_line.toLocal8Bit();
  char* command_line = temp.data();
  system(command_line);
}

void view::on_SaveGif_clicked() {
  gif_timer->start(100);
  create_screen();
}

void view::gif_saving() {
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Save screenshot"), "",
      tr("GIF screenshot (*.gif);;GIF screenshot (*.gif)"));
  QGifImage gif(QSize(640, 480));

  gif.setDefaultTransparentColor(Qt::black);
  gif.setDefaultDelay(100);

  for (QVector<QImage>::Iterator img = images_arr.begin();
       img != images_arr.end(); ++img) {
    gif.addFrame(*img);
  }

  gif.save(fileName);
  images_arr.clear();
  ui->GifTimer_label->clear();
  time_val = 0;
}

void view::create_screen() {
  if (time_val < 4.9) {
    images_arr.push_back(ui->sceneWidget->grab().toImage().scaled(
        640, 480, Qt::IgnoreAspectRatio));
    time_val += 0.1;
    ui->GifTimer_label->setText(QString::number(time_val));
  } else {
    gif_saving();
    gif_timer->stop();
  }
}
