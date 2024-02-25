#ifndef SCENE_H
#define SCENE_H

#define GL_SILENCE_DEPRECATION
#include <QColorDialog>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <iostream>

#include "../model/objdata.h"

namespace s21 {
class Scene : public QOpenGLWidget,
              protected QOpenGLFunctions,
              public Observer {
  Q_OBJECT
 public:
  Scene(QWidget *parent = nullptr);
  void LoadObjToScene(const std::vector<double> &v, const std::vector<int> &i);
  void SetParameter(const std::string &parameter, QVariant value);
  QVariant GetParameter(const std::string &parameter);
  virtual void handleUpdate(const std::vector<double> &vertexes,
                            const std::vector<int> &indexes) override;

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  void DrawObjModel();

 private:
  bool isObjLoaded = false, isOrtho = false;
  std::vector<double> vertexesInScene;
  std::vector<int> indexesInScene;
  QColor backColor, lineColor, pointColor;
  int lineType, pointType, lineThickness, pointThickness;
};
}  // namespace s21

#endif  // SCENE_H
