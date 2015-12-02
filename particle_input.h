//! this function is for reading particle generator information

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void read_generator(const int& argc, char** argv, unsigned& num_particles,double& max_radius ,double& min_radius){

  std::string inputfile, outputfile;
  std::string line;
  
  if (argc == 3){
    inputfile = argv[1];
    outputfile = argv[2];
  } else {
    std::cerr<<"Incorret number of arguments."<<std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::ifstream infile(inputfile);
  std::ofstream outfile(outputfile);

//! read the generator information
   if(infile.good())
  {
    while (std::getline(infile, line)) {
      // std::cout<<__FILE__ << __LINE__ <<"   "<<line<<std::endl;
      if(line!=""){    //! skip blank line

        if (line.find("*NUM_PARTICLES")!=std::string::npos){
              std::getline(infile, line);
              std::istringstream istream(line);
              istream >> num_particles;
              }
        else if (line.find("*MAX_RADIUS")!=std::string::npos){
              std::getline(infile, line);
              std::istringstream istream(line);
              istream >> max_radius;
              outfile << num_particles;
          }
          else if (line.find("MIN_RADIUS")!=std::string::npos){
             std::getline(infile, line);
             std::istringstream istream(line);
             istream >> min_radius;
          }
          else if (line.find("*END")){
            break;}
        }
     }
    infile.close();
  }
  else std::cerr<<"Unable to open file";

   //! make sure the max_radius is always larger than the min_radius
  if (min_radius > max_radius) std::swap(min_radius, max_radius);

  
}
  
