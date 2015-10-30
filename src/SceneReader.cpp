#include "../include/SceneReader.h"
#include "../include/Scene.h"

map<string, Material*> SceneReader::materialsMap;

void SceneReader::ReadScene(Scene& scene, string filename)
{
    FILE *f;
    f = fopen(filename.c_str(), "r");

    AST *root = NULL;
    ANTLR(program(&root),  f);
    ASTPrint(root);
    AST* section = root->down; //MATERIALS, SCENE, ...

    while(section != nullptr)
    {
        if(section->kind == "CAMERA")
        {
            //CAMERA
            ReadCamera(scene, section);
        }
        else if(section->kind == "MATERIALS")
        {  
            //MATERIALS
            AST *material = section->down;
            while (material != nullptr) 
            {
                if(material->kind == "id") ReadMaterial(material);
                material = material->right;
            }
        }
        else if(section->kind == "SCENE")
        { 
            //SCENE
            AST *object = section->down;
            while (object != nullptr) 
            {
                if (object->kind == "id")
                {
                    if(object->text == "Cube") ReadCube(scene, object);
                    else if (object->text == "Sphere") ReadSphere(scene, object);
                    else if (object->text == "DLight") ReadDLight(scene, object);
                    else if (object->text == "PLight") ReadPLight(scene, object);
                }
                object = object->right; //Go to next object
            }
        }
        section = section->right; //Go to next section
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


/////////////////////////////////////////////////////////////////

void SceneReader::ReadCamera(Scene& scene, void* astCamera)
{
    AST *property = ((AST*)astCamera)->down;

    double FOV = Scene::GetFov();
    int MSAA = Scene::GetMSAA();
    int windowWidth = Scene::GetWindowWidth();
    int windowHeight = Scene::GetWindowHeight();
    double depthOfField = Scene::GetDepthOfField();

    while(property != nullptr)
    {
        if(property->text == "FOV") FOV = atof(property->down->kind.c_str());
        else if(property->text == "MSAA")  MSAA = atoi(property->down->kind.c_str());
        else if(property->text == "windowWidth")  windowWidth = atoi(property->down->kind.c_str());
        else if(property->text == "windowHeight")  windowHeight = atoi(property->down->kind.c_str());
        else if(property->text == "depthOfField")  depthOfField = atof(property->down->kind.c_str());
        else if(property->text == "clearColor")  Scene::ClearColor = ReadVec3(property->down);
        else if(property->text == "depthOfFieldEnabled")
        {
            if(property->down->text == "True" || property->down->text == "true") Scene::DepthOfFieldEnabled = true;
            else if(property->down->text == "False" || property->down->text == "false") Scene::DepthOfFieldEnabled = false;
            else UnrecognizedPropertyWarning(property->down->text);
        }
        else UnrecognizedPropertyWarning(property->text);

        property = property->right;
    }

    scene.SetCamera(FOV, depthOfField, MSAA, windowWidth, windowHeight);
}


/////////////////////////////////////////////////////////////////


void SceneReader::ReadMaterial(void* astMaterial)
{
    Material *material = new Material();

    AST *property = ((AST*)astMaterial)->down;
    while(property != nullptr)
    {
        if(property->kind == ":")
        {
            *material = *(materialsMap[property->down->text]);
        }
        else if(property->text == "ambient") material->ambient = ReadVec3(property->down);
        else if(property->text == "diffuse") material->diffuse = ReadVec3(property->down);
        else if(property->text == "specular") material->specular = ReadVec3(property->down);

        else if(property->text == "shininess") material->shininess = atof(property->down->kind.c_str());
        else if(property->text == "roughness") material->roughness = atof(property->down->kind.c_str());
        else if(property->text == "alpha") material->alpha = atof(property->down->kind.c_str());
        else if(property->text == "refraction") material->refraction = atof(property->down->kind.c_str());

        else UnrecognizedPropertyWarning(property->text);

        property = property->right;
    }

    materialsMap[((AST*)astMaterial)->text] = material;
}


////////////////////////////////////////////////////////////////////////

void SceneReader::ReadCube(Scene& scene, void* astCube)
{
    Cube *obj = new Cube();
    AST *property = ((AST*)astCube)->down;
    while(property  != nullptr)
    {
        if(property->text == "center") obj->center = ReadDVec3(property->down);
        else if(property->text == "dimensions") obj->dimensions = ReadDVec3(property->down);
        else if(property->text == "material")
        {
            delete obj->material;
            obj->material = materialsMap[property->down->text];
        }
        else UnrecognizedPropertyWarning(property->text);
        
        property = property->right;
    }
    scene.primitives.push_back(obj);
}

void SceneReader::ReadSphere(Scene& scene, void* astSphere)
{
    Sphere *obj = new Sphere();
    AST *property = ((AST*)astSphere)->down;
    while(property != nullptr)
    {
        if(property->text == "center") obj->center = ReadDVec3(property->down);
        else if(property->text == "radius") obj->radius = atof(property->down->kind.c_str());
        else if(property->text == "material")
        {
            delete obj->material;
            obj->material = materialsMap[property->down->text];
        }
        else UnrecognizedPropertyWarning(property->text);
        
        property = property->right;
    }
    scene.primitives.push_back(obj);
}

void SceneReader::ReadDLight(Scene& scene, void* astDLight)
{
    DirectionalLight *obj = new DirectionalLight();
    AST *property = ((AST*)astDLight)->down;
    while(property != nullptr)
    {
        if(property->text == "dir") obj->dir = glm::normalize(ReadDVec3(property->down));
        else if(property->text == "intensity") obj->intensity = atof(property->down->kind.c_str());
        else if(property->text == "color") obj->color = ReadVec3(property->down);
        else UnrecognizedPropertyWarning(property->text);
        
        property = property->right;
    }
    scene.lights.push_back(obj);
}

void SceneReader::ReadPLight(Scene& scene, void* astPLight)
{
    PointLight *obj = new PointLight();
    AST *property = ((AST*)astPLight)->down;
    while(property != nullptr)
    {
        if(property->text == "center") obj->center = ReadDVec3(property->down);
        else if(property->text == "range") obj->range = atof(property->down->kind.c_str());
        else if(property->text == "intensity") obj->intensity = atof(property->down->kind.c_str());
        else if(property->text == "color") obj->color = ReadVec3(property->down);
        else UnrecognizedPropertyWarning(property->text);

        property = property->right;
    }
    scene.lights.push_back(obj);
}

///////////////////////////////////////////////////////////


void SceneReader::UnrecognizedPropertyWarning(string propertyName)
{
    cout << "[   SceneReader   ] Warning: Unrecognized property '" << propertyName << "'" << endl;
}

void SceneReader::Warning(string msg)
{
    cout << "[   SceneReader   ] Warning: " << msg << endl;
}







