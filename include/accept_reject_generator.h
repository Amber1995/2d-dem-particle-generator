#ifndef DEM_ACCEPT_REJECT__GENERATOR_H_
#define DEM_ACCEPT_REJECT__GENERATOR_H_

#include <memory>
#include <vector>

#include "particle.h"
#include "particle_generator.h"

//! \tparam Tdim - the dimension (2 or 3) of particle
template <unsigned Tdim>
//! \brief Derived class to generate particles using acceptance-rejection method proposed by Von Neumann
class AcceptRejectGenerator : public ParticleGenerator<Tdim>{

public:
//! AcceptRejectGenerator constructor with information to generator particles with beta function
AcceptRejectGenerator(const unsigned& num_particles, const double& min_radius, const double& max_radius, double& alpha,const double& beta)
  :ParticleGenerator<Tdim>(num_particles, min_radius,max_radius),alpha_{alpha},beta_{beta}{}
  
  ~AcceptRejectGenerator(){};

  //! Function to generate particles based on beta distribution
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

private:
  //! Private variables alpha and beta in beta function
  double alpha_;
  double beta_;
};

#include "accept_reject_generator.tcc"
#endif
