#ifndef DEM_ACCEPT_REJECT__GENERATOR_H_
#define DEM_ACCEPT_REJECT__GENERATOR_H_

#include <memory>
#include <vector>

#include "particle.h"
#include "particle_generator.h"

//! derived class
template <unsigned Tdim>
class AcceptRejectGenerator : public ParticleGenerator<Tdim>{

public:

AcceptRejectGenerator(const unsigned& num_particles, const double& min_radius, const double& max_radius, double& alpha,const double& beta)
  :ParticleGenerator<Tdim>(num_particles, min_radius,max_radius),alpha_{alpha},beta_{beta}{}
  
  ~AcceptRejectGenerator(){};
  
  void generator();
  
protected:
  using ParticleGenerator<Tdim>::num_particles_;
  using ParticleGenerator<Tdim>::min_radius_;
  using ParticleGenerator<Tdim>::max_radius_;
  using ParticleGenerator<Tdim>::vec_particles_ptr_;

private:
  double alpha_;
  double beta_;
};

#include "accept_reject_generator.tcc"
#endif
