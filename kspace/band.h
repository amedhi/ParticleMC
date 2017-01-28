/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-16 21:33:33
* Last Modified by:   Amal Medhi, amedhi@macbook
* Last Modified time: 2017-01-28 23:59:04
* Copyright (C) Amal Medhi, amedhi@iisertvm.ac.in
*----------------------------------------------------------------------------*/
#ifndef ENERGYBAND_H
#define ENERGYBAND_H

#include <iostream>
#include "../simulator/system.h"
#include "valley.h"

namespace kspace {

enum class band_id {
  CB, VB, end
};

class EnergyBand : private std::vector<Valley> 
{
public:
  // ctors
  EnergyBand(); 
  EnergyBand(const band_id& id, const phy::SystemParam& sys); 
  int construct(const band_id& id, const phy::SystemParam& sys); 
  ~EnergyBand() {}
  //int add_valley(const Valley& v);
  const Valley& gamma_v(void) const { return operator[](0); } 
private:
  band_id id_;
  //std::vector<Valley> valleys_;
  int add_valley(const vid& id, const std::string& name, const Vector3d& k0, 
    const phy::SystemParam& sys);
};

/*class ConductionBand : public EnergyBand
{
public:
  ConductionBand(); 
  ConductionBand(const phy::SystemParam& sys); 
  int construct(const phy::SystemParam& sys); 
private:
};*/


} // end namespace particle

#endif
