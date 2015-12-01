#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <cstdlib>
#include <memory>

//#include "readInputInfo.cc"
#include "particle_generator.h"
#include "random_particle_generator.h"


int main(int argc, char** argv) {

  const unsigned Dim = 3;
  double min_radius = 10.;
  double max_radius = 1.;
  unsigned num_particles = 100;

  std::string inputfile, outputfile;
  std::string line;

  if (argc == 3){
    inputfile = argv[1];
    outputfile = argv[2];
  } else {
    std::cerr<<"Incorret number of arguments."<<std::endl;
    std::exit(EXIT_FAILURE);
  }
  
  std::ifstream infile("inputfile");
  // std::ofstream outfile(outputfile);
  // int readInputInfo(char[],int&,double&,double&);

    
  //! read the generator information
   if(infile.good())
  {
    while (std::getline(infile, line)) {
      std::istringstream istream(line);
      if(line!=""){    //! skip blank line

        while(istream.good())
        {
          if (line.find("*NUM_PARTICLES")){
              std::getline(infile, line);
              std::istringstream istream(line);
              istream >> num_particles;
              }
          else if (line.find("*MAX_RADIUS")){
              std::getline(infile, line);
              std::istringstream istream(line);
              istream >> max_radius;}
          else if (line.find("MIN_RADIUS")){
              std::getline(infile, line);
              std::istringstream istream(line);
              istream >> min_radius;}
          else if (line.find("*END")){
            break;} 
        }
      }
      
     }
    infile.close();
    }
  else std::cerr<<"Unable to open file";
  
  //! make sure the max_radius is always larger than the min_radius
   if (min_radius > max_radius) std::swap(min_radius, max_radius);

  std::shared_ptr<ParticleGenerator<Dim>> grain_generator = std::make_shared<RandomParticleGenerator<Dim>>(num_particles, min_radius,max_radius);

   grain_generator->generator();

   grain_generator->particles_info();

}
