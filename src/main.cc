#include <iostream>
#include <limits>
#include <memory>

#include <cstdlib>

#include "particle_generator.h"
#include "particle_input.h"
#include "random_particle_generator.h"
#include "accept_reject_generator.h"
#include "beta_distribution_generator.h"

// Generate particles in the DEM simulation using different constructors
// \param argc argv    Command line arguments
int main(int argc, char** argv) {
  
  // if you want to generate ciculars, set Dim = 2; if sphere, Dim = 3
  const unsigned Dim = 3;

  // the total number of particles in DEM generation process
  unsigned num_particles = std::numeric_limits<unsigned>::min();
  
  // the minimum radius of particles in DEM generation process
  double min_radius = std::numeric_limits<double>::min();
  
  // the maximum radius of particles in DEM generation process
  double max_radius = std::numeric_limits<double>::max();
  
  // that alph, bata are parameters in beta function
  double alpha = std::numeric_limits<double>::min();
  double beta = std::numeric_limits<double>::min();
  // Used to ensure the number of particles in each class more than a certain number
  unsigned num_particles_class = std::numeric_limits<unsigned>::min();
  // that the number of classes devided in the interval [0,1] in beta function
  unsigned num_classes = std::numeric_limits<unsigned>::min();

  //! the name of the inputfile and outputfile
  std::string inputfile, outputfile;

  //! to make sure correct command-line arguments are entered
  if (argc == 3){
    inputfile = argv[1];
    outputfile = argv[2];
  } else {
    std::cerr<<"Incorret number of arguments."<<std::endl;
    std::exit(EXIT_FAILURE);
  }

  //! to read the generation control information from  file
  read_generator(inputfile,num_particles,min_radius,max_radius,num_particles_class,num_classes,alpha,beta);
  
  //! to construct the object of type ParticleGenerator and wrap it in grain_generator using args&& num_particles, max_radius, min_radius etc.
  // std::shared_ptr<ParticleGenerator<Dim>> grain_generator = std::make_shared<RandomParticleGenerator<Dim>>(num_particles, min_radius,max_radius);
  
//read_generator(inputfile,num_particles,min_radius,max_radius,alpha,beta);
  //std::shared_ptr<ParticleGenerator<Dim>> grain_generator = std::make_shared<AcceptRejectGenerator<Dim>>(num_particles,min_radius,max_radius,alpha,beta);

  std::shared_ptr<ParticleGenerator<Dim>> grain_generator = std::make_shared<BetaParticleGenerator<Dim>>(num_particles,min_radius,max_radius,num_particles_class,num_classes,alpha,beta);
  
   //! to generate all particles
   grain_generator->generator();
   
   //! to print out all particles information to .csv file
   grain_generator->particles_info(outputfile);
  

}
