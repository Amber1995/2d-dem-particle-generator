#ifndef DEM_RANDOM_PARTICLE_GENERATOR_H_
#define DEM_RANDOM_PARTICLE_GENERATOR_H_

#include <memory>
#include <vector>

#include "particle.h"
#include "particle_generator.h"

//! \param Tdim - the dimension (2 or 3) of grains
template <unsigned Tdim>
//! \brief Derived class container for generating particles randomly between the minimum radius and maximum radius
class RandomParticleGenerator : public ParticleGenerator<Tdim> {
  
public:
  //! RandomParticleGenrator constructor for generating random particles
  RandomParticleGenerator(const unsigned& num_particles,const double& min_radius, const double& max_radius)
    : ParticleGenerator<Tdim>(num_particles,min_radius, max_radius){}

  //! Destructor for RandomParticleGenerator
  ~RandomParticleGenerator(){};

  //! Function to generate particles based on random distribution
  void generator();

protected:
  //! Derived class uses public member access specifier to derive from base class,meaning of these variables can be found in ParticleGenerator
  //! Total number of particles
  using ParticleGenerator<Tdim>::num_particles_;
  //! minimum radius of generated particles
  using ParticleGenerator<Tdim>::min_radius_;
  //! maximum radius of generated particles
  using ParticleGenerator<Tdim>::max_radius_;
  //! vector of particle pointers
  using ParticleGenerator<Tdim>::vec_particles_ptr_;
};

#include "random_particle_generator.tcc"
#endif
