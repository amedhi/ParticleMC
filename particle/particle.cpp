/*---------------------------------------------------------------------------
* Copyright (C) 2015-2016 by Amal Medhi <amedhi@iisertvm.ac.in>.
* All rights reserved.
* Author: Amal Medhi
* Date:   2016-01-25 18:05:03
* Last Modified by:   amedhi
* Last Modified time: 2017-01-26 10:02:07
*----------------------------------------------------------------------------*/
#include "particle.h"

namespace particle {

Particle::Particle(void) 
  : cell_idx_{0}, band_idx_{0}, r_{Vector3d(0,0,0)}, k_{Vector3d(0,0,0)}
  , age_{0.0}, displacement_{Vector3d(0,0,0)}, flytime_{0.0}, mass_{0.0}
  , mass_inv_{0.0}, Efield_{Vector3d(0,0,0)}
{
  //valley = nullptr;
}

void Particle::set_environment(const kspace::Valley& v)
{
  valley = &v;
  flytime_ = valley->get_next_flytime();
}

void Particle::time_evolve(const double& t)
{
  if (t < flytime_) {
    // fly for time 't'
    move_ballistic(t);
    flytime_ -= t;
    age_ += t;
  } 
  else {
    // fly for time 'flytime'
    move_ballistic(flytime_);
    //get_scattered();
    flytime_ = valley->get_next_flytime();
    age_ += flytime_;
  }
} 

void Particle::move_ballistic(const double& dt)
{
  //k_ += (phy::e()*phy::hbar_inv()*dt)*Efield_;
}








} // end namespace particle

