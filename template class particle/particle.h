#ifndef DEM_PARTICLE_H_
#define DEM_PARTICLE_H_

#include <array>
#include <iostream>

//! brief base class containder for a single DEM particle

template <unsigned Tdim>
class Particle {

 public:
  //! Arguments passed by reference;
  Particle(const unsigned& id, const std::array<double, Tdim>& coordinates,
           const double& radius)
      : id_{id}, radius_{radius} {
    coordinates_ = coordinates;
  }

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
