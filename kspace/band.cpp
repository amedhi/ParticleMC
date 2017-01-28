/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-19 11:19:32
* Last Modified by:   Amal Medhi, amedhi@macbook
* Last Modified time: 2017-01-29 00:10:41
* Copyright (C) Amal Medhi, amedhi@iisertvm.ac.in
*----------------------------------------------------------------------------*/
#include "band.h"

namespace kspace {

EnergyBand::EnergyBand(void) 
{
  clear();
}

EnergyBand::EnergyBand(const band_id& id, const phy::SystemParam& sys)
{
  construct(id, sys);
}

int EnergyBand::construct(const band_id& id, const phy::SystemParam& sys)
{
  using v = kspace::vid;
  using sc = kspace::sc_id;
  clear();
  double kp, km;
  id_ = id;
  switch (id_) {
    case band_id::CB: 
      // Gamma Valley
      add_valley(v::GAMMA, "Gamma (000)", Vector3d(0,0,0), sys);
      // L-Valleys
      kp = phy::pi()/sys.lattice_constant();
      km = -kp;
      add_valley(v::L, "L1 (111)", Vector3d(kp,kp,kp), sys);
      add_valley(v::L, "L2 (m11)", Vector3d(km,kp,kp), sys);
      add_valley(v::L, "L3 (1m1)", Vector3d(kp,km,kp), sys);
      add_valley(v::L, "L4 (11m)", Vector3d(kp,kp,km), sys);
      // X-Valleys
      kp = 0.8*phy::pi()/sys.lattice_constant();
      km = -kp;
      add_valley(v::X, "X1 (100)", Vector3d(kp,0,0), sys);
      add_valley(v::X, "X2 (m00)", Vector3d(km,0,0), sys);
      add_valley(v::X, "X3 (010)", Vector3d(0,kp,0), sys);
      add_valley(v::X, "X4 (0m0)", Vector3d(0,km,0), sys);
      add_valley(v::X, "X5 (001)", Vector3d(0,0,kp), sys);
      add_valley(v::X, "X6 (00m)", Vector3d(0,0,km), sys);

      // Intravalley Accoustic Phonon
      for (auto& valley : *this) {
        valley.add_scatterer(sys, sc::AccousticPhonon);
      }
      // Intravalley Optical Phonon
      for (auto& valley : *this) {
        if (valley.id() == v::L)
          valley.add_scatterer(sys, sc::OpticalPhonon);
      }

      break;
    case band_id::VB: 
      break;
    default:
      std::cout << "EnergyBand::construct: unknown band\n";
  }
  return 0;
}


int EnergyBand::add_valley(const vid& id, const std::string& name, const Vector3d& k0, 
    const phy::SystemParam& sys)
{
  push_back(Valley(id,name,k0,sys));
  return size()-1;
}





} // end namespace kspace

