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

BetaParticleGenerator(const unsigned& num_particles, const double& min_radius, const double& max_radius, const unsigned& num_particles_class, const unsigned& num_classes, double& alpha,const double& beta)
  :ParticleGenerator<Tdim>(num_particles, min_radius,max_radius),num_particles_class_{num_particles_class},num_classes_{num_classes},alpha_{alpha},beta_{beta}{}
  
  ~BetaParticleGenerator(){};
  //! $\Gamma_x = x + y$  
  void generator();
  
  
protected:
  using ParticleGenerator<Tdim>::num_particles_;
  using ParticleGenerator<Tdim>::min_radius_;
  using ParticleGenerator<Tdim>::max_radius_;
  using ParticleGenerator<Tdim>::vec_particles_ptr_;

private:
  unsigned num_particles_class_;
  unsigned num_classes_;
  double alpha_;
  double beta_;
  double betai(const double& a, const double& b,const double& x);
  double betacf(const double& a, const double& b,const double& x);
  double gammln(const double& xx );
};

#include "beta_distribution_generator.tcc"
#endif
