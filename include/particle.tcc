//! print a particle information to the csv file

template <unsigned Tdim>
void Particle <Tdim>::info(std::ofstream& outfile) {

//! outfile << "Particle ID,Radius,\n";

  outfile<<id_<<","<<radius_<<"\n";

// for(const auto& coordinate:coordinates_)
//    std::cout<<coordinate<<"";
//    std::cout<<std::endl;
}
