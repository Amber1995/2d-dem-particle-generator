#ifndef DEM_PARTICLE_GENERATOR_H_
#define DEM_PARTICLE_GENERATOR_H_

#include <memory>
#include <vector>

#include "particle.h"

//! \brief base class container for generating particles with certain numbers
template <unsigned Tdim>
class ParticleGenerator
{
public:

  //!
ParticleGenerator(const unsigned& num_particles,const double& min_radius, const double& max_radius)
  :num_particles_{num_particles},min_radius_{min_radius}, max_radius_{max_radius}{}

  virtual ~ParticleGenerator(){vec_particles_ptr_.clear();}
  
  virtual void generator() = 0;

  void particles_info();
  
protected:
  unsigned num_particles_;
  double min_radius_;
  double max_radius_;
  std::vector<std::shared_ptr<Particle<Tdim>>> vec_particles_ptr_;
};

#include "particle_generator.tcc"
#endif  //DEM_PARTICLE_GENERATOR_H
