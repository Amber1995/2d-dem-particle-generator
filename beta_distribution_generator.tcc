//! to generate particles with beta distribution
#include <cmath>

template <unsigned Tdim>
void BetaParticleGenerator<Tdim>::generator(){

const double Pi = 3.141592653589793;
double volume = std::numeric_limits<double>::min();

std::vector<unsigned> vec_num_particles;
vec_num_particles.reserve(num_intervals_);

std::vector<double> vec_mean_radius;
vec_mean_radius.reserve(num_intervals_);

//! the cumulative beta distribution in a single class
double cum_beta = std::numeric_limits<double>::min();

//! the mean radius in a single class
double mean_radius = std::numeric_limits<double>::min();

  //! the number of particles in a single class
unsigned num_subparticles = std::numeric_limits<unsigned>::min();

  //! the minimum number of particles in all classes
unsigned min_num_subparticles = std::numeric_limits<unsigned>::max();

  //! the total number of particles obtained by the parameters min_class_particles
double total_particles = std::numeric_limits<double>::max();

double gaps = std::numeric_limits<double>::min();
double low_radius = std::numeric_limits<double>::min();
double up_radius = std::numeric_limits<double>::max();
double middle_radius = std::numeric_limits<double>::max();
double beta_function = std::numeric_limits<double>::max();

gaps = (max_radius_ - min_radius_) / num_intervals_;

//! to determine the amount of the particles in the class for a unit total volume
for(unsigned i = 0; i < num_intervals_; ++i){
low_radius = min_radius_ + gaps*i;
up_radius = min_radius_ + gaps*(i+1);
middle_radius = (low_radius + up_radius)/2;

beta_function = (std::tgamma(alpha_+beta_))/((std::tgamma(alpha_))*(std::tgamma(beta_)))*(std::pow(middle_radius,alpha_-1))*(std::pow(1-middle_radius,beta_-1));

cum_beta = beta_function*middle_radius;

mean_radius = (up_radius-low_radius)*0.5/(up_radius*(0.5-low_radius));
vec_mean_radius.push_back(mean_radius);

   if (Tdim == 2){
      volume =  Pi*vec_mean_radius.at(i)*vec_mean_radius.at(i)*1.0;
      }
    else if(Tdim ==3){
      volume = 4.0*Pi*std::pow(vec_mean_radius.at(i),3)/3.0;
    }

num_subparticles = static_cast<int>(cum_beta/volume);
vec_num_particles.push_back(num_subparticles);
std::cout<<vec_num_particles.at(i)<<std::endl;
if (min_num_subparticles > vec_num_particles.at(i)) min_num_subparticles = vec_num_particles.at(i);
}

//! to ensure each class constains at least min_class_particles
  for (unsigned i=0; i<num_intervals_;++i){
vec_num_particles.at(i)= static_cast<int>(min_class_particles_/min_num_subparticles*vec_num_particles.at(i));
total_particles += vec_num_particles.at(i);
 }

//! to ensure the number of generated particles is more than the minimum number of particles 'num_particles' required for the construction of the packing
// if(total_particles < num_particles_){
//    for (unsigned i=0; i<num_intervals_;++i){
//vec_num_particles.at(i) = static_cast<int>(num_particles_/total_particles*vec_num_particles.at(i));
//  }
// }

//  for (unsigned i=0; i<num_intervals_;++i){

//auto grain = std::make_shared<Particle<Tdim>>(vec_num_particles.at(i),vec_mean_radius.at(i));

//      vec_particles_ptr_.push_back(grain);
//  }

}

