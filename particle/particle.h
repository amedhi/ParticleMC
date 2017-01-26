/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-08 12:19:48
* Last Modified by:   amedhi
* Last Modified time: 2017-01-26 09:29:44
* Copyright (C) Amal Medhi, amedhi@iisertvm.ac.in
*----------------------------------------------------------------------------*/
#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <string>
#include <memory>
#include "../lattice/lattice.h"
#include "../kspace/valley.h"
#include "../simulator/system.h"

namespace particle {

class Particle 
{
public:
  // ctors
  Particle(); 
  ~Particle() {}
  void time_evolve(const double& time);
  void move_ballistic(const double& dt);
  void set_environment(const kspace::Valley& v);
  double age(void) const { return age_; }
private:
  unsigned cell_idx_;
  unsigned band_idx_;
  Vector3d r_;
  Vector3d k_;
  // total time evolved 
  double age_{0.0};
  // total displacement undergone 
  Vector3d displacement_{Vector3d(0,0,0)};
  // time left for next free flight
  double flytime_{0.0};

  // external fields on it
  double mass_{0.0};
  double mass_inv_{0.0};
  Vector3d Efield_{Vector3d(0,0,0)};

  // energy band valley on which it lives
  //std::shared_ptr<kspace::Valley> valley{nullptr};
  const kspace::Valley* valley;

  void scan_environment(void);
};

} // end namespace particle

#endif
