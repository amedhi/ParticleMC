/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-21 21:08:14
* Last Modified by:   Amal Medhi, amedhi@macbook
* Last Modified time: 2017-01-28 13:37:34
* Copyright (C) Amal Medhi, amedhi@iisertvm.ac.in
*----------------------------------------------------------------------------*/
#ifndef SCATTERER_H
#define SCATTERER_H

#include <iostream>
#include <string>
#include "../scheduler/task.h"
#include "../lattice/matrix.h"
#include "../simulator/system.h"

namespace kspace {

enum class sc_id {
  AccousticPhonon, OpticalPhonon, end
};

enum class vid {
  GAMMA, L, X, end
};

class Scatterer 
{
public:
  Scatterer(const vid& id, const std::string& name); 
  ~Scatterer() {}
  const std::string& name(void) { return name_; } 
  double cross_section(const double& energy_in) const;
  //Vector3d scatter(const Vector3d& k_in, const double& en_in) const;
private:
  vid id_;
  std::string name_;
};

class AccousticPhonon : public Scatterer 
{
public:
  AccousticPhonon(const vid& vid, const phy::SystemParam& sys); 
  AccousticPhonon(const phy::SystemParam& sys, const vid& id, const MassTensor& mass); 
  ~AccousticPhonon() {}
  //double get_cross_section(const MassTensor& m, const double& energy_in) const;
  //Vector3d scatter(const Vector3d& incident_k) const;
private:
  double scattering_constant_;
};



} // end namespace particle

#endif
