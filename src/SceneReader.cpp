#include "../include/SceneReader.h"
#include "../include/Scene.h"

void SceneReader::ReadScene(Scene& scene, string filename)
{
  FILE *f;
  f = fopen(filename.c_str(), "r");
  
  AST *root = NULL;
  ANTLR(program(&root),  f);
  ASTPrint(root);
  AST* sceneRoot = root;
  AST* object = root->down;
  while (object != nullptr) 
  {
    cout << (object->kind) << endl;
    if (object->kind == "Cube") 
    {
      glm::dvec3 center = ReadDVec3(object->down);
      glm::dvec3 dimensions = ReadDVec3(object->down->right);
      Cube *c = new Cube(center, dimensions);
      scene.primitives.push_back(c);
    }
    else if (object->kind == "Sphere") 
    {
      glm::dvec3 center = ReadDVec3(object->down);
      double radius = atof(object->down->right->kind.c_str());
      Sphere *s = new Sphere(center, radius);
      scene.primitives.push_back(s);
    }
    object = object->right;
  }
  fclose(f);
}

glm::vec3 SceneReader::ReadVec3 (void* v)
{
  AST *vec = (AST*)v;
  float x = atof(vec->down->kind.c_str());
  float y = atof(vec->down->right->kind.c_str());
  float z = atof(vec->down->right->right->kind.c_str());
  return glm::vec3(x,y,z);
}

glm::dvec3 SceneReader::ReadDVec3 (void* v)
{
  AST *vec = (AST*)v;
  double x = atof(vec->down->kind.c_str());
  double y = atof(vec->down->right->kind.c_str());
  double z = atof(vec->down->right->right->kind.c_str());
  return glm::dvec3(x,y,z);
}