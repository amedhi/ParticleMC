/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-19 11:22:20
* Last Modified by:   Amal Medhi, amedhi@macbook
* Last Modified time: 2017-01-28 23:22:41
* Copyright (C) Amal Medhi, amedhi@iisertvm.ac.in
*----------------------------------------------------------------------------*/
#include "valley.h"

namespace kspace {


rng::RandomNumber Valley::rng_;

//Valley::Valley(void) 
//  : name_{""} //, mass_{MassTensor(phy::m_e(),phy::m_e(),phy::m_e())}
//{
//}
Valley::Valley(const vid& id, const std::string& name, 
  const Vector3d& k0, const phy::SystemParam& sys) 
: id_{id}, name_{name}, k0_{k0}
{
  double ml, mt;
  switch (id_) {
    case vid::GAMMA: 
      e0_ = sys.GV_e0();
      m0_ = sys.GV_m0();
      mass_ = MassTensor(m0_,m0_,m0_);
      HV_transform_ = MassTensor(1.0,1.0,1.0);
      HV_transform_inv_ = MassTensor(1.0,1.0,1.0);
      parabolic_ = sys.GV_parabolic();
      alpha_ = sys.GV_alpha();
      break;
    case vid::L: 
      e0_ = sys.LV_e0();
      ml = sys.LV_ml();
      mt = sys.LV_mt();
      mass_ = MassTensor(mt,mt,ml);
      m0_ = sys.me();
      HV_transform_ = MassTensor(sqrt(m0_/mt),sqrt(m0_/mt),sqrt(m0_/ml));
      HV_transform_inv_ = MassTensor(sqrt(mt/m0_),sqrt(mt/m0_),sqrt(ml/m0_));
      parabolic_ = sys.LV_parabolic();
      alpha_ = sys.LV_alpha();
      break;
    case vid::X:
      e0_ = sys.XV_e0();
      ml = sys.XV_ml();
      mt = sys.XV_mt();
      mass_ = MassTensor(mt,mt,ml);
      m0_ = sys.me();
      HV_transform_ = MassTensor(sqrt(m0_/mt),sqrt(m0_/mt),sqrt(m0_/ml));
      HV_transform_inv_ = MassTensor(sqrt(mt/m0_),sqrt(mt/m0_),sqrt(ml/m0_));
      parabolic_ = sys.XV_parabolic();
      alpha_ = sys.XV_alpha();
      break;
    default:
      std::cout << "Valley::Valley: unknown valley\n";
  }
  scatterers_.clear();
}

int Valley::add_scatterer(const Scatterer& s) 
{
  scatterers_.push_back(s);
  return scatterers_.size();
}

int Valley::add_scatterer(const phy::SystemParam& sys, const sc_id& scatterer)
{
  switch (scatterer) {
    case sc_id::AccousticPhonon: 
      scatterers_.push_back(AccousticPhonon(sys, id_, mass_));
      break;
    case sc_id::OpticalPhonon: 
      break;
    default:
      std::cout << "Valley::add_scatterer: unknown scatterer\n";
  }
  return 0;
}

double Valley::get_next_flytime(void) const
{
  return rng_.random_real();
}

//------------------ GAMMA Valley ----------------------
/*ValleyGamma::ValleyGamma(const phy::SystemParam& sys, const Vector3d& k0) 
  : Valley(vid::GV, "Gamma (000)", k0, sys)
{
  //add_scatterer(AccousticPhonon(vid::GV, sys));
}
*/



} // end namespace kspace










