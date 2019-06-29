#include <cstdlib>  
#include <ctime>


template <unsigned Tdim>
//! Function to generate random particles
void RandomParticleGenerator<Tdim>::generator() {
  //!
  std::srand(std::time(nullptr));

  //! Generates particles by using rand()
  for (unsigned id = 0; id < num_particles_; ++id) {
    double radius = static_cast<double>(std::rand()) /
                        (static_cast<double>(RAND_MAX)) *
                        (max_radius_ - min_radius_) +
                    min_radius_;

    //! Uses smart pointer to store the information of particle id and radius
    auto grain = std::make_shared<Particle<Tdim>>(id, radius);

    //! Stores the information of particles in the vector
    vec_particles_ptr_.push_back(grain);
  }
}
