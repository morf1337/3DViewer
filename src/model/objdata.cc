#include "objdata.h"

using namespace s21;

int ObjData::GetFacetsNum() { return facets_num; }
void ObjData::SetFacetsNum(int n) { facets_num = n; }
int ObjData::GetVertexesNum() { return vertexes_num; }
void ObjData::SetVertexesNum(int n) { vertexes_num = n; }
std::vector<double>& ObjData::GetVertexesArr() { return vertexes; }
std::vector<int>& ObjData::GetIndexesArr() { return indexes; }
void ObjData::SetIndexes(std::vector<int>& i) { indexes = std::move(i); }
void ObjData::SetVertexes(std::vector<double>& v) {
  vertexes = std::move(v);
  notifyObservers();
}
