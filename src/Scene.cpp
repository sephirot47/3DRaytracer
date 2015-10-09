#include "../include/Scene.h"

int Scene::WindowWidth  = 800;
int Scene::WindowHeight = 600;

float Scene::AspectRatio = float(Scene::WindowWidth) / Scene::WindowHeight;

float   Scene::Fov  = 60; //degrees
float Scene::RFov = Scene::Fov * 3.1415926535f/180.0f; //rads

float Scene::ZNear = 5.0f;
float Scene::ViewportWidth  = Scene::ZNear * tan(Scene::RFov/2);
float Scene::ViewportHeight = Scene::ViewportWidth / Scene::AspectRatio;

Scene::Scene()
{
    frameBuffer.create(WindowWidth, WindowHeight);
    timeCount = 0.0f;
    
    Sphere *sphere = new Sphere(glm::vec3(sin(timeCount) * 2.5f, -cos(timeCount) *2.5f, sin(timeCount*3.0f) *2.0f +10.0f),  0.5f);
    primitives.push_back(sphere);
    
    Cube *cube = new Cube(glm::vec3(0.0f, 0.0f, 12.0f),  0.1f);
    //primitives.push_back(cube);
    
    depthBuffer.reserve(WindowWidth * WindowHeight);
    ClearDepthBuffer();
}
    
Scene::~Scene() 
{
  for(Primitive *p : primitives) delete p;
}

void Scene::GetRayFromPixel(int pixelX, int pixelY, Ray &ray)
{
  float x =  ViewportWidth  * ( float(pixelX) / (WindowWidth /2) );
  float y = -ViewportHeight * ( float(pixelY) / (WindowHeight/2) );
  float z = ZNear;

  ray.dir = glm::vec3(x,y,z);
}

void Scene::ClearDepthBuffer()
{
    for(int i = 0; i < depthBuffer.size(); ++i) depthBuffer[i] = 999999999.0f;
}

float Scene::GetDepthAt(int pixelX, int pixelY)
{
    return depthBuffer[pixelX + WindowWidth/2 + (pixelY + WindowHeight/2) * WindowWidth];
}

void Scene::SetDepthAt(int pixelX, int pixelY, float depth)
{
    depthBuffer[pixelX + WindowWidth/2 + (pixelY + WindowHeight/2) * WindowWidth] = depth;
}
  
void Scene::Draw(sf::RenderWindow &window)
{
    ClearDepthBuffer();
    
    timeCount += 0.05f;
    primitives[0]->center = glm::vec3(sin(timeCount) * 2.5f, -cos(timeCount) *2.5f, sin(timeCount*3.0f) *2.0f +10.0f);
    glm::vec3 lightDir = glm::normalize(glm::vec3(1.0f, 0.0f, 1.0f));

    sf::Color bgColor = sf::Color(255, 255, 255);
    window.clear(sf::Color::Black);
    for(int x = -WindowWidth/2; x < WindowWidth/2; ++x)
    {
        for(int y = -WindowHeight/2; y < WindowHeight/2; ++y)
        {
            Ray ray; GetRayFromPixel(x, y, ray);

            for(Primitive *primitive : primitives) 
            {
                bool primitiveDrawn = false;
                sf::Color pixelColor;
                Intersection intersection;
                if(primitive->GetIntersection(ray, intersection))
                {
                    float depth = GetDepthAt(x,y);
                    if(intersection.point.z < depth)
                    {
                        SetDepthAt(x, y, intersection.point.z);

                        pixelColor = sf::Color(255, 0, 0);
                        float dot = glm::dot(-lightDir, intersection.normal);
                        dot = dot < 0.0f ? 0.0f : (dot > 1.0f ? 1.0f : dot);
                        primitiveDrawn = true;
                        pixelColor = sf::Color(pixelColor.r * dot, pixelColor.g * dot, pixelColor.b * dot);
                    }
                }
                
                if(!primitiveDrawn) pixelColor = bgColor;

                frameBuffer.setPixel(x + WindowWidth/2, y + WindowHeight/2, pixelColor);
            }
        }
    }
  
  sf::Texture texture; texture.loadFromImage(frameBuffer);
  sf::Sprite sprite; sprite.setTexture(texture);
  window.draw(sprite);
  window.display();
}