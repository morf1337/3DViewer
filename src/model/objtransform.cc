#include "objtransform.h"

using namespace s21;

void ObjTransform::RotateModel(ObjData& obj, int rot, int coord_code) {
  double rad = rot * PI / 180;
  double s = sin(rad), c = cos(rad), x1 = 0, y1 = 0, z1 = 0;
  std::vector<double> modifiedVertexes = obj.GetVertexesArr();

  for (int i = 0; i < obj.GetVertexesNum() * 3; i += 3) {
    x1 = modifiedVertexes[i];
    y1 = modifiedVertexes[i + 1];
    z1 = modifiedVertexes[i + 2];

    if (coord_code == 0) {
      modifiedVertexes[i + 1] = y1 * c - s * z1;
      modifiedVertexes[i + 2] = y1 * s + c * z1;
    } else if (coord_code == 2) {
      modifiedVertexes[i] = x1 * c - s * y1;
      modifiedVertexes[i + 1] = x1 * s + c * y1;
    } else if (coord_code == 1) {
      modifiedVertexes[i] = x1 * c + s * z1;
      modifiedVertexes[i + 2] = -x1 * s + c * z1;
    }
  }

  obj.SetVertexes(modifiedVertexes);
}

void ObjTransform::MoveModel(ObjData& obj, double val, int coord_code) {
  std::vector<double> modifiedVertexes = obj.GetVertexesArr();

  for (int i = 0; i < obj.GetVertexesNum() * 3; i += 3) {
    modifiedVertexes[i + coord_code] += val;
  }

  obj.SetVertexes(modifiedVertexes);
}

void ObjTransform::ScaleModel(ObjData& obj, double val) {
  std::vector<double> modifiedVertexes = obj.GetVertexesArr();

  for (int i = 0; i < obj.GetVertexesNum() * 3; ++i) {
    modifiedVertexes[i] *= val;
  }

  obj.SetVertexes(modifiedVertexes);
}
