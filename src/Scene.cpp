#include "../include/Scene.h"
#include "../include/PointLight.h"

int Scene::MSAA = 2;
int Scene::WindowWidth  = 700 * MSAA;
int Scene::WindowHeight = 500 * MSAA;

glm::vec3 Scene::ClearColor = glm::vec3(0.5, 0.5, 1.0);

double Scene::AspectRatio = double(Scene::WindowWidth) / Scene::WindowHeight;

double Scene::Fov  = 90; //degrees
double Scene::DepthOfField = 5.0;
bool   Scene::DepthOfFieldEnabled = true;
double Scene::RFov = Scene::Fov * 3.1415926535f/180.0; //rads

double Scene::ZNear = 5.0;
double Scene::ViewportWidth  = Scene::ZNear * tan(Scene::RFov/2);
double Scene::ViewportHeight = Scene::ViewportWidth / Scene::AspectRatio;
double Scene::InfiniteDepth = 999999999.0;

glm::dvec3 Scene::CameraPosition = glm::dvec3(1,1,2);
glm::dvec3 Scene::CameraRotation = glm::dvec3(0,M_PI/6,0);

Scene::Scene()
{
    srand(time(0));
    
    frameBuffer.create(WindowWidth, WindowHeight);
    timeCount = 0.0;
      
    depthBuffer = vector<double>(WindowWidth * WindowHeight);
    ClearDepthBuffer();

    sphereVectors = vector<glm::dvec3>();

    int n = 200;
    double alpha = 4.0 * M_PI/n;
    double d = sqrt(alpha);
    int Mv = round(M_PI/d);
    double dv = M_PI/Mv, dy = alpha/dv;
    for (int i = 0; i < Mv; ++i) {
      double v = M_PI*(i + 0.5)/Mv;
      double My = round(2*M_PI*sin(v)/dy);
      for (int j = 0; j < My; ++j) {
        double y = 2*M_PI*j/My;
        sphereVectors.push_back(glm::dvec3(
          sin(v)*cos(y),
          sin(v)*sin(y),
          cos(v)
          ));
      }
    }
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

  ray.origin = CameraPosition;
  glm::vec4 dir(x,y,z,1);
  glm::mat4 transform(1.0);
  transform = glm::rotate(transform, float(CameraRotation.x), glm::vec3(1,0,0));
  transform = glm::rotate(transform, float(CameraRotation.y), glm::vec3(0,1,0));
  transform = glm::rotate(transform, float(CameraRotation.z), glm::vec3(0,0,1));
  dir = transform*dir;
  ray.dir = glm::normalize(glm::dvec3(dir.x,dir.y,dir.z));
}

void Scene::ClearDepthBuffer()
{
    for(int i = 0; i < depthBuffer.size(); ++i) depthBuffer[i] = Scene::InfiniteDepth;
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
  double minDist = 99999999999.0;
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

glm::vec3 Scene::ColorToVec3(sf::Color color)
{
  float r = ((float) color.r) / 255.0f;
  float g = ((float) color.g) / 255.0f;
  float b = ((float) color.b) / 255.0f;
  return glm::vec3(r,g,b);
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

glm::vec3 Scene::GetPixelColor(Ray& ray, int bounces, bool inVoid, bool indirectLightning /* = false*/)
{
    Intersection intersection;
    glm::vec3 percentageixelColor;
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
        glm::vec3 pixelColor = glm::vec3(0);

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

        if (indirectLightning) pixelColor += GetIndirectLightning(intersection, pixelColor);
        
        return pixelColor;
    }
    return ClearColor;
}

glm::vec3 Scene::GetIndirectLightning(const Intersection &intersection, glm::vec3 ownColor)
{
  glm::dvec3 color(0);
  int nRays = sphereVectors.size();
  
  for (int i = 0; i < nRays; ++i) 
  {
    glm::dvec3 dir = sphereVectors[i] + (GetRandomVector() * 0.05);
    glm::dvec3 origen = intersection.point + intersection.normal * 0.01;
    Ray r(origen, dir);
    Intersection indirectInter;
    if (RayTrace(r, indirectInter)) {
      if (abs(glm::length(intersection.point - indirectInter.point)) < 0.05) 
      {
        color += ownColor;
      } 
      else 
      {
        color += GetPixelColor(r, 999999, false) * (1.0f - float (indirectInter.material->roughness));  
      }
    } else {
      color += ClearColor;
    }
  }

  color = color / double (nRays);
  return color;
}

void Scene::Draw(sf::RenderWindow &window)
{
  sf::Texture texture; texture.loadFromImage(frameBuffer);
  texture.setSmooth(true);
  sf::Sprite sprite; sprite.setTexture(texture);
  sprite.setScale(1.0f / MSAA, 1.0f / MSAA);
  window.draw(sprite);
  window.display();
}

void Scene::RenderColumns(int n)
{
    int mod = 3;
    ClearFrameBuffer( Vec3ToColor(ClearColor) );
    ClearDepthBuffer();

    float lastShownPercentage = 0.0f; float percentageStep = 0.005f;
    for(int x = -WindowWidth/2 + n; x < WindowWidth/2; x += mod)
    {
        for(int y = -WindowHeight/2; y < WindowHeight/2; ++y)
        {
            Ray ray; GetRayFromPixel(x, y, ray);
            Intersection intersection;
            if(RayTrace(ray, intersection))
            {
                SetDepthAt(x, y, intersection.point.z);
                glm::vec3 pixelColor = GetPixelColor(ray, 0, true, true);
                frameBuffer.setPixel(x + WindowWidth/2, y + WindowHeight/2, Vec3ToColor(pixelColor));
            }
            
            //Print percentage
            float percentage = float((x+WindowWidth/2) * WindowHeight + y + WindowHeight/2) / (WindowWidth*WindowHeight);
            if(percentage - lastShownPercentage > percentageStep) 
            { lastShownPercentage = percentage; cout <<  n << ": " << (DepthOfFieldEnabled ? (percentage*100.0f)/2 : (percentage*100.0f)) << "%" << endl; }
        }
    } 
}

void Scene::Render() {
  int nThreads = 3;
  thread threads[nThreads];
  for (int i = 0; i < nThreads; ++i)
  {
    threads[i] = thread(&Scene::RenderColumns, this, i);
  }
  
  for (int i = 0; i < nThreads; ++i) threads[i].join();
  
  
  if(DepthOfFieldEnabled) ApplyDepthOfField();
}

void Scene::ApplyDepthOfField()
{
    sf::Image originalFrameBuffer;
    originalFrameBuffer.create(frameBuffer.getSize().x, frameBuffer.getSize().y);
    originalFrameBuffer.copy(frameBuffer, 0, 0);

    float lastShownPercentage = 0.0f; float percentageStep = 0.00005f;
    for(int x = -WindowWidth/2; x < WindowWidth/2; ++x)
    {
        for(int y = -WindowHeight/2; y < WindowHeight/2; ++y)
        {
          float depth = GetDepthAt(x,y);
          //if (depth < Scene::InfiniteDepth*0.99)
          {
            double distanceToFocus = abs(depth - DepthOfField);

            int radius = ceil(distanceToFocus) * MSAA;
            //radius *= radius;
            if (radius % 2 == 0) ++radius;
            radius = min(radius, 15);

            vector< vector<double> > kernel; 
            GetGaussianKernel(radius, kernel); 
            glm::vec3 color = glm::vec3(0);
            for (int i = 0; i < radius; ++i)
            {
              for (int j = 0; j < radius; ++j)
              {
                int ix = x + i - radius/2  + WindowWidth/2, iy = y + j - radius/2 + WindowHeight/2;
                ix = min(WindowWidth, max(0, ix));
                iy = min(WindowHeight, max(0, iy));
                color += ColorToVec3(originalFrameBuffer.getPixel(ix, iy)) * float(kernel[i][j]);
              }
            }
            frameBuffer.setPixel(x + WindowWidth/2, y + WindowHeight/2, Vec3ToColor(color));
          }
            
          float percentage = float((x+WindowWidth/2) * WindowHeight + y + WindowHeight/2) / (WindowWidth*WindowHeight);
          if(percentage - lastShownPercentage > percentageStep) 
          { lastShownPercentage = percentage; cout << (percentage*100.0f)/2 + 50.0f << "%" << endl; }

      }
    }   
}

void Scene::GetGaussianKernel(int r, vector < vector<double> >& kernel) 
{
  double sigma = 25;
  kernel = vector< vector<double> > (r, vector<double>(r));
  double mean = r/2;
  double sum = 0.0; // For accumulating the kernel values
  for (int x = 0; x < r; ++x) 
      for (int y = 0; y < r; ++y)
      {
          //kernel[x][y] = exp( -0.5 * (pow((x-mean)/(sigma), 2.0) + pow((y-mean)/(sigma),2.0)) ) / (2 * M_PI * sigma * sigma);
          kernel[x][y] = exp( -1.0 * ( (x-mean)*(x-mean) + (y-mean)*(y-mean)) / (2.0*sigma*sigma) )
                         / (2 * M_PI * sigma * sigma);

          // Accumulate the kernel values
          sum += kernel[x][y];
      }

  // Normalize the kernel
  for (int x = 0; x < r; ++x) 
      for (int y = 0; y < r; ++y) 
          //kernel[x][y] = 1.0f/(r*r);
          kernel[x][y] /= sum;
}


void Scene::SetCamera(glm::dvec3 _Position, glm::dvec3 _Rotation, double _FOV, double _DepthOfField, int _MSAA, int _WindowWidth, int _WindowHeight)
{
    Fov = _FOV;
    MSAA = _MSAA;
    DepthOfField = _DepthOfField;
    WindowWidth  = _WindowWidth  * _MSAA;
    WindowHeight = _WindowHeight * _MSAA;

    CameraPosition = _Position;
    CameraRotation = _Rotation;

    AspectRatio = double(WindowWidth) / WindowHeight;
    RFov = Fov * 3.1415926535f/180.0; //rads

    //ZNear = 5.0;
    //InfiniteDepth = 999999999.0;
    ViewportWidth  = ZNear * tan(RFov/2);
    ViewportHeight = ViewportWidth / AspectRatio;

    frameBuffer.create(WindowWidth, WindowHeight);
    timeCount = 0.0;

    depthBuffer = vector<double>(WindowWidth * WindowHeight);
    ClearDepthBuffer();
}
