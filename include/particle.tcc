//! \param outfile is the name of the output file
template <unsigned Tdim>

//! Function to print particle information to .csv file
void Particle <Tdim>::info(std::ofstream& outfile) {

//! outfile << "Particle ID,Radius,\n";
  outfile<<radius_<<"\n";

// for(const auto& coordinate:coordinates_)
//    std::cout<<coordinate<<"";
//    std::cout<<std::endl;
}
