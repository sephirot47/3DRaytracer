#include "../include/Scene.h"
#include "../include/PointLight.h"

int Scene::MSAA = 1;
int Scene::WindowWidth  = 1000 * MSAA;
int Scene::WindowHeight = 1000 * MSAA;

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
    
    DirectionalLight *light4 = new DirectionalLight();
    //light4->center = glm::dvec3(0.0,0.0,2.0);
    light4->color = glm::vec3(1, 0., 0.5);
    light4->dir = glm::dvec3(0, 1, 0);
    light4->intensity = 0.8;
    //lights.push_back(light4);
    
    DirectionalLight *light = new DirectionalLight();
    //light4->center = glm::dvec3(0.0,0.0,2.0);
    light->color = glm::vec3(1, 1, 1);
    light->dir = glm::normalize( glm::dvec3(-0.8, -1, 0.8) );
    light->intensity = 0.4;
    lights.push_back(light);
    
    PointLight *light2 = new PointLight();
    light2->color = glm::vec3(1, 1, 1);
    light2->range = 15.0;
    light2->center = glm::vec3(2, 4, 10);
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

glm::vec3 Scene::GetPixelColor(Ray& ray, int bounces, bool inVoid)
{
    Intersection intersection;
    glm::vec3 pixelColor;
    if(RayTrace(ray, intersection))
    {
        bool calcBounceColor = (bounces < 6 && intersection.material->roughness < 1.0);
        float r = float(intersection.material->roughness);
        
        //Apply reflection
        Ray bounceRay = ray.reflect(intersection);
        
        //Apply random vector of roughness to the ray bounce direction
        glm::dvec3 roughnessVector = (GetRandomVector() * double(r) * 0.01);
        bounceRay.dir = glm::normalize( bounceRay.dir + roughnessVector);
        
        glm::vec3 bounceColor = calcBounceColor ? GetPixelColor(bounceRay, bounces + 1, inVoid) : ClearColor;
        pixelColor = intersection.material->ambient;
        //Apply light
        for(Light *light : lights)
        {
            pixelColor = light->LightIt(*this, pixelColor, intersection);
        }
        
        pixelColor = (r * pixelColor + (1.0f-r) * bounceColor);
        
        //Apply refraction
        double alpha = intersection.material->alpha;
        if(alpha < 1.0)
        {
            double epsilon = 0.0001;
            Ray refractionRay = ray.refract(intersection, inVoid);
            refractionRay.origin = intersection.point + epsilon * refractionRay.dir;
            pixelColor = float(alpha) * pixelColor + float(1.0-alpha) * GetPixelColor(refractionRay, bounces+1, !inVoid);
        }
        
        return pixelColor;
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
                SetDepthAt(x, y, intersection.point.z);
                glm::vec3 pixelColor = GetPixelColor(ray, 0, true);
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
  texture.setSmooth(true);
  sf::Sprite sprite; sprite.setTexture(texture);
  sprite.setScale(1.0f/MSAA, 1.0f/MSAA);
  window.draw(sprite);
  window.display();
}
