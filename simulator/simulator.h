/*---------------------------------------------------------------------------
* Copyright (C) 2015-2016 by Amal Medhi <amedhi@iisertvm.ac.in>.
* All rights reserved.
* Author: Amal Medhi
*----------------------------------------------------------------------------*/
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <array>
#include <Eigen/Core>
#include "../scheduler/worker.h"
#include "./random.h"
#include "../lattice/lattice.h"
#include "../kspace/band.h"
#include "../particle/particle.h"
#include "system.h"
//#include "../observable/observables.h"
//#include "sitebasisstate.h"
//#include "observable_operator.h"

namespace mc {

class Simulator : public scheduler::Worker
{
public:
  Simulator(input::Parameters& parms); 
  ~Simulator() {}
  int start(input::Parameters& parms) override;
  void run(void) override {} 
  void finish(void) override {} 
  void dostep(void) override {} 
  void halt(void) override {} 
  static void print_copyright(std::ostream& os);
private:
  phy::SystemParam system;
  unsigned num_electrons{1};
  std::vector<particle::Particle> electrons;
  std::vector<particle::Particle> holes;
  kspace::ConductionBand CBand;

  void init_particle_states(void);
};



} // end namespace monte carlo

#endif
