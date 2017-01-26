/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-21 21:08:14
* Last Modified by:   amedhi
* Last Modified time: 2017-01-26 11:18:13
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

enum class valley_id {
  GV, LV, XV, end
};

class Scatterer 
{
public:
  Scatterer(const std::string& name); 
  ~Scatterer() {}
  const std::string& name(void) { return name_; } 
  double get_cross_section(const MassTensor& m, const double& energy_in) const;
  //Vector3d scatter(const Vector3d& incident_k) const;
private:
  std::string name_;
};

class AccousticPhonon : public Scatterer 
{
public:
  AccousticPhonon(); 
  AccousticPhonon(const valley_id& vid, const phy::SystemParam& sys); 
  ~AccousticPhonon() {}
  //double get_cross_section(const MassTensor& m, const double& energy_in) const;
  //Vector3d scatter(const Vector3d& incident_k) const;
private:
  double scattering_constant_;
  double deformation_potential_;
  double longitudinal_sound_velocity_;
  double crystal_mass_density_;
};



} // end namespace particle

#endif
