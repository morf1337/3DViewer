#include "fileparcer.h"

using namespace s21;

void FileParcer::ReadFile(ObjData& objModel, std::string fileName) {
  std::string tempStr, token;
  std::vector<double> vertexes;
  std::vector<int> indexes, strIndexes;
  std::istringstream iss;
  double v1;
  int v_counter = 0, fac_counter = 0, connections = 0, help_v_counter = 0,
      index_value = 0;
  PreRead(fileName, v_counter, fac_counter, connections);
  vertexes.reserve(v_counter * 3);
  indexes.reserve(connections * 2);
  std::ifstream obj(fileName);

  if (obj) {
    while (std::getline(obj, tempStr)) {
      if (tempStr.size() > 2 && tempStr[0] == 'v' && tempStr[1] == ' ') {
        iss.clear();
        iss.str(tempStr.substr(2));
        while (iss >> v1) {
          vertexes.push_back(v1);
        }
        ++help_v_counter;
      } else if (tempStr.size() > 2 && tempStr[0] == 'f' && tempStr[1] == ' ') {
        iss.clear();
        iss.str(tempStr.substr(2));
        while (std::getline(iss, token, ' ')) {
          if (!token.empty()) {
            try {
              index_value = std::stoi(token);
              if (index_value < 0) {
                strIndexes.push_back(index_value + help_v_counter + 1);
              } else {
                strIndexes.push_back(index_value);
              }
            } catch (const std::invalid_argument& e) {
              continue;
            }
          }
        }
        LoopingVertexes(strIndexes, indexes);
        strIndexes.clear();
      }
    }
    obj.close();
    objModel.SetFacetsNum(fac_counter);
    objModel.SetVertexesNum(v_counter);
    objModel.SetIndexes(indexes);
    objModel.SetVertexes(
        vertexes);  // SetVertexes only after SetIndexes!(observer notify is set
                    // up only for vertexes changes)
  }
}

void FileParcer::LoopingVertexes(const std::vector<int>& input_vector,
                                 std::vector<int>& output_vector) {
  size_t inputSize = input_vector.size();
  for (size_t i = 0; i < inputSize; ++i) {
    output_vector.push_back(input_vector[i] - 1);
    output_vector.push_back(input_vector[(i + 1) % inputSize] - 1);
  }
}

void FileParcer::PreRead(std::string fileName, int& ver_num, int& fac_num,
                         int& con) {
  int v_counter = 0, fac_counter = 0, connections = 0;
  std::ifstream obj(fileName);
  std::string tempStr, token;
  std::istringstream iss;
  if (obj) {
    while (std::getline(obj, tempStr)) {
      if (tempStr.size() > 2 && tempStr[0] == 'v' && tempStr[1] == ' ') {
        ++v_counter;
      } else if (tempStr.size() > 2 && tempStr[0] == 'f' && tempStr[1] == ' ') {
        iss.clear();
        iss.str(tempStr.substr(2));
        while (std::getline(iss, token, ' ')) {
          ++connections;
        }
        ++fac_counter;
      }
    }
  }
  obj.close();
  ver_num = v_counter;
  fac_num = fac_counter;
  con = connections;
}
