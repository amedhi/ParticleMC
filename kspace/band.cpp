/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-19 11:19:32
* Last Modified by:   amedhi
* Last Modified time: 2017-01-26 10:34:48
* Copyright (C) Amal Medhi, amedhi@iisertvm.ac.in
*----------------------------------------------------------------------------*/
#include "band.h"

namespace kspace {

EnergyBand::EnergyBand(void) 
{
  valleys_.clear();
}

int EnergyBand::add_valley(const Valley& v)
{
  valleys_.push_back(v);
  return valleys_.size();
} 

const Valley& EnergyBand::gamma_v(void) const
{
  return valleys_[0];
}


ConductionBand::ConductionBand() 
  : EnergyBand()
{
}

ConductionBand::ConductionBand(const phy::SystemParam& sys)
  : EnergyBand()
{
  construct(sys);
}

int ConductionBand::construct(const phy::SystemParam& sys)
{
  add_valley(ValleyGamma(sys));
  return 0;
}




} // end namespace kspace

