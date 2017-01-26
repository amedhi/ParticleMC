/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-26 08:52:44
* Last Modified by:   amedhi
* Last Modified time: 2017-01-26 11:23:11
* Copyright (C) Amal Medhi, amedhi@iisertvm.ac.in
*----------------------------------------------------------------------------*/
#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include "../scheduler/task.h"
#include "physical.h"

namespace phy {

class SystemParam
{
public:
  SystemParam();
  SystemParam(input::Parameters& parms);
  ~SystemParam() {}
  void init(input::Parameters& input);
  const double& c(void) const { return c_.in_natural(); }
  const double& hbar(void) const { return hbar_.in_natural(); }
  const double& e(void) const { return e_.in_natural(); }
  const double& me(void) const { return me_.in_natural(); }
  const double& kB(void) const { return kB_.in_natural(); }
  const double& T(void) const { return T_.in_natural(); }
  const double& Efield(void) const { return Efield_.in_natural(); }
  const double& sound_ul(void) const { return sound_ul_.in_natural(); }
  const double& sound_ut(void) const { return sound_ut_.in_natural(); }
  const double& GV_e0(void) const { return GV_e0_.in_natural(); }
  const double& GV_m0(void) const { return GV_m0_.in_natural(); }
  const double& LV_e0(void) const { return LV_e0_.in_natural(); }
  const double& LV_ml(void) const { return LV_ml_.in_natural(); }
  const double& LV_mt(void) const { return LV_mt_.in_natural(); }
  const double& XV_e0(void) const { return XV_e0_.in_natural(); }
  const double& XV_ml(void) const { return XV_ml_.in_natural(); }
  const double& XV_mt(void) const { return XV_mt_.in_natural(); }
private:
  // constants
  phy::LightSpeed c_;
  phy::PlanckHbar hbar_;
  phy::ElectronCharge e_;
  phy::ElectronMass me_;
  phy::BoltzmannConst kB_; 
  // parameters
  phy::Temperature T_;
  phy::ElectricField Efield_;
  phy::Speed sound_ul_;
  phy::Speed sound_ut_;
  // GAMMA Valley parameters
  phy::Energy GV_e0_;
  phy::Mass GV_m0_;
  // L Valley parameters
  phy::Energy LV_e0_;
  phy::Mass LV_ml_;
  phy::Mass LV_mt_;
  // X Valley parameters
  phy::Energy XV_e0_;
  phy::Mass XV_ml_;
  phy::Mass XV_mt_;
};



} // end namespace phy

#endif
