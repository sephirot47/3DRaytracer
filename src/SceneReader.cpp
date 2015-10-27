#include "../include/SceneReader.h"
#include "../src/Scene.cpp"

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
    if (object->kind == "CUBE") 
    {
      glm::dvec3 center = ReadDVec3(object->down);
      glm::dvec3 dimensions = ReadDVec3(object->down->right);
      Cube *c = new Cube(center, dimensions);
      scene.primitives.push_back(c);
    }
      
    object = object->right;
  }
  fclose(f);
}

glm::vec3 SceneReader::ReadVec3 (AST* vec)
{
  float x = atof(vec->down->text.c_str());
  float y = atof(vec->down->right->text.c_str());
  float z = atof(vec->down->right->right->text.c_str());
  return glm::vec3(x,y,z);
}

glm::dvec3 SceneReader::ReadDVec3 (AST* vec)
{
  double x = atof(vec->down->text.c_str());
  double y = atof(vec->down->right->text.c_str());
  double z = atof(vec->down->right->right->text.c_str());
  return glm::dvec3(x,y,z);
}