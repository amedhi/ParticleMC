/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-21 21:08:23
* Last Modified by:   Amal Medhi, amedhi@macbook
* Last Modified time: 2017-01-28 23:25:17
* Copyright (C) Amal Medhi, amedhi@iisertvm.ac.in
*----------------------------------------------------------------------------*/
#include "scatterer.h"

namespace kspace {


//rng::RandomNumber Scatterer::rng_;

Scatterer::Scatterer(const vid& id, const std::string& name)
  : id_{id}, name_{name}
{
}

AccousticPhonon::AccousticPhonon(const vid& id, const phy::SystemParam& sys)
  : Scatterer(id, "AccousticPhonon")
{
  double h = sys.hbar();
  double kB = sys.kB();
  double T = sys.T();
  double rho = sys.mass_density();
  double vs = sys.sound_speed();

  double E1, m, a, b;
  switch (id) {
    case vid::GAMMA: 
      E1 = sys.GV_acc_deform_pot();
      m = sys.GV_m0();
      a = std::sqrt(2.0*m*m*m)*kB*T*E1*E1;
      b = phy::pi()*h*h*h*h*vs*vs*rho; 
      scattering_constant_ = a/b;
    case vid::L: 
    case vid::X:
    default:
      std::cout << "Valley::Valley: unknown valley\n";
  }
}

AccousticPhonon::AccousticPhonon(const phy::SystemParam& sys, const vid& id, 
  const MassTensor& mass) : Scatterer(id, "AccousticPhonon")
{
  double h = sys.hbar();
  double kB = sys.kB();
  double T = sys.T();
  double rho = sys.mass_density();
  //std::cout << "rho = " << rho << "\n";
  double vs = sys.sound_speed();
  double m3 = mass.diagonal().prod();
  double E1 = 0.0;
  switch (id) {
    case vid::GAMMA: 
      E1 = sys.GV_acc_deform_pot();
      break;
    case vid::L: 
      E1 = sys.LV_acc_deform_pot();
      break;
    case vid::X:
      E1 = sys.XV_acc_deform_pot();
      break;
    default:
      std::cout << "AccousticPhonon::AccousticPhonon: unknown valley\n";
  }
  // scattering constant
  double a, b;
  a = std::sqrt(2.0*m3)*kB*T*E1*E1;
  b = phy::pi()*h*h*h*h*vs*vs*rho; 
  scattering_constant_ = a/b;
}




} // end namespace kspace










