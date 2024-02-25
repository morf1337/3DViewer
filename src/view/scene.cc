#include "scene.h"

using namespace s21;

Scene::Scene(QWidget *parent) : QOpenGLWidget(parent) {
  backColor = QColor(Qt::white);
  lineColor = QColor(Qt::black);
  pointColor = QColor(Qt::blue);
  lineType = pointType = 0;
  lineThickness = pointThickness = 1;
}

void Scene::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(backColor.redF(), backColor.greenF(), backColor.blueF(), 1);
  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_COLOR_MATERIAL);
}

void Scene::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void Scene::paintGL() {
  glClearColor(backColor.redF(), backColor.greenF(), backColor.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (isObjLoaded) {
    DrawObjModel();
  }
}

void Scene::DrawObjModel() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (!isOrtho) {
    glFrustum(-5, 5, -5, 5, 5, 100);
    glTranslated(0, 0, -10);
  } else {
    glOrtho(-10, 10, -10, 10, 2, 100);
    glTranslatef(0, 0, -5);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glVertexPointer(3, GL_DOUBLE, 0, vertexesInScene.data());
  glEnableClientState(GL_VERTEX_ARRAY);
  glLineWidth(lineThickness);
  glColor3f(lineColor.redF(), lineColor.greenF(), lineColor.blueF());
  if (lineType) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0X0101);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glDrawElements(GL_LINES, indexesInScene.size(), GL_UNSIGNED_INT,
                 indexesInScene.data());
  glDisableClientState(GL_VERTEX_ARRAY);

  if (pointType != 0) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_POINT_SMOOTH);
    glColor3f(pointColor.redF(), pointColor.greenF(), pointColor.blueF());
    if (pointType == 2) glDisable(GL_POINT_SMOOTH);
    glPointSize(pointThickness);
    glDrawArrays(GL_POINTS, 0, vertexesInScene.size() / 3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_POINT_SMOOTH);
  }
}

void Scene::SetParameter(const std::string &parameter, QVariant value) {
  if (parameter == "projType") {
    isOrtho = value.toInt();
  } else if (parameter == "lineType") {
    lineType = value.toInt();
  } else if (parameter == "pointType") {
    pointType = value.toInt();
  } else if (parameter == "backColor") {
    backColor = value.value<QColor>();
  } else if (parameter == "lineColor") {
    lineColor = value.value<QColor>();
  } else if (parameter == "pointColor") {
    pointColor = value.value<QColor>();
  } else if (parameter == "lineThickness") {
    lineThickness = value.toInt();
  } else if (parameter == "pointThickness") {
    pointThickness = value.toInt();
  }
  update();
}

QVariant Scene::GetParameter(const std::string &parameter) {
  if (parameter == "projType") {
    return QVariant::fromValue(isOrtho);
  } else if (parameter == "lineType") {
    return QVariant::fromValue(lineType);
  } else if (parameter == "pointType") {
    return QVariant::fromValue(pointType);
  } else if (parameter == "backColor") {
    return QVariant::fromValue(backColor);
  } else if (parameter == "lineColor") {
    return QVariant::fromValue(lineColor);
  } else if (parameter == "pointColor") {
    return QVariant::fromValue(pointColor);
  } else if (parameter == "lineThickness") {
    return QVariant::fromValue(lineThickness);
  } else if (parameter == "pointThickness") {
    return QVariant::fromValue(pointThickness);
  } else {
    return QVariant();
  }
}

void Scene::handleUpdate(const std::vector<double> &v,
                         const std::vector<int> &i) {
  vertexesInScene.clear();
  indexesInScene.clear();
  vertexesInScene = v;
  indexesInScene = i;
  isObjLoaded = true;
  update();
}
