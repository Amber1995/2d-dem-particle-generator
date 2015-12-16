//! to generate particles with beta distribution
#include <cmath>
#include <random>

template <unsigned Tdim>
void BetaParticleGenerator<Tdim>::generator() {

  const double Pi = 3.141592653589793;
  double volume = std::numeric_limits<double>::min();

  
  //! Minumun number of particles in all classes
  double min_num_particles_class = 10000000;

  //! Temporary total number of particles calculated by minimum number of particles in all classes
  double temp_total_particles = std::numeric_limits<double>::min();
  double raison = std::numeric_limits<double>::min();
  //! Vector of lower limit in each interval
  std::vector<double> vec_division;
  vec_division.reserve(num_classes_+1);

  //! Vector of volume per class
  std::vector<double> vec_volume_class;
  vec_volume_class.reserve(num_classes_);

  //! Vector of probability per class, equals to volume_per_class/volume_meanradius
  std::vector<double> vec_prob_class;
  vec_prob_class.reserve(num_classes_);
  
  //! Vector of number of particles per class, equals to unsigned<prob>
  std::vector<unsigned> vec_num_particles_class;
  vec_num_particles_class.reserve(num_classes_);

  double a = alpha_;
  double b = beta_;
  min_radius_ = min_radius_ *2;
  max_radius_ = max_radius_ *2;
  double interval = max_radius_ - min_radius_;
  //! The first step is to discretize the interval
  raison = std::exp((std::log(max_radius_)-std::log(min_radius_))/static_cast<double>(num_classes_));
  
  //! Initialized the vec_division to the value of raison
   for(unsigned i = 0;i < num_classes_+1;++i){
   vec_division.push_back(raison);
  }
  
  //! Calculates lower limit in each interval
  vec_division.at(0)=min_radius_;
  for(unsigned i=0;i<num_classes_;++i){
    vec_division.at(i+1) = vec_division.at(i)*raison;  
  }
  vec_division.at(num_classes_)=max_radius_;

  //! Calculates volume of each class
  for (unsigned i=0;i<num_classes_;++i){
    double volume_class = betai(a,b,(vec_division.at(i+1)-min_radius_)/interval);
    double volume_class2 = betai(a,b,(vec_division.at(i)-min_radius_)/interval);
    double volume3 = volume_class - volume_class2;
    vec_volume_class.push_back(volume3);
  }

  for(unsigned i=0;i<num_classes_;++i){
    //! Mean radius of each class
    double mean_radius = vec_division.at(i)/(0.5*(1+1.0/raison));
    
    //! Calculated the volume of each class
    if(Tdim == 2) volume = Pi*mean_radius*mean_radius/4.0;
    else volume = Pi*std::pow(mean_radius,3)/6.0;
    double prob = vec_volume_class.at(i)/volume;
    vec_prob_class.push_back(prob);
    if(min_num_particles_class > vec_prob_class.at(i))
      min_num_particles_class = vec_prob_class.at(i);
  }

  //! Temporary number of particles in each class
  for(unsigned i=0;i<num_classes_;++i){
    double num = static_cast<unsigned>(std::floor(num_particles_class_)/min_num_particles_class*vec_prob_class.at(i));
    vec_num_particles_class.push_back(num);
    temp_total_particles += vec_num_particles_class.at(i);
  }

  if(temp_total_particles < num_particles_){
    for(unsigned i =0; i< num_classes_;++i){
      vec_num_particles_class.at(i) = static_cast<unsigned>((static_cast<double>(num_particles_)/temp_total_particles)*vec_num_particles_class.at(i));
    }
  }
  
  unsigned id = 0;
  for(unsigned i= 0;i<num_classes_;++i){
    double low_radius = min_radius_+(max_radius_-min_radius_)/num_classes_*i;
    double up_radius = low_radius +(max_radius_-min_radius_)/num_classes_;
    for(unsigned j=0;j<vec_num_particles_class.at(i);++j){
      double radius = static_cast<double>(std::rand())/RAND_MAX*(up_radius-low_radius)+low_radius;
      auto grain = std::make_shared<Particle<Tdim>>(id,radius);
      vec_particles_ptr_.push_back(grain);
      ++id;
    }
  }
  
  


    
}

//! Returns the incomplete beta function Ix(a,b)
template <unsigned Tdim>
double BetaParticleGenerator<Tdim>::betai(const double& a, const double& b,const double& x){
  
  //double betacf(const double& a, const double& b,const double& x);
  // double gammln(const double& xx);
  double bt;
  
  if (x < 0.0 || x > 1.0) std::cout<<"Bad x in routine betai"<<std::endl;
  if (x == 0.0 || x == 1.0) bt = 0.0;
  else bt = std::exp(gammln(a + b)- gammln(a) - gammln(b) + a * std::log(x) + b * std::log(1.0 - x));
  
  if (x < (a + 1.0) / (a + b + 2.0)){
    return bt * betacf(a, b, x) / a;
  }
  else{
    return 1.0 - bt * betacf(b, a, 1.0 - x) / b;
  }
  
}

//! Evaluates continued fraction for incomplete beta function by modified Lentz's method.
//! \param a=alpha-1, b=beta-1, x=
template <unsigned Tdim>
double BetaParticleGenerator<Tdim>:: betacf(const double& a, const double& b,const double& x){
  int m, m2;
  double aa, c, d, del, h, qab, qam, qap;

  qab = a + b;
  qap = a + 1.0;
  qam = a - 1.0;
  c = 1.0;
  d = 1.0 - qab * x / qap;
  if (std::fabs(d) < std::pow(10,-30))
    d = std::pow(10,-30);
  d = 1.0 / d;
  h = d;
  for (m = 1; m <= 100; m++) {
    m2 = 2 * m;
    aa = m * (b - m) * x / ((qam + m2) * (a + m2));
    d = 1.0 + aa * d;
    if (std::fabs(d) < std::pow(10,-30))
      d = std::pow(10,-30);
    c = 1.0 + aa / c;
    if (std::fabs(c) < std::pow(10,-30))
      c = std::pow(10,-30);
    d = 1.0 / d;
    h *= d * c;
    aa = -(a + m) * (qab + m) * x / ((a + m2) * (qap + m2));
    d = 1.0 + aa * d;
    if (std::fabs(d) < std::pow(10,-30))
      d = std::pow(10,-30);
    c = 1.0 + aa / c;
    if (std::fabs(c) < std::pow(10,-30))
      c = std::pow(10,-30);
    d = 1.0 / d;
    del = d * c;
    h *= del;
    if (std::fabs(del - 1.0) < 3.0*std::pow(10,-7))
      break; // Are we done?
  }
  return h;
}

template <unsigned Tdim>
double BetaParticleGenerator<Tdim>::gammln(const double& xx){
  double x, tmp, ser;
  static const double cof[6] = {76.18009172947146,     -86.50532032941677,
                          24.01409824083091,     -1.231739572450155,
                          0.1208650973866179e-2, -0.5395239384953e-5};

  x = xx - 1.0;
  tmp = x + 5.5;
  tmp -= (x + 0.5) * std::log(tmp);
  ser = 1.0;
  for (unsigned j = 0; j <= 5; ++j) {
    x += 1.0;
    ser += cof[j] / x;
  }
  
  return -tmp + std::log(2.50662827465 * ser);
}


