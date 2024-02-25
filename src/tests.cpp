#include "gtest/gtest.h"
#include "model/fileparcer.h"
#include "model/objdata.h"
#include "model/objtransform.h"

namespace s21 {

class ObjFileLoadTest : public ::testing::Test {
 protected:
  ObjData obj_f;
  FileParcer parcer;

  void SetUp() override { parcer.ReadFile(obj_f, "./obj/cube.obj"); }
};

class ObjTransformTest : public ::testing::Test {
 protected:
  ObjTransform transformer;
  ObjData obj;

  void SetUp() override {
    std::vector<double> vertexes = {0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0,
                                    0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1};
    obj.SetVertexes(vertexes);
    obj.SetVertexesNum(8);
  }
};

TEST_F(ObjFileLoadTest, LoadObjFileTest) {
  EXPECT_EQ(obj_f.GetVertexesNum(), 8);  // вершины
  EXPECT_EQ(obj_f.GetFacetsNum(), 12);   // поверхности
}

TEST_F(ObjTransformTest, RotateModel90DegreesAroundZTest) {
  transformer.RotateModel(obj, 90, 2);

  auto& vertexes = obj.GetVertexesArr();

  // Предположим, что после поворота на 90 градусов вокруг оси Z, вершины куба
  // изменятся следующим образом:
  std::vector<double> expected_vertexes = {0, 0,  0,  0, 1, 0,  -1, 1,
                                           0, -1, 0,  0, 0, 0,  1,  0,
                                           1, 1,  -1, 1, 1, -1, 0,  1};

  // Проверяем все вершины
  for (size_t i = 0; i < vertexes.size(); ++i) {
    EXPECT_NEAR(vertexes[i], expected_vertexes[i], 1e-5);
  }
}

TEST_F(ObjTransformTest, ScaleModelTest) {
  transformer.ScaleModel(obj, 2.0);

  auto& vertexes = obj.GetVertexesArr();

  // Предположим, что после масштабирования вершины куба изменятся следующим
  // образом:
  std::vector<double> expected_vertexes = {0, 0, 0, 2, 0, 0, 2, 2, 0, 0, 2, 0,
                                           0, 0, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2};

  // Проверяем все вершины
  for (size_t i = 0; i < vertexes.size(); ++i) {
    EXPECT_DOUBLE_EQ(vertexes[i], expected_vertexes[i]);
  }
}

TEST_F(ObjTransformTest, MoveModelTest) {
  transformer.MoveModel(obj, 2.0, 1);

  auto& vertexes = obj.GetVertexesArr();

  // Предположим, что после перемещения на 2 единицы по оси Y, вершины куба
  // изменятся следующим образом:
  std::vector<double> expected_vertexes = {0, 2, 0, 1, 2, 0, 1, 3, 0, 0, 3, 0,
                                           0, 2, 1, 1, 2, 1, 1, 3, 1, 0, 3, 1};

  // Проверяем все вершины
  for (size_t i = 0; i < vertexes.size(); ++i) {
    EXPECT_DOUBLE_EQ(vertexes[i], expected_vertexes[i]);
  }
}

// Кол-во вершин
TEST_F(ObjTransformTest, VertexesNumTest) {
  obj.SetVertexesNum(8);
  EXPECT_EQ(obj.GetVertexesNum(), 8);
}

// Кол-во поверхностей
TEST_F(ObjTransformTest, FacetsNumTest) {
  obj.SetFacetsNum(12);
  EXPECT_EQ(obj.GetFacetsNum(), 12);
}
}  // namespace s21

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
