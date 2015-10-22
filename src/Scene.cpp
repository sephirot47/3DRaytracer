#include "../include/Scene.h"
#include "../include/PointLight.h"

int Scene::WindowWidth  = 800;
int Scene::WindowHeight = 800;

glm::vec3 Scene::ClearColor = glm::vec3(0.5, 0.5, 1.0);

double Scene::AspectRatio = double(Scene::WindowWidth) / Scene::WindowHeight;

double Scene::Fov  = 90; //degrees
double Scene::RFov = Scene::Fov * 3.1415926535f/180.0; //rads

double Scene::ZNear = 5.0;
double Scene::ViewportWidth  = Scene::ZNear * tan(Scene::RFov/2);
double Scene::ViewportHeight = Scene::ViewportWidth / Scene::AspectRatio;

Scene::Scene()
{
    srand(time(0));
    
    frameBuffer.create(WindowWidth, WindowHeight);
    timeCount = 0.0;

    double wallsRoughness = 0.95;
    
    //MIRROR
    glm::dvec3 dimensions = glm::dvec3(6.0, 6.0, 0.1) * 0.9;
    Cube *mirror = new Cube(glm::dvec3(0.0, 4.0, 17.0), dimensions);
    mirror->material.ambient = glm::vec3(1,1,1);
    mirror->material.diffuse = glm::vec3(1,1,1);
    mirror->material.specular = glm::vec3(1,1,1);
    mirror->material.roughness = 0.1;
    //primitives.push_back(mirror);
    
    //FLOOR
    dimensions = glm::dvec3(10.0, 0.1, 10.0);
    Cube *floor = new Cube(glm::dvec3(0, -2.0, 10.0), dimensions);
    floor->material.ambient = glm::vec3(0.2,0.2,0.2) * 0.3f;
    floor->material.diffuse = glm::vec3(0.6,0.6,0.6) * 0.3f;
    floor->material.specular = glm::vec3(0);
    floor->material.roughness = wallsRoughness;
    primitives.push_back(floor);
    
    //FRONT WALL
    dimensions = glm::dvec3(10.0, 10.0, 0.1);
    Cube *frontWall = new Cube(glm::dvec3(0, 4.0, 0.0), dimensions);
    frontWall->material.ambient = glm::vec3(0.2,0.2,0.2) * 0.3f;
    frontWall->material.diffuse = glm::vec3(0.6,0.6,0.6) * 0.3f;
    frontWall->material.specular = glm::vec3(0);
    frontWall->material.roughness = wallsRoughness;
    primitives.push_back(frontWall);
    
    //BACK WALL
    dimensions = glm::dvec3(10.0, 10.0, 0.1);
    Cube *backWall = new Cube(glm::dvec3(0, 0.0, 18.0), dimensions);
    backWall->material.ambient = glm::vec3(0.2,0.2,0.2) * 0.3f;
    backWall->material.diffuse = glm::vec3(0.6,0.6,0.6) * 0.3f;
    backWall->material.specular = glm::vec3(0);
    backWall->material.roughness = wallsRoughness;
    primitives.push_back(backWall);

    //RIGHT WALL
    dimensions = glm::dvec3(0.1, 10.0, 10.0);
    Cube *rightWall = new Cube(glm::dvec3(7.0, 0.0, 10.0), dimensions);
    rightWall->material.ambient = glm::vec3(0.2,0.2,0.2) * 0.3f;
    rightWall->material.diffuse = glm::vec3(0.6,0.6,0.6) * 0.3f;
    rightWall->material.specular = glm::vec3(0);
    rightWall->material.roughness = wallsRoughness;
    primitives.push_back(rightWall);

    //LEFT WALL
    dimensions = glm::dvec3(0.1, 10.0, 10.0);
    Cube *leftWall = new Cube(glm::dvec3(-7.0, 0.0, 10.0), dimensions);
    leftWall->material.ambient = glm::vec3(0.2,0.2,0.2) * 0.3f;
    leftWall->material.diffuse = glm::vec3(0.6,0.6,0.6) * 0.3f;
    leftWall->material.specular = glm::vec3(0);
    leftWall->material.roughness = wallsRoughness;
    primitives.push_back(leftWall);
    
    //CEIL
    dimensions = glm::dvec3(10.0, 0.1, 10.0);
    Cube *ceil = new Cube(glm::dvec3(0.0, 8.0, 10.0), dimensions);
    ceil->material.ambient = glm::vec3(0.2,0.2,0.2) * 0.3f;
    ceil->material.diffuse = glm::vec3(0.6,0.6,0.6) * 0.3f;
    ceil->material.specular = glm::vec3(0);
    ceil->material.roughness = wallsRoughness;
    //primitives.push_back(ceil);
    
    
    Sphere *bigSphere = new Sphere(glm::dvec3(3.0, 0.0, 10.0),  2.0f);
    bigSphere->material.roughness = 0.5;
    primitives.push_back(bigSphere);
    
    Sphere *sphere = new Sphere(glm::dvec3(0.0, -1.0, 10.0),  1.0f);
    sphere->material.ambient = glm::vec3(0.2,0,0.0);
    sphere->material.diffuse = glm::vec3(0.6,0,0.0);
    sphere->material.specular = glm::vec3(1,1,1);
    sphere->material.roughness = 0.8;
    primitives.push_back(sphere);

    Sphere *littleSphere = new Sphere(glm::dvec3(1, 0.6, 7.5),  0.3f);
    littleSphere->material.ambient = glm::vec3(0.2,0.2,0);
    littleSphere->material.diffuse = glm::vec3(0.6,0.6,0);
    littleSphere->material.roughness = 0.5;
    primitives.push_back(littleSphere);
    
    /*
    dimensions = glm::dvec3(0.5, 0.5, 1.0);
    Cube *littleCube = new Cube(glm::dvec3(-1.0, -1.5, 8.0),  dimensions);
    littleCube->material.ambient = glm::vec3(0.0,0.0,0.1);
    littleCube->material.diffuse = glm::vec3(0.0,0.0,0.3);
    littleCube->material.roughness = 0.6;
    primitives.push_back(littleCube);
    */
    
    DirectionalLight *light4 = new DirectionalLight();
    //light4->center = glm::dvec3(0.0,0.0,2.0);
    light4->color = glm::vec3(1, 0.5, 0.5);
    light4->dir = glm::dvec3(0, 1, 0);
    light4->intensity = 0.8;
    lights.push_back(light4);
    
    DirectionalLight *light = new DirectionalLight();
    //light4->center = glm::dvec3(0.0,0.0,2.0);
    light->color = glm::vec3(1, 1, 1);
    light->dir = glm::dvec3(0, -1, 0);
    light->intensity = 0.4;
    lights.push_back(light);
    
    PointLight *light2 = new PointLight();
    light2->color = glm::vec3(1, 1, 1);
    light2->range = 15.0;
    light2->center = glm::vec3(2, 4, 15);
    //light2->dir = glm::dvec3(-1, 1, 1);
    light2->intensity = 0.5;
    lights.push_back(light2);

    depthBuffer = vector<double>(WindowWidth * WindowHeight);
    ClearDepthBuffer();
}

Scene::~Scene()
{
  for(Primitive *p : primitives) delete p;
  for(Light *l : lights) delete l;
}

void Scene::GetRayFromPixel(int pixelX, int pixelY, Ray &ray)
{
  double x =  ViewportWidth  * ( double(pixelX) / (WindowWidth /2) );
  double y = -ViewportHeight * ( double(pixelY) / (WindowHeight/2) );
  double z = ZNear;

  ray.dir = glm::dvec3(x,y,z);
}

void Scene::ClearDepthBuffer()
{
    for(int i = 0; i < depthBuffer.size(); ++i) depthBuffer[i] = 999999999.0;
}

void Scene::ClearFrameBuffer(sf::Color clearColor) {
  frameBuffer.create(WindowWidth, WindowHeight, clearColor);
}


double Scene::GetDepthAt(int pixelX, int pixelY)
{
    return depthBuffer[pixelX + WindowWidth/2 + (pixelY + WindowHeight/2) * WindowWidth];
}

void Scene::SetDepthAt(int pixelX, int pixelY, double depth)
{
    depthBuffer[pixelX + WindowWidth/2 + (pixelY + WindowHeight/2) * WindowWidth] = depth;
}

bool Scene::RayTrace(const Ray& ray, Intersection &intersection) const
{
  double minDist;
  Intersection inter;
  bool intersected = false;
  for(Primitive *primitive : primitives)
  {
      if(primitive->GetIntersection(ray, inter))
      {
        double dist = glm::length(ray.origin - inter.point);
        if (dist < minDist || !intersected) {
          minDist = dist;
          intersection = inter;
        }
        intersected = true;
      }
  }
  return intersected;
}

sf::Color Scene::Vec3ToColor(glm::vec3 color)
{
  unsigned char r = (unsigned char) glm::clamp(color.r * 255.0f, 0.0f, 255.0f);
  unsigned char g = (unsigned char) glm::clamp(color.g * 255.0f, 0.0f, 255.0f);
  unsigned char b = (unsigned char) glm::clamp(color.b * 255.0f, 0.0f, 255.0f);
  return sf::Color(r,g,b);
}

glm::dvec3 Scene::GetRandomVector()
{
    glm::dvec3 randVector(GetRand(), GetRand(), GetRand());
    return glm::normalize(randVector);
}

glm::vec3 Scene::GetPixelColor(Ray& ray, int bounces)
{
    Intersection intersection;
    glm::vec3 pixelColor;
    if(RayTrace(ray, intersection))
    {
        bool calcBounceColor = (bounces < 6 && intersection.material->roughness < 1.0);
        float r = float(intersection.material->roughness);
        
        Ray bounceRay = ray.reflect(intersection);
        glm::dvec3 roughnessVector = (GetRandomVector() * double(r) * 0.01);
        bounceRay.dir = glm::normalize( bounceRay.dir + roughnessVector);
        
        glm::vec3 bounceColor = calcBounceColor ? GetPixelColor(bounceRay, bounces + 1) : ClearColor;
        pixelColor = intersection.material->ambient;
        for(Light *light : lights)
        {
            pixelColor = light->LightIt(*this, pixelColor, intersection);
        }
        return (r * pixelColor + (1.0f-r) * bounceColor);
    }
    return ClearColor;
}

void Scene::Draw(sf::RenderWindow &window)
{
    ClearFrameBuffer( Vec3ToColor(ClearColor) );
    ClearDepthBuffer();

    timeCount += 0.01f;
    //((PointLight*)lights[2])->center = primitives[1]->center;
    //primitives[0]->center = glm::dvec3(-sin(timeCount*2.0) * 1.5f, cos(timeCount*2.0) * 1.5f, 10.0);
    //primitives[1]->center = glm::dvec3( 2.5f, cos(timeCount*2.0) * 2.5f, 10.0 + sin(timeCount * 4.0) * 2.5);
    //primitives[2]->center = glm::dvec3(-sin(timeCount * 1.5f) * 2.5f, cos(timeCount * 2.0) * 2.5f, 10.0 + sin(timeCount * 3.0) * 2.0);

    float lastShownPercentage = 0.0f; float percentageStep = 0.005f;
    for(int x = -WindowWidth/2; x < WindowWidth/2; ++x)
    {
        for(int y = -WindowHeight/2; y < WindowHeight/2; ++y)
        {
            Ray ray; GetRayFromPixel(x, y, ray);
            Intersection intersection;
            if(RayTrace(ray, intersection))
            {
                glm::vec3 pixelColor = GetPixelColor(ray, 0);
                SetDepthAt(x, y, intersection.point.z);
                frameBuffer.setPixel(x + WindowWidth/2, y + WindowHeight/2, Vec3ToColor(pixelColor));
            }
            
            //Print percentage
            float percentage = float((x+WindowWidth/2) * WindowHeight + y + WindowHeight/2) / (WindowWidth*WindowHeight);
            if(percentage - lastShownPercentage > percentageStep) 
            { lastShownPercentage = percentage; cout << (percentage*100.0f) << "%" << endl; }
        }
    }

  //for (int i = 0; i < WindowWidth; ++i) frameBuffer.setPixel(i,WindowHeight/2, sf::Color::Green);
  //for (int i = 0; i < WindowHeight; ++i) frameBuffer.setPixel(WindowWidth/2,i, sf::Color::Green);
  sf::Texture texture; texture.loadFromImage(frameBuffer);

  sf::Sprite sprite; sprite.setTexture(texture);
  window.draw(sprite);
  window.display();
}
