#include <cstdlib>  //!srand, rand
#include <ctime>  //!time

#include <memory>
#include <vector>

//! to generate particles
template <unsigned Tdim>
void RandomParticleGenerator<Tdim>::generator(){
  
  std::srand (std::time(nullptr));

  for (unsigned id=0; id<num_particles_; ++id){
    double radius=static_cast<double>(std::rand())/(static_cast<double>(RAND_MAX))*(max_radius_ - min_radius_)+min_radius_;
    auto grain = std::make_shared <Particle<Tdim>>(id, radius);
      vec_particles_ptr_.push_back(grain);
  }
  
}
