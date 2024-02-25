#include "controller.h"

#include "../view/view.h"

using namespace s21;

void Controller::LoadObjFromFile(std::string fileName) {
  facade->LoadObjFromFile(fileName);
}

void Controller::SetObjInfo(int vertexes, int facets) {
  mainwindow->SetObjInfo(vertexes, facets);
}

void Controller::RotateModel(int rot, int coord_code) {
  facade->RotateModel(rot, coord_code);
}
void Controller::ScaleModel(double val) { facade->ScaleModel(val); }

void Controller::MoveModel(double val, int coord_code) {
  facade->MoveModel(val, coord_code);
}

void Controller::SetParameter(const std::string &parameter, QVariant value) {
  scene->SetParameter(parameter, value);
}

QVariant Controller::GetParameter(const std::string &parameter) {
  return scene->GetParameter(parameter);
}
