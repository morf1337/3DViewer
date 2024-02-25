#include "facade.h"

#include "../controller/controller.h"

using namespace s21;

void Facade::ConnectController(Controller* c) { control = c; }

void Facade::LoadObjFromFile(std::string fileName) {
  parcer->ReadFile(localObj, fileName);
  SetObjInfo();
}

void Facade::SetObjInfo() {
  control->SetObjInfo(localObj.GetVertexesNum(), localObj.GetFacetsNum());
}

void Facade::RotateModel(int rot, int coord_code) {
  transformer->RotateModel(localObj, rot, coord_code);
}

void Facade::ScaleModel(double val) { transformer->ScaleModel(localObj, val); }

void Facade::MoveModel(double val, int coord_code) {
  transformer->MoveModel(localObj, val, coord_code);
}
