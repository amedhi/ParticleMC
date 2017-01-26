/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-16 21:33:33
* Last Modified by:   amedhi
* Last Modified time: 2017-01-26 10:34:45
* Copyright (C) Amal Medhi, amedhi@iisertvm.ac.in
*----------------------------------------------------------------------------*/
#ifndef ENERGYBAND_H
#define ENERGYBAND_H

#include <iostream>
#include "../simulator/system.h"
#include "valley.h"

namespace kspace {

class EnergyBand 
{
public:
  // ctors
  EnergyBand(); 
  ~EnergyBand() {}
  int add_valley(const Valley& v);
  const Valley& gamma_v(void) const; 
private:
  std::vector<Valley> valleys_;
};

class ConductionBand : public EnergyBand
{
public:
  ConductionBand(); 
  ConductionBand(const phy::SystemParam& sys); 
  int construct(const phy::SystemParam& sys); 
private:
};


} // end namespace particle

#endif
