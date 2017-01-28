/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-26 08:53:24
* Last Modified by:   Amal Medhi, amedhi@macbook
* Last Modified time: 2017-01-28 23:07:23
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
  mass_density_.set_cgs(5.32);
  a0_.set_cgs(5.658e-8);
  Efield_.set_voltpcm(1.0e4);
  sound_speed_.set_cgs(1.0e5);

  double me = me_.in_natural();
  // Gamma Valley
  GV_e0_.set_natural(0.14);
  GV_m0_.set_natural(0.037*me);
  GV_acc_deform_pot_.set_natural(5.0);
  GV_parabolic_ = false;
  GV_alpha_.set_natural(0.3);
  // L Valley
  LV_e0_.set_natural(0.00);
  LV_ml_.set_natural(1.588*me);
  LV_mt_.set_natural(0.08152*me);
  LV_acc_deform_pot_.set_natural(11.0);
  LV_parabolic_ = false;
  LV_alpha_.set_natural(0.3);
  // X Valley
  XV_e0_.set_natural(0.18);
  XV_ml_.set_natural(1.353*me_.in_natural());
  XV_mt_.set_natural(0.288*me_.in_natural());
  XV_acc_deform_pot_.set_natural(9.0);
  XV_parabolic_ = false;
  XV_alpha_.set_natural(0.3);
}


} // end namespace phy









