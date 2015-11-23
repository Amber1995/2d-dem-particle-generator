#include <iostream>
#include <memory>

#include "particle.h"
#include "particle_generator.h"

int main() {

  //! initialize the variables
  const unsigned Dim = 3;
  unsigned id = 0;
  double radius = 1.;
  unsigned total_numbers = 100;
  double min_radius = 1.;
  double max_radius = 10.;

  std::array<double, Dim> coordiantes = {0., 0.,0.};

    auto grain = std::make_shared <Particle<Dim>>(id, coordiantes, radius);

  //(*grain).info();
  grain->info();
}
