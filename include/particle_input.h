//! this function is for reading particle generator information

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
void read_generator(std::string& inputfile, unsigned& num_particles,double& min_radius, double& max_radius,unsigned& num_particles_class, unsigned& num_classes,double& alpha, double& beta){
  
  std::string line;
  
  std::ifstream infile(inputfile);

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
              }
        else if (line.find("*MIN_RADIUS")!=std::string::npos){
             std::getline(infile, line);
             std::istringstream istream(line);
             istream >> min_radius;
             }
                else if (line.find("*MIN_PARTICLE")!=std::string::npos){
             std::getline(infile, line);
             std::istringstream istream(line);
             istream >> num_particles_class;
             }

        else if (line.find("*NUM_CLASSES")!=std::string::npos){
             std::getline(infile, line);
             std::istringstream istream(line);
             istream >> num_classes;
             }
        else if(line.find("*ALPHA")!=std::string::npos){
             std::getline(infile, line);
             std::istringstream istream(line);
             istream >> alpha;
           
             }
        else if(line.find("*BETA")!=std::string::npos){
             std::getline(infile, line);
             std::istringstream istream(line);
             istream >> beta;
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
  
