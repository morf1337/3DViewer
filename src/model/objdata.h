#ifndef OBJDATA_H
#define OBJDATA_H
#include <vector>

namespace s21 {
class Observer {
 public:
  virtual void handleUpdate(const std::vector<double>& vertexes,
                            const std::vector<int>& indexes) = 0;
};

// contains the data of loaded .obj model
class ObjData {
 public:
  int GetFacetsNum();
  void SetFacetsNum(int n);
  int GetVertexesNum();
  void SetVertexesNum(int n);
  std::vector<double>& GetVertexesArr();
  std::vector<int>& GetIndexesArr();
  void SetVertexes(std::vector<double>& v);
  void SetIndexes(std::vector<int>& i);

  // for observer pattern
  void addObserver(Observer* observer) { observers.push_back(observer); }
  void notifyObservers() {
    for (Observer* observer : observers) {
      observer->handleUpdate(vertexes, indexes);
    }
  }

 private:
  std::vector<double> vertexes;
  std::vector<int> indexes;
  int vertexes_num = 0;
  int facets_num = 0;
  std::vector<Observer*> observers;
};
}  // namespace s21

#endif  // OBJDATA_H
