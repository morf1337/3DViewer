#ifndef OBJTRANSFORM_H
#define OBJTRANSFORM_H

#define PI 3.141592

#include <cmath>

#include "objdata.h"

namespace s21 {
class ObjTransform {
 public:
  // coord code -- rotate around: 0 - X, 1 - Y, 2 - Z
  void RotateModel(ObjData& obj, int rot, int coord_code);
  void ScaleModel(ObjData& obj, double val);
  void MoveModel(ObjData& obj, double val, int coord_code);
};
}  // namespace s21

#endif  // OBJTRANSFORM_H
