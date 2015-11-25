#include <memory>

#include "particle_generator.h"

int main() {
  
  const unsigned Dim = 3;
  std::array<double,Dim> coordinates={0.,0.,0.}; 
  const double radius=1.;
  unsigned num_particles = 100;
  double min_radius = 0.1;
  double max_radius = 10.;

    
  //! create a ParticleGenerator object called grainGenerator
  
  auto grain_generator = std::make_shared <ParticleGenerator<Dim>>(num_particles,min_radius,max_radius);

  grain_generator->generator();


}
