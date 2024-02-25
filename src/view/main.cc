#include <QApplication>

#include "../controller/controller.h"
#include "../model/facade.h"
#include "../model/fileparcer.h"
#include "view.h"

using namespace s21;

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  FileParcer parcer;
  ObjTransform trans;
  Facade& facade = Facade::getInstance();
  facade.Initialize(&parcer, &trans);
  view w;
  facade.RegisterSceneObserver(w.GetScene());
  Controller control(&facade, w.GetScene(), &w);
  facade.ConnectController(&control);
  w.ConnectController(&control);
  w.show();
  return a.exec();
}
