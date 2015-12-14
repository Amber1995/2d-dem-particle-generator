#ifndef DEM_PARTICLE_H_
#define DEM_PARTICLE_H_

#include <array>
#include <fstream>
#include <limits>

// \brief Base class containder for DEM particles
// \details Has constructors with information of a particle, i.e. id, radius and coordinates
// \param TDIM - the dimension (2 or 3) of the DEM simulation

template <unsigned Tdim>
class Particle {

 public:

  // Initializes the constructor 
  Particle(const unsigned& id, const std::array<double, Tdim>& coordinates,
           const double& radius)
      : id_{id}, radius_{radius} {
    static_assert(Tdim==2 || Tdim == 3,"Undefined dimension.");
    coordinates_ = coordinates;
  }

  // used for the particle_generator loop
  Particle(const unsigned& id, const double& radius)
    :id_{id},radius_{radius} {coordinates_.fill(std::numeric_limits<double>::max());}
  
  // Returns the value of id
  unsigned id() const { return id_; }

  // Parameterizes constructor
  std::array<double, Tdim> coordinates() const { return coordinates_; }
  void coordinates(const std::array<double, Tdim>& coordinates) {
    coordinates_ = coordinates;
  }

  double radius() const { return radius_; }
  void radius(const double& radius) { radius_ = radius; }
    
  // the implementation of function info() is in the particle.tcc
  void info(std::ofstream& outfile);

 private:
  // the basic information of a particle
  // Particle ID
  unsigned id_;
  // Particle Coordinates
  std::array<double, Tdim> coordinates_;
  // Particle radius
  double radius_;
  
};

#include "particle.tcc"
#endif  // DEM_PARTICLE_H_
