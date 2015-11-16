#include <iostream>
#include <ctime>
#include <cstdlib>

class Particle{

public:

  double x,y,z;
  double radius;
  Particle(double,double,double,double);
  
}

  Particle::Particle(double x1,double y1,double z1,double r)
  {
    x=x1;
    y=y1;
    z=z1;
    radius=r;
  }

