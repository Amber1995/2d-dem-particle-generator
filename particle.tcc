//! print the particle information
template <unsigned Tdim>
void Particle <Tdim>::info() {

  std::cout << "Particle ID " << id_ << std::endl;

  std::cout<<"Coordinates ";
  
  // range based for loop
//  for(auto it = coordinates_.begin();it != coordinate_.end;++it)
  //   std::cout<<' '<*it<<
  //    std::cout<<std::endl;
  
  for(const auto &coordinate:coordinates_)
     std::cout<<coordinate<<' ';
  std::cout << std::endl;
  
  std::cout << "Particle radius " << radius_ << std::endl;
}
