//! to generate particles with beta distribution
#include <cmath>
#include <random>

template <unsigned Tdim>
void BetaParticleGenerator<Tdim>::generator() {

  const double Pi = 3.141592653589793;
  double volume = std::numeric_limits<double>::min();

  double gaps = std::numeric_limits<double>::min();
  double low_radius = std::numeric_limits<double>::min();
  double up_radius = std::numeric_limits<double>::max();
  double middle_radius =
      std::numeric_limits<double>::min();  //! to do integrate
  double beta_function = std::numeric_limits<double>::min();
  double cum_beta = std::numeric_limits<double>::min();  //! the cumulative beta
                                                         //! distribution in a
                                                         //! single class

  double mean_radius =
      std::numeric_limits<double>::min();  //! the mean radius of a single class
  std::vector<double> vec_mean_radius;     //! to store the particle radius of a
                                           //! class in the vector
  vec_mean_radius.reserve(num_classes_);

  double num_subparticles =
      std::numeric_limits<double>::min();  //! the number of particles in the
                                           //! class for a unit of total volume
  double min_num_subparticles =
      std::numeric_limits<double>::max();  //! the minumun number of particles
                                           //! in all classes
  double temp_num_particles_class =
      std::numeric_limits<double>::min();  //! the temporary number of particles
                                           //! in class i
  unsigned total_particles = std::numeric_limits<unsigned>::min();

  std::vector<unsigned> vec_num_particles_class;  //! to store the number of
                                                  //! particles of a class in
                                                  //! the vector
  vec_num_particles_class.reserve(num_classes_);

  //! the variables is for generating particles using accept-reject method
  double lamda = std::numeric_limits<double>::min();
  double r1 = std::numeric_limits<double>::min();
  double r2 = std::numeric_limits<double>::min();
  double lamda_radius = std::numeric_limits<double>::min();

  double radius = std::numeric_limits<double>::min();
  std::random_device generator;
  std::uniform_real_distribution<> distribution(0, 1);

  gaps = 1.0 / num_classes_;

  //! to calculate the number of particles in a class for a unit total volume
  for (unsigned i = 0; i < num_classes_; ++i) {
    low_radius = gaps * i;
    up_radius = low_radius + gaps;
    middle_radius = (low_radius + up_radius) / 2;

    beta_function = (std::tgamma(alpha_ + beta_)) /
                    (std::tgamma(alpha_) * std::tgamma(beta_)) *
                    (std::pow(middle_radius, alpha_ - 1)) *
                    (std::pow(1 - middle_radius, beta_ - 1));

    cum_beta = beta_function * middle_radius;

    mean_radius = 2 * low_radius * up_radius / (low_radius + up_radius);
    vec_mean_radius.push_back(mean_radius);  //! the vector of particle radius

    if (Tdim == 2) volume = Pi * mean_radius * mean_radius * 1.0;
    else if (Tdim == 3) volume = 4 * Pi * std::pow(mean_radius, 3) / 3;
    

    num_subparticles = cum_beta / volume;

    if (min_num_subparticles > num_subparticles)
      min_num_subparticles = num_subparticles;
    temp_num_particles_class =
        num_particles_class_ / min_num_subparticles * num_subparticles;
    vec_num_particles_class.push_back(
        temp_num_particles_class);  //! the vector of particle number
  }

  vec_num_particles_class.at(0) = num_particles_class_;

  //! to ensure the number of generated particles is more than the minimum
  //! number of particles "num_particles" required for the construction of the
  //! packing
  for (unsigned i = 0; i < num_classes_; ++i) {
    total_particles += vec_num_particles_class.at(i);
    // std::cout<<vec_num_particles_class.at(i)<<std::endl;
  }

  for (unsigned i = 0; i < num_classes_; ++i) {
    if (total_particles < num_particles_) {
      vec_num_particles_class.at(i) = static_cast<int>(
          static_cast<double>(num_particles_ / total_particles) *
          vec_num_particles_class.at(i));
    }
  }

  //  unsigned i=0;
  //  unsigned j=0;
  //  gaps = (max_radius_-min_radius_)/num_classes_;
  //   for(unsigned i=0; i<num_classes_;++i){
  //     low_radius = min_radius_+gaps*i;
  //     up_radius = low_radius+gaps;
  //     for (unsigned id=j; id<j+vec_num_particles_class.at(i); ++id){
  //        do
  //        {
  //        r1=distribution(generator);
  //        r2=distribution(generator);
  //        radius = low_radius+(up_radius-low_radius)*r1;
  //        lamda_radius =
  //        lamda*(std::tgamma(alpha_+beta_))/((std::tgamma(alpha_))*(std::tgamma(beta_)))*(std::pow(radius,alpha_-1))*(std::pow(radius,beta_-1));
  //        } while (r2 <= lamda_radius);
  //        std::cout<<id<<"   "<<radius<<std::endl;
  //         auto grain = std::make_shared <Particle<Tdim>>(id, radius);
  //        vec_particles_ptr_.push_back(grain);
  //     }
  //     j += vec_num_particles_class.at(i);
  //   }

  unsigned id = 0;
  gaps = (max_radius_ - min_radius_) / num_classes_;
  for (unsigned i = 0; i < num_classes_; ++i) {
    low_radius = min_radius_ + gaps * i;
    up_radius = low_radius + gaps;
    for (unsigned j = 0; j < vec_num_particles_class.at(i); ++j) {
      radius = static_cast<double>(std::rand()) /
                   (static_cast<double>(RAND_MAX)) * (up_radius - low_radius) +
               low_radius;
      auto grain = std::make_shared<Particle<Tdim>>(id, radius);
      vec_particles_ptr_.push_back(grain);
      ++id;
    }
  }
}
