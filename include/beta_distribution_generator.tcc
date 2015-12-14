//! to generate particles with beta distribution
#include <cmath>
#include <random>

template <unsigned Tdim>
void BetaParticleGenerator<Tdim>::generator() {

  const double Pi = 3.141592653589793;
  double volume = std::numeric_limits<double>::min();
  
  double min_num_particles_class = std::numeric_limits<double>::max();  //! the minumun number of particles in all classes
  unsigned total_particles = std::numeric_limits<unsigned>::min();

  std::vector<unsigned> vec_num_particles_class;  //! to store the number of particles of a class in the vector
  vec_num_particles_class.reserve(num_classes_);

  //! to calculate the number of particles in a class for a unit total volume
  for (unsigned i = 0; i < num_classes_; ++i) {
    double low_radius = 1.0/num_classes_ * i;
    double up_radius = low_radius + 1.0/num_classes_;
    double mean_radius = (low_radius + up_radius) / 2;

    double beta_function = (std::tgamma(alpha_ + beta_)) /
                    (std::tgamma(alpha_) * std::tgamma(beta_)) *
                    (std::pow(mean_radius, alpha_ - 1)) *
                    (std::pow(1 - mean_radius, beta_ - 1));
    
    double cum_beta = beta_function * mean_radius;       //! the cumulative beta distribution in a single class

    if (Tdim == 2) volume = Pi * mean_radius * mean_radius * 1.0;
    else if (Tdim == 3) volume = 4 * Pi * std::pow(mean_radius, 3) / 3;
    
    
    unsigned temp_num_particles_class = std::ceil(cum_beta / volume);  //! the number of particles in the class for a unit of total volume
      
    vec_num_particles_class.push_back(temp_num_particles_class);  //! the vector of particle number

    if (min_num_particles_class > temp_num_particles_class) min_num_particles_class = temp_num_particles_class;
    std::cout<<vec_num_particles_class.at(i)<<"   "<<std::endl;
  }

  //! vec_num_particles_class.at(i) is rescaled by a factor num_particles_class_ to make sure the number of particles in each class is more than a minumum value
  for (unsigned i = 0; i < num_classes_; ++i) {
    if(vec_num_particles_class.at(i)<num_particles_class_){
      vec_num_particles_class.at(i) = static_cast<int>(static_cast<double>(num_particles_class_) / static_cast<double>(min_num_particles_class)) * vec_num_particles_class.at(i);
      total_particles += vec_num_particles_class.at(i);
      std::cout<<vec_num_particles_class.at(i)<<"   "<<std::endl;
    }
  }
  std::cout<<"total_particles   "<<total_particles<<std::endl;
  
  //! to ensure the number of generated particles is more than the minimum  number of particles "num_particles" required for the construction of the packing
  for (unsigned i = 0; i < num_classes_; ++i) {
    if (total_particles < num_particles_){
      vec_num_particles_class.at(i) = static_cast<int>(static_cast<double>(num_particles_) / static_cast<double>(total_particles)) * vec_num_particles_class.at(i);
  
    }
  }

  unsigned id = 0;
  for (unsigned i = 0; i < num_classes_; ++i) {
    double low_radius = min_radius_ + (max_radius_ - min_radius_) / num_classes_ * i;
    double up_radius = low_radius + (max_radius_ - min_radius_) / num_classes_;
    for (unsigned j = 0; j < vec_num_particles_class.at(i); ++j) {
      double radius = static_cast<double>(std::rand()) / (static_cast<double>(RAND_MAX)) * (up_radius - low_radius) + low_radius;
      auto grain = std::make_shared<Particle<Tdim>>(id, radius);
      vec_particles_ptr_.push_back(grain);
      ++id;
    }
  }
}

//! Here we can use Von Neumann's Acceptance-Rejection method to generate particles randomly in each class

//! the variables is for generating particles using accept-reject method
//  double lamda = std::numeric_limits<double>::min();
//  double radius = std::numeric_limits<double>::min();

//  std::random_device generator;
//  std::uniform_real_distribution<> distribution(0, 1);

  //  unsigned i=0;
  //  unsigned j=0;
  //  gaps = (max_radius_-min_radius_)/num_classes_;
  //   for(unsigned i=0; i<num_classes_;++i){
  //     low_radius = min_radius_+gaps*i;
  //     up_radius = low_radius+gaps;
  //     for (unsigned id=j; id<j+vec_num_particles_class.at(i); ++id){
  //        do
  //        {
  //        double r1=distribution(generator);
  //        double r2=distribution(generator);
  //        radius = low_radius+(up_radius-low_radius)*r1;
  //        double lamda_radius =
  //        lamda*(std::tgamma(alpha_+beta_))/((std::tgamma(alpha_))*(std::tgamma(beta_)))*(std::pow(radius,alpha_-1))*(std::pow(radius,beta_-1));
  //        } while (r2 <= lamda_radius);
  //        std::cout<<id<<"   "<<radius<<std::endl;
  //         auto grain = std::make_shared <Particle<Tdim>>(id, radius);
  //        vec_particles_ptr_.push_back(grain);
  //     }
  //     j += vec_num_particles_class.at(i);
  //   }
