
template <unsigned Tdim>
//! Function to print the particle information
void ParticleGenerator <Tdim>::particles_info(std::string& outputfile) {

  //! output file
  std::ofstream outfile(outputfile);
  
  //! prints the generated particles by using vector of particle pointers  
  for(const auto& grain:vec_particles_ptr_)
    grain->info(outfile);

}
