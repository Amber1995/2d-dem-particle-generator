#ifndef DEM_PARTICLE_H_
#define DEM_PARTICLE_H_

#include <array>
#include <iostream>
#include <limits>

//! brief base class containder for a single DEM particle

template <unsigned Tdim>
class Particle {

 public:
  //! reference to an object and constructor initialization

  //! the first Particle constructor is for storing granular information
  Particle(const unsigned& id, const std::array<double, Tdim>& coordinates,
           const double& radius)
      : id_{id}, radius_{radius} {
    static_assert(Tdim==2 || Tdim == 3,"Undefined dimension.");
    coordinates_ = coordinates;
  }

  //! the second Particle constructor is for the particle_generator loop
  Particle(const unsigned& id, const double& radius)
    :id_{id},radius_{radius} {coordinates_.fill(std::numeric_limits<double>::max());}
  

  unsigned id() const { return id_; }

  std::array<double, Tdim> coordinates() const { return coordinates_; }

  void coordinates(const std::array<double, Tdim>& coordinates) {
    coordinates_ = coordinates;
  }

  double radius() const { return radius_; }

  void radius(const double& radius) { radius_ = radius; }
    
  //! print the variables in the file particle.tcc
  void info();

 private:
  unsigned id_;
  std::array<double, Tdim> coordinates_;
  double radius_;


};

#include "particle.tcc"
#endif  // DEM_PARTICLE_H_
