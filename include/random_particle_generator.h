#ifndef DEM_RANDOM_PARTICLE_GENERATOR_H_
#define DEM_RANDOM_PARTICLE_GENERATOR_H_

#include <memory>
#include <vector>

#include "particle.h"
#include "particle_generator.h"

//! \brief Derived class container for generating particles randomly between the minimum radius and maximum radius
//! \param Tdim - the dimension (2 or 3) of grains
template <unsigned Tdim>
class RandomParticleGenerator : public ParticleGenerator<Tdim> {
  
public:
  //! Constructor for random particle generator
  RandomParticleGenerator(const unsigned& num_particles,const double& min_radius, const double& max_radius)
    : ParticleGenerator<Tdim>(num_particles,min_radius, max_radius){}

  //! Destructor for random particle generator
  ~RandomParticleGenerator(){};

  //! Generates particles based on random distribution
  void generator();

protected:
  // Derived class uses public member access specifier to derive from base
  // meaning of these variables can be found in ParticleGenerator
  using ParticleGenerator<Tdim>::num_particles_;
  using ParticleGenerator<Tdim>::min_radius_;
  using ParticleGenerator<Tdim>::max_radius_;
  using ParticleGenerator<Tdim>::vec_particles_ptr_;
};

#include "random_particle_generator.tcc"
#endif
