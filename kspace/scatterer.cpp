/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-21 21:08:23
* Last Modified by:   amedhi
* Last Modified time: 2017-01-26 11:22:03
* Copyright (C) Amal Medhi, amedhi@iisertvm.ac.in
*----------------------------------------------------------------------------*/
#include "scatterer.h"

namespace kspace {


//rng::RandomNumber Scatterer::rng_;

Scatterer::Scatterer(const std::string& name)
  : name_{name}
{
}

AccousticPhonon::AccousticPhonon()
  : Scatterer("Accoustic Phonon")
{
  deformation_potential_ = 1.0;
  longitudinal_sound_velocity_ = 1.0;
  crystal_mass_density_ = 1.0;
}


AccousticPhonon::AccousticPhonon(const valley_id& vid, const phy::SystemParam& sys)
  : Scatterer("AccousticPhonon_GV")
{
  deformation_potential_ = 1.0;
  longitudinal_sound_velocity_ = 1.0;
  crystal_mass_density_ = 1.0;
  // short names
  double T = sys.T();
  double E1 = deformation_potential_;
  double ul = longitudinal_sound_velocity_;
  double rho = crystal_mass_density_;
  // constant
  double a = std::sqrt(2.0) * sys.kB() * T * E1 * E1;
  double h = sys.hbar();
  double b = phy::pi()*h*h*h*h*ul*ul*rho; 
  scattering_constant_ = a/b;
}





} // end namespace kspace










