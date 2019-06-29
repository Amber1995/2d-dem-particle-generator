#ifndef DEM_PARTICLE_GENERATOR_H_
#define DEM_PARTICLE_GENERATOR_H_

#include <memory>
#include <vector>

#include "particle.h"

//! \tparam Tdim - the dimension (2 or 3) of particles
template <unsigned Tdim>

//! \brief Base class for generating particles
class ParticleGenerator {

 public:
  //! ParticleGenerator constructor with particle generation information, i.e.
  //! number of particles, minimum and maximum radius of genrated particles
  ParticleGenerator(const unsigned& num_particles, const double& min_radius,
                    const double& max_radius)
      : num_particles_{num_particles},
        min_radius_{min_radius},
        max_radius_{max_radius} {}

  virtual ~ParticleGenerator() { vec_particles_ptr_.clear(); }

  virtual void generator() = 0;

  //! Function to print particles information
  void particles_info(std::string& outputfile);

 protected:
  //! total number of particles
  unsigned num_particles_;
  //! minimum radius of particles
  double min_radius_;
  //! maximum radius of particles
  double max_radius_;
  //! vector of shared particle pointers
  std::vector<std::shared_ptr<Particle<Tdim>>> vec_particles_ptr_;
};

#include "particle_generator.tcc"
#endif  // DEM_PARTICLE_GENERATOR_H
