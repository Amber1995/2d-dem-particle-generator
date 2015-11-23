#ifndef DEM_PARTICLE_GENERATOR_H_
#define DEM_PARTICLE_GENERATOR_H_

#include "particle.h"

//! base class containder for generating particles with certain numbers
//! Particle_generator is derived from Particle

class Particle_generator: public Particle
{
public:
Particle_generator(const unsigned& total_numbers,const double& min_radius, const double& max_radius)
  :total_numbers_{total_numbers},min_radius_{min_radius}, max_radius_{max_radius};

  unsigned total_numbers() const{return total_numbers_;}
  
  double min_radius() const {return min_radius_;}

  void min_radius(const double& min_radius){min_radius_=min_radius;}

  double max_radius() const {return max_radius_;}

  void max_radius(const double& max_radius){max_radius_=max_radius;}

  void generator();
private:
  unsigned total_numbers_;
  double min_radius_;
  double max_radius_;
  
}

//! print out the information of all the particles(id, radius & coordinates)
#include "generator.cc"

#endif  //DEM_PARTICLE_GENERATOR_H
