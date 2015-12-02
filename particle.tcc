//! print the particle information to the terminal

template <unsigned Tdim>
void Particle <Tdim>::info() {

  std::cout << "Particle ID " << id_ << std::endl;

  std::cout<<"Coordinates ";
  
  for(const auto &coordinate:coordinates_)
     std::cout<<coordinate<<' ';
  std::cout << std::endl;
  
  std::cout << "Particle radius " << radius_ << std::endl;
}
