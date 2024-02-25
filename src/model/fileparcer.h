#ifndef FILEPARCER_H
#define FILEPARCER_H
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "objdata.h"

namespace s21 {
class FileParcer {
 public:
  void ReadFile(ObjData& objModel, std::string fileName);

 private:
  void LoopingVertexes(const std::vector<int>& input_vector,
                       std::vector<int>& output_vector);
  void PreRead(std::string fileName, int& ver_num, int& fac_num, int& con);
};
}  // namespace s21

#endif  // FILEPARCER_H
