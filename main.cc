#include <memory>

#include "particle_generator.h"
#include "random_particle_generator.h"

int main() {
  
  const unsigned Dim = 3;
  unsigned num_particles = 100;
  double min_radius = 10.;
  double max_radius = 1.;
  
  std::shared_ptr<ParticleGenerator<Dim>> grain_generator = std::make_shared <RandomParticleGenerator<Dim>>(num_particles,min_radius,max_radius);

  grain_generator->generator();
  grain_generator->particles_info();

}
