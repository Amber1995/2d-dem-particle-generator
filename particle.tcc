//! print the variables in the file particle.tcc
template <unsigned Tdim>
void Particle <Tdim>::info() {

   static_assert(Tdim==2 | Tdim == 3,"Undefined dimension.");

  std::cout << "Particle ID " << id_ << std::endl;

  std::cout<<"Coordinates ";
  
  // range based for loop
  for(const auto &coordinate:coordinates_)
     std::cout<<coordinate<<' ';
  std::cout << std::endl;
  
  std::cout << "Particle radius " << radius_ << std::endl;
}
