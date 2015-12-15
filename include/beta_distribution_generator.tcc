//! to generate particles with beta distribution
#include <cmath>
#include <random>

template <unsigned Tdim>
void BetaParticleGenerator<Tdim>::generator() {

  const double Pi = 3.141592653589793;
  double volume = std::numeric_limits<double>::min();

  
  //! Minumun number of particles in all classes
  double min_num_particles_class = std::numeric_limits<double>::max();

  //! Temporary total number of particles calculated by minimum number of particles in all classes
  double temp_total_particles = std::numeric_limits<double>::min();
  
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

  double a = alpha_-1;
  double b = beta_-1;
  double interval = max_radius_ - min_radius_;
  //! The first step is to discretize the interval
  double raison = std::exp((std::log(max_radius_)-std::log(min_radius_))/static_cast<double>(num_classes_));
  //! Initialized the vec_division to the value of raison
  for(unsigned i =0;i<num_classes_+1;++i){
    vec_division.push_back(raison);
  }
  
  //! Calculates lower limit in each interval
  vec_division.at(0)=min_radius_;
  for(unsigned i=1;i<num_classes_;++i){
    vec_division.at(i) = vec_division.at(i-1)*raison;
  }
  vec_division.at(num_classes_)=max_radius_;
  
  //! Calculates volume of each class
  for (unsigned i=0;i<num_classes_;++i){
   double volume_class = betai(a,b,(vec_division.at(i+1)-min_radius_)/interval) - betai(a,b,(vec_division.at(i)-min_radius_)/interval);
    vec_volume_class.push_back(volume_class);
  }

  for(unsigned i=0;i<num_classes_;++i){
    //! Mean radius of each class
    double mean_radius = vec_division.at(i)/(0.5*(1+1.0/raison));
  //! Calculates the volume of each particle
    if(Tdim == 2) volume = Pi*mean_radius*mean_radius;
    else volume = 4.0*std::pow(mean_radius,3)/3.0;
    double prob = vec_volume_class.at(i)/volume;
     vec_prob_class.push_back(prob);
    if(min_num_particles_class >  vec_prob_class.at(i))
      min_num_particles_class =  vec_prob_class.at(i);  
    }

  //! Temporary number of particles in each class
  for (unsigned i=0;i<num_classes_;++i){
    vec_num_particles_class.at(i) = static_cast<unsigned>(std::floor((num_particles_class_)/min_num_particles_class* vec_prob_class.at(i)));
    temp_total_particles += vec_num_particles_class.at(i);
  }

  if(temp_total_particles < num_particles_){
    for(unsigned i=0; i<num_classes_;++i){
      vec_num_particles_class.at(i) = static_cast<unsigned>((static_cast<double>(num_particles_)/temp_total_particles)*vec_num_particles_class.at(i));
    }
  }
  unsigned id = 0;
  for(unsigned i = 0; i<num_classes_;++i){
    double low_radius = min_radius_+(max_radius_-min_radius_)/num_classes_*i;
    double up_radius = low_radius +(max_radius_-min_radius_)/num_classes_;
    for(unsigned j=0;j<vec_num_particles_class.at(i);++j){
      double radius = static_cast<double>(std::rand())/RAND_MAX*(up_radius-low_radius+low_radius);
      auto grain = std::make_shared<Particle<Tdim>>(id,radius);
      vec_particles_ptr_.push_back(grain);
      ++id;
    }
  }
 
}

//! Returns the incomplete beta function Ix(a,b)
template <unsigned Tdim>
double BetaParticleGenerator<Tdim>::betai(const double& a, const double& b,const double& x){
  double betacf(const double& a, const double& b,const double& x);
  double gamma(const double& xx);
  double bt;
  if (x < 0.0 || x > 1.0) std::cout<<"Bad x in routine betai"<<std::endl;
  if (x == 0.0 || x == 1.0) bt = 0.0;
  else bt = exp(gammln(a + b) - gammln(a) - gammln(b) + a * log(x) +
             b * log(1.0 - x));

  return bt;
  if (x < (a + 1.0) / (a + b + 2.0)){
    bt = bt * betacf(a, b, x) / a;
    return bt;
  } 
  else{
    bt = 1.0 - bt * betacf(b, a, 1.0 - x) / b;
    return bt;
  } 
}

//! Evaluates continued fraction for incomplete beta function by modified Lentz's method.
//! \param a=alpha-1, b=beta-1, x=
template <unsigned Tdim>
double BetaParticleGenerator<Tdim>:: betacf(const double& a, const double& b,const double& x){
  //! These q's are factors use in the equations...
  double qab = a + b;
  double qap = a + 1.0;
  double qam = a - 1.0;
  //! First step of Lentz's method
  double c = 1.0;
  double d = 1.0 - qab*x/qap;
  if (fabs(d) < 1.0e-30) d = 1.0e-30;
  d = 1.0 / d;
  double h = d;
  for (unsigned m=1;m<1000;m++){
    unsigned m2 = m * 2;
    double aa = m * (b - m) * x/((qam+m2)*(a+m2));
    //! One step (the even one) of the recurrence
    d = 1.0 + aa * d;
    if (fabs(d) < 1.0e-30) d = 1.0e-30;
    d = 1.0 / d;
    h *= d * c;
    aa = -(a+m) * (qab + m) * x/((a+m2)*(qap+m2));
    //! Next step of the recurrence (the odd one)
    d = 1.0 + aa * d;
    if (fabs(d) < 1.0e-30) d = 1.0e-30;
    c = 1.0 + aa/c;
    if (fabs(d) < 1.0e-30) d = 1.0e-30;
    d = 1.0 / d;
    double del = d*c;
    h *= del;
    if (fabs(del-1.0)<=1.0e-7) break;    // Are we done?
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
  tmp -= (x + 0.5) * log(tmp);
  ser = 1.0;
  for (unsigned j = 0; j <= 5; ++j) {
    x += 1.0;
    ser += cof[j] / x;
  }
  return -tmp + log(2.50662827465 * ser);
}


