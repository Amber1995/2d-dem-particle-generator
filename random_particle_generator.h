#ifndef DEM_RANDOM_PARTICLE_GENERATOR_H_
#define DEM_RANDOM_PARTICLE_GENERATOR_H_

#include <memory>
#include <vector>

#include "particle.h"
#include "particle_generator.h"

template <unsigned Tdim>
class RandomParticleGenerator : public ParticleGenerator<Tdim> {
  
public:

  RandomParticleGenerator(const unsigned& num_particles,const double& min_radius, const double& max_radius)
    : ParticleGenerator( num_particles, min_radius,  max_radius){};
  // void generator();

  private:
  unsigned num_particles_;
  double min_radius_;
  double max_radius_;
   std::vector<std::shared_ptr<Particle<Tdim>>> vec_particles_ptr_;
  
};

//#include "generator.tcc"
#endif
