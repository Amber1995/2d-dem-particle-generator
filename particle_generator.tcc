//! print the particle information
template <unsigned Tdim>
void ParticleGenerator <Tdim>::particles_info() {

  for(const auto& grain:vec_particles_ptr_)
    grain->info();

}
