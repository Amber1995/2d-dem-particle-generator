// Prints particle information to .csv file
// \param outfile is the name of the output file 

template <unsigned Tdim>
void Particle <Tdim>::info(std::ofstream& outfile) {

//! outfile << "Particle ID,Radius,\n";
  outfile<<id_<<","<<radius_<<"\n";

// for(const auto& coordinate:coordinates_)
//    std::cout<<coordinate<<"";
//    std::cout<<std::endl;
}
