#include <iostream>
#include <memory>

#include "particle.h"

int main() {

  //! initialize the variables
  const unsigned Dim = 3;
  unsigned id = 0;
  double radius = 1.;

  std::array<double, Dim> coordiantes = {0., 0.,0.};

    auto grain = std::make_shared <Particle<Dim>>(id, coordiantes, radius);

  //(*grain).info();
  grain->info();
}
