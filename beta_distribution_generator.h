#ifndef DEM_BETA_DISTRIBUTION_PARTICLE_GENERATOR_H_
#define DEM_BETA_DISTRIBUTION_PARTICLE_GENERATOR_H_

#include <memory>
#include <vector>

#include "particle.h"
#include "particle_generator.h"

//! derived class
template <unsigned Tdim>
class BetaParticleGenerator : public ParticleGenerator<Tdim>{

public:

BetaParticleGenerator(const unsigned& num_particles, const double& min_radius, const double& max_radius, const unsigned& min_class_particles, const unsigned& num_intervals, double& alpha,const double& beta)
  :ParticleGenerator<Tdim>(num_particles, min_radius,max_radius),min_class_particles_{min_class_particles},num_intervals_{num_intervals},alpha_{alpha},beta_{beta}{}
  
  ~BetaParticleGenerator(){};
  
  void generator();
  
protected:
  using ParticleGenerator<Tdim>::num_particles_;
  using ParticleGenerator<Tdim>::min_radius_;
  using ParticleGenerator<Tdim>::max_radius_;
  using ParticleGenerator<Tdim>::vec_particles_ptr_;

private:
  unsigned min_class_particles_;
  unsigned num_intervals_;
  double alpha_;
  double beta_;
};

#include "beta_distribution_generator.tcc"
#endif
