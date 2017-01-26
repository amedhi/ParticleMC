/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-26 08:53:24
* Last Modified by:   amedhi
* Last Modified time: 2017-01-26 11:12:38
* Copyright (C) Amal Medhi, amedhi@iisertvm.ac.in
*----------------------------------------------------------------------------*/
#include "system.h"

namespace phy {

SystemParam::SystemParam(void) 
  : c_(), hbar_(), e_(), me_()
{}

SystemParam::SystemParam(input::Parameters& input) 
  : c_(), hbar_(), e_(), me_()
{
  init(input);
}

void SystemParam::init(input::Parameters& input)
{
  T_.set_kelvin(300.0);
  Efield_.set_voltpcm(1.0e4);
  sound_ul_.set_cgs(1.0e5);
  sound_ut_.set_cgs(1.0e5);

  // Gamma Valley
  GV_e0_.set_natural(0.1);
  GV_m0_.set_natural(1.0*me_.in_natural());
  // L Valley
  LV_e0_.set_natural(0.1);
  LV_ml_.set_natural(1.0*me_.in_natural());
  LV_mt_.set_natural(1.0*me_.in_natural());
  // X Valley
  XV_e0_.set_natural(0.1);
  XV_ml_.set_natural(1.0*me_.in_natural());
  XV_mt_.set_natural(1.0*me_.in_natural());
}


} // end namespace phy









