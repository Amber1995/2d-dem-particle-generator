//! print the particle information

template <unsigned Tdim>
void ParticleGenerator <Tdim>::particles_info(std::string& outputfile) {

  std::ofstream outfile(outputfile);
    
  for(const auto& grain:vec_particles_ptr_)
    grain->info(outfile);

}
