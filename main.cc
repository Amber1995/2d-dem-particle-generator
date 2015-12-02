#include <iostream>
#include <limits>
#include <memory>

#include <cstdlib>

#include "particle_generator.h"
#include "particle_input.h"
#include "random_particle_generator.h"


int main(int argc, char** argv) {

  const unsigned Dim = 3;
  double min_radius = std::numeric_limits<double>::min();
  double max_radius = std::numeric_limits<double>::max();
  unsigned num_particles = std::numeric_limits<unsigned>::min();
  
  read_generator(argc,argv,num_particles,max_radius,min_radius);

  std::shared_ptr<ParticleGenerator<Dim>> grain_generator = std::make_shared<RandomParticleGenerator<Dim>>(num_particles, min_radius,max_radius);

   grain_generator->generator();

   grain_generator->particles_info();

}
