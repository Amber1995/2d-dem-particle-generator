#include <iostream>
#include <limits>
#include <memory>

#include <cstdlib>

#include "particle_generator.h"
#include "particle_input.h"
#include "random_particle_generator.h"

int main(int argc, char** argv) {

  const unsigned Dim = 3;
  double min_radius = std::numeric_limits<double>::min();
  double max_radius = std::numeric_limits<double>::max();
  unsigned num_particles = std::numeric_limits<unsigned>::min();

  std::string inputfile, outputfile;

  //! to use the command-line arguments
  if (argc == 3){
    inputfile = argv[1];
    outputfile = argv[2];
  } else {
    std::cerr<<"Incorret number of arguments."<<std::endl;
    std::exit(EXIT_FAILURE);
  }

  //! to read the generation control information from a file
  read_generator(inputfile,num_particles,max_radius,min_radius);

  std::shared_ptr<ParticleGenerator<Dim>> grain_generator = std::make_shared<RandomParticleGenerator<Dim>>(num_particles, min_radius,max_radius);

  //! to generate all particles
   grain_generator->generator();

   //! to print out all particles information to csv file
   grain_generator->particles_info(outputfile);

}
