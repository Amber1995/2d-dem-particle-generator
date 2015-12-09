#ifndef DEM_RANDOM_PARTICLE_GENERATOR_H_
#define DEM_RANDOM_PARTICLE_GENERATOR_H_

#include <memory>
#include <vector>

#include "particle.h"
#include "particle_generator.h"

//! derived class

template <unsigned Tdim>
class RandomParticleGenerator : public ParticleGenerator<Tdim> {
  
public:

  RandomParticleGenerator(const unsigned& num_particles,const double& min_radius, const double& max_radius)
    : ParticleGenerator<Tdim>(num_particles,min_radius, max_radius){}

  ~RandomParticleGenerator(){};
  
  void generator();

protected:
  
  using ParticleGenerator<Tdim>::num_particles_;
  using ParticleGenerator<Tdim>::min_radius_;
  using ParticleGenerator<Tdim>::max_radius_;
  using ParticleGenerator<Tdim>::vec_particles_ptr_;
};

#include "random_particle_generator.tcc"
#endif
