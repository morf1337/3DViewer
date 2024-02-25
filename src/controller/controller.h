#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QColorDialog>

#include "../model/facade.h"
#include "../view/scene.h"

namespace s21 {
class view;
class Controller {
 public:
  Controller(Facade* f, Scene* s, view* w)
      : facade(f), scene(s), mainwindow(w) {}
  //<-- to facade&model
  void LoadObjFromFile(std::string fileName);
  void RotateModel(int rot, int coord_code);
  void ScaleModel(double val);
  void MoveModel(double val, int coord_code);

  //--> to scene
  void SetParameter(const std::string& parameter, QVariant value);
  QVariant GetParameter(const std::string& parameter);

  //--> to view
  void SetObjInfo(int vertexes, int facets);

 private:
  Facade* facade;
  Scene* scene;
  view* mainwindow;
};
}  // namespace s21
#endif  // CONTROLLER_H
