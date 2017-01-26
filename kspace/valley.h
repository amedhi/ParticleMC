/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-16 22:00:00
* Last Modified by:   amedhi
* Last Modified time: 2017-01-26 11:13:51
* Copyright (C) Amal Medhi, amedhi@iisertvm.ac.in
*----------------------------------------------------------------------------*/
#ifndef VALLEY_H
#define VALLEY_H

#include <iostream>
#include <string>
#include "../lattice/matrix.h"
#include "../simulator/random.h"
#include "../simulator/system.h"
#include "scatterer.h"

namespace kspace {

class Valley 
{
public:
  // ctors
  Valley(const valley_id& vid, const phy::SystemParam& sys); 
  ~Valley() {}
  //int define(const input::Parameters& parms) { m_e_=1.0; m_h_=1.0; return 0; }
  int add_scatterer(const Scatterer& s);
  double get_next_flytime(void) const;
private:
  valley_id vid_;
  std::string name_;
  Vector3d k0_;
  double e0_;
  MassTensor mass_;
  std::vector<Scatterer> scatterers_;
  static rng::RandomNumber rng_;
};

class ValleyGamma : public Valley
{
public:
  ValleyGamma(const phy::SystemParam& sys); 
  ~ValleyGamma() {} 
private:
};




} // end namespace particle

#endif
