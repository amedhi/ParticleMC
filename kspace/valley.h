/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-16 22:00:00
* Last Modified by:   Amal Medhi, amedhi@macbook
* Last Modified time: 2017-01-28 23:53:12
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
  Valley(const vid& id, const std::string& name, const Vector3d& k0, const phy::SystemParam& sys); 
  ~Valley() {}
  //int define(const input::Parameters& parms) { m_e_=1.0; m_h_=1.0; return 0; }
  const vid& id(void) const { return id_; }
  int add_scatterer(const Scatterer& s);
  int add_scatterer(const phy::SystemParam& sys, const sc_id& scatterer);
  double get_next_flytime(void) const;
private:
  vid id_;
  std::string name_;
  MassTensor mass_; // mass tensor
  MassTensor HV_transform_; // Herring-Vogt transormation (diagonal matrix)
  MassTensor HV_transform_inv_; // inverse
  double m0_; // transformed isotropic mass
  Vector3d k0_; // valley center pos
  double e0_; // valley center energy
  bool parabolic_; // is parabolic
  double alpha_; // non-parabolicity parameter
  std::vector<Scatterer> scatterers_;
  static rng::RandomNumber rng_;
};

/*class ValleyGamma : public Valley
{
public:
  ValleyGamma(const phy::SystemParam& sys); 
  ~ValleyGamma() {} 
private:
};*/




} // end namespace particle

#endif
