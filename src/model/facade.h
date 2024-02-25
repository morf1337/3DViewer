#ifndef FACADE_H
#define FACADE_H

#include "../view/scene.h"
#include "fileparcer.h"
#include "objtransform.h"

namespace s21 {
class Controller;
class Facade {
 public:
  // for singleton
  static Facade& getInstance() {
    static Facade instance;
    return instance;
  }

  void Initialize(FileParcer* f, ObjTransform* t) {
    parcer = f;
    transformer = t;
  }

  // connections
  void ConnectController(Controller* c);
  void RegisterSceneObserver(Scene* scene) { localObj.addObserver(scene); }

  //<-- to model
  void LoadObjFromFile(std::string fileName);
  void RotateModel(int rot, int coord_code);
  void ScaleModel(double val);
  void MoveModel(double val, int coord_code);

  //--> to controller
  void SetObjInfo();

 private:
  Facade() : control(nullptr), parcer(nullptr), transformer(nullptr) {}
  Controller* control;
  FileParcer* parcer;
  ObjTransform* transformer;
  ObjData localObj;
};
}  // namespace s21

#endif  // FACADE_H
