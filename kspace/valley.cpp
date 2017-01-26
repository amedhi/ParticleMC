/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-19 11:22:20
* Last Modified by:   amedhi
* Last Modified time: 2017-01-26 11:06:40
* Copyright (C) Amal Medhi, amedhi@iisertvm.ac.in
*----------------------------------------------------------------------------*/
#include "valley.h"

namespace kspace {


rng::RandomNumber Valley::rng_;

//Valley::Valley(void) 
//  : name_{""} //, mass_{MassTensor(phy::m_e(),phy::m_e(),phy::m_e())}
//{
//}
Valley::Valley(const valley_id& vid, const phy::SystemParam& sys)
{
  vid_ = vid; 
  double m0, ml, mt;
  switch (vid_) {
    case valley_id::GV: 
      name_ = "GAMMA_Valley";
      k0_ = Vector3d(0,0,0);
      e0_ = sys.GV_e0();
      m0 = sys.GV_m0();
      mass_ = MassTensor(m0,m0,m0);
    case valley_id::LV: 
      name_ = "L_Valley";
      k0_ = Vector3d(0,0,0);
      e0_ = sys.LV_e0();
      ml = sys.LV_ml();
      mt = sys.LV_mt();
      mass_ = MassTensor(mt,mt,ml);
    case valley_id::XV:
      name_ = "X_Valley";
      k0_ = Vector3d(0,0,0);
      e0_ = sys.XV_e0();
      ml = sys.XV_ml();
      mt = sys.XV_mt();
      mass_ = MassTensor(mt,mt,ml);
    default:
      std::cout << "Valley::Valley: unknown valley\n";
  }
}

int Valley::add_scatterer(const Scatterer& s) 
{
  scatterers_.push_back(s);
  return scatterers_.size();
}

double Valley::get_next_flytime(void) const
{
  return rng_.random_real();
}

//------------------ GAMMA Valley ----------------------
ValleyGamma::ValleyGamma(const phy::SystemParam& sys) 
  : Valley(valley_id::GV, sys)
{
  //add_scatterer(AccousticPhonon(valley_id::GV, sys));
}



} // end namespace kspace










