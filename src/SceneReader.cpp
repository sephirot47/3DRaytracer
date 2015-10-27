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
    if (object->kind == "id")
    {
        if(object->text == "Cube")
        {
            Cube *obj = new Cube();
            AST *property = object->down;
            while(property  != nullptr)
            {
                if(property->text == "center") obj->center = ReadDVec3(property->down);
                else if(property->text == "dimensions") obj->dimensions = ReadDVec3(property->down);
                property = property->right;
            }
            scene.primitives.push_back(obj);
        }
        else if (object->text == "Sphere") 
        {
            Sphere *obj = new Sphere();
            AST *property = object->down;
            while(property != nullptr)
            {
                if(property->text == "center") obj->center = ReadDVec3(property->down);
                else if(property->text == "radius") obj->radius = atof(property->down->kind.c_str());
                property = property->right;
            }
            scene.primitives.push_back(obj);
        }
        else if (object->text == "DLight") 
        {
            DirectionalLight *obj = new DirectionalLight();
            AST *property = object->down;
            while(property != nullptr)
            {
                if(property->text == "dir") obj->dir = glm::normalize(ReadDVec3(property->down));
                else if(property->text == "intensity") obj->intensity = atof(property->down->kind.c_str());
                else if(property->text == "color") obj->color = ReadVec3(property->down);
                property = property->right;
            }
            scene.lights.push_back(obj);
        }
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