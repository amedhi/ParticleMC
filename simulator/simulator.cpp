/*---------------------------------------------------------------------------
* Copyright (C) 2015-2016 by Amal Medhi <amedhi@iisertvm.ac.in>.
* All rights reserved.
* Author: Amal Medhi
* Date:   2016-03-09 15:27:50
* Last Modified by:   Amal Medhi, amedhi@macbook
* Last Modified time: 2017-01-27 21:54:13
*----------------------------------------------------------------------------*/
#include <iomanip>
#include "simulator.h"

namespace mc {

Simulator::Simulator(input::Parameters& parms) 
  : system(parms), CBand(kspace::band_id::CB, system)
{
  //Model::construct(LatticeGraph::lattice(), parms);
  num_electrons = 1;
  electrons.resize(num_electrons);
  electrons[0].set_environment(CBand.gamma_v());
}

int Simulator::start(input::Parameters& parms) 
{

  phy::Mass mass = 9.1e-28;
  std::cout << mass.in_cgs() << "\n";
  std::cout << mass.in_natural() << "\n";


  // this function must be override
  std::cout << "Simulator::start\n";
  lattice::Lattice lattice(parms);
  //std::cout << "lattice: num sites = " << lattice.num_sites() << "\n";
  // init particle states
  //init_particle_states();

  // simulation
  double dt = 0.1;
  for (unsigned n=0; n<10; ++n) {
    electrons[0].time_evolve(dt);
  }
  std::cout << "simulation time = " << electrons[0].age() << "\n";

  return 0;
}

void Simulator::init_particle_states(void)
{
  for (unsigned i=0; i<electrons.size(); ++i) {
    //electrons[i].set_rvector();
    //electrons[i].set_kvector();
    //electrons[i].set_cell_idx();
    //electrons[i].set_band_idx();
    //electrons[i].set_valley_idx();
  }
}


void Simulator::print_copyright(std::ostream& os)
{
  os << "#" << std::string(72,'-') << "\n";
  os << "#" << " Program: MC Simulation\n";
  os << "#" << "          (c) Amal Medhi <amedhi@iisertvm.ac.in>\n";
  os << "#" << std::string(72,'-') << "\n";
}


} // end namespace mc
