#ifndef DEM_PARTICLE_H_
#define DEM_PARTICLE_H_

#include <array>
#include <fstream>
#include <limits>


//! \tparam TDIM - Dimension (2 or 3) of the DEM simulation
template <unsigned Tdim>

//! \brief Base class for DEM particle information
//! \details A particle should have the information of particle id, radius and coordinates
class Particle {

 public:
  //! Particle constructor with particle id, radius and coordinates
  Particle(const unsigned& id, const std::array<double, Tdim>& coordinates,
           const double& radius)
      : id_{id}, radius_{radius} {
    static_assert(Tdim==2 || Tdim == 3,"Undefined dimension.");
    coordinates_ = coordinates;
  }

  //! Particle constructor with particle id and radius
  Particle(const unsigned& id, const double& radius)
    :id_{id},radius_{radius} {coordinates_.fill(std::numeric_limits<double>::max());}
  
  //! Function used to return particle id
  unsigned id() const { return id_; }

  //! Function used to return particle coordinates
  std::array<double, Tdim> coordinates() const { return coordinates_; }
  void coordinates(const std::array<double, Tdim>& coordinates) {
    coordinates_ = coordinates;
  }

  //! Function used to return particle radius
  double radius() const { return radius_; }
  void radius(const double& radius) { radius_ = radius; }
    
  //! Function to output the particle information to the file
  void info(std::ofstream& outfile);

 private:
  //! the basic information of a particle
  //! Particle id
  unsigned id_;
  //! Particle coordinates
  std::array<double, Tdim> coordinates_;
  //! Particle radius
  double radius_;
  
};

#include "particle.tcc"
#endif  // DEM_PARTICLE_H_
