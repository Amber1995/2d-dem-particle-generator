//! to generate particles with beta distribution
#include <cmath>
#include <random>

template <unsigned Tdim>
void BetaParticleGenerator<Tdim>::generator(){

  double lamda = std::numeric_limits<double>::min();
  double r1 = std::numeric_limits<double>::min();
  double r2 = std::numeric_limits<double>::min();
  double lamda_radius = std::numeric_limits<double>::min();

  double radius = std::numeric_limits<double>::min();
  std::random_device generator;
  std::uniform_real_distribution<> distribution(0,1);

  for(unsigned id=0; id<num_particles_;++id){
    do
    {
  r1=distribution(generator);
  r2=distribution(generator);
  radius = min_radius_+(max_radius_-min_radius_)*r1;
  lamda_radius = lamda*(std::tgamma(alpha_+beta_))/((std::tgamma(alpha_))*(std::tgamma(beta_)))*(std::pow(radius,alpha_-1))*(std::pow(radius,beta_-1));

  }while (r2 <= lamda_radius);
auto grain = std::make_shared <Particle<Tdim>>(id, radius);

    vec_particles_ptr_.push_back(grain);
  }
  
}

