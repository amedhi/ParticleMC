/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-18 20:55:56
* Last Modified by:   amedhi
* Last Modified time: 2017-01-26 11:13:20
* Copyright (C) Amal Medhi, amedhi@iisertvm.ac.in
*----------------------------------------------------------------------------*/
#ifndef PHYSICAL_H
#define PHYSICAL_H
#include <cmath>

namespace phy {

constexpr double pi(void) { return 3.1415926535897932384626433832795028841971693993751058209; }
constexpr double two_pi(void) { return 2.0 * pi(); }
constexpr double half_pi(void) { return 0.5 * pi(); }
//constexpr double m_e(void) { return 5.11E+5; } // electronic mass (eV)
//constexpr double e(void) { return 1.0; } // electronic charge
//constexpr double e_inv(void) { return 1.0/e(); } // electronic charge
//constexpr double hbar(void) { return 1.0; } // Planck hbar
//constexpr double hbar_inv(void) { return 1.0/hbar(); } // Planck hbar
//constexpr double kB(void) { return 8.617330E-5; } // Boltzmann constant (eV/T)
//constexpr std::complex<double> ii(void) { return std::complex<double>(0.0, 1.0); }


class NaturalUnits 
{
public:
  NaturalUnits() {} 
  ~NaturalUnits() {}
  const double& eV(void) const { return unit_eV_; }
  const double& c(void) const { return unit_c_; }
  const double& hbar(void) const { return unit_hbar_; }
  const double& gm(void) const { return unit_gm_; }
  const double& cm(void) const { return unit_cm_; }
  const double& sec(void) const { return unit_sec_; }
  const double& esu(void) const { return unit_esu_; }
  const double& charge(void) const { return unit_charge_; }
private:
  //double c_{1.0}; // speed of light (c)
  //double hbar_{1.0}; // Planck hbar (hbar)
  //double me_{5.110e+5}; // electronic mass (eV/c^2)
  //double e_{0.08542454611904483754}; // electronic charge (sqrt(1/137)) ([hbar*c]^{1/2}) 
  //double kB_{8.617330e-5}; // Boltzmann constant (eV/K)
  // conversion factors (from cgs to nutaural)
  double unit_gm_{5.60958616e+32}; // 1 gm = x eV/c^2
  double unit_cm_{5.06772886e+4}; // 1 cm = x hbar c/eV
  double unit_sec_{1.51926689e+15}; // 1 sec = x hbar/eV
  double unit_esu_{1.77848986e+8}; // 1 esu charge = x (hbar c)^{1/2}
  // conversion factors (from nutaural to cgs)
  double unit_c_{2.99792458e+10}; // 1 c = x cm/sec 
  double unit_hbar_{1.05457266e-27}; // 1 hbar = x gm cm^2/sec
  double unit_eV_{1.60217733e-12}; // 1 hbar = x gm cm^2/sec^2
  double unit_charge_{5.62274781e-9}; // 1 charge unit = x esu ([gm cm^3 / sec^2]^{1/2})
};

class PhysicalQuantity 
{
public:
  PhysicalQuantity() {} 
  ~PhysicalQuantity() {}
  const double& in_natural(void) const { return natural_; }
  const double& in_cgs(void) const { return cgs_; }
protected:
  double cgs_{0.0};
  double natural_{0.0};
  static NaturalUnits unit;
};

class Mass : public PhysicalQuantity
{
public:
  Mass() {}
  Mass(const double& x) { set_cgs(x); }
  void set_cgs(const double& x) 
    { cgs_=x; natural_=cgs_*unit.gm(); }
  void set_natural(const double& x) 
    { natural_=x; cgs_=(natural_*unit.eV())/(unit.c()*unit.c()); }
};

class Length : public PhysicalQuantity
{
public:
  Length() {}
  Length(const double& x) { set_cgs(x); }
  void set_cgs(const double& x) 
    { cgs_=x; natural_=cgs_*unit.cm(); }
  void set_natural(const double& x) 
    { natural_=x; cgs_=(natural_*unit.hbar()*unit.c())/unit.eV(); }
};

class Time : public PhysicalQuantity
{
public:
  Time() {}
  Time(const double& x) { set_cgs(x); }
  void set_cgs(const double& x) 
    { cgs_=x; natural_=cgs_*unit.sec(); }
  void set_natural(const double& x) 
    { natural_=x; cgs_=natural_*unit.hbar()/unit.eV(); }
};

class Charge : public PhysicalQuantity
{
public:
  Charge() {}
  Charge(const double& x) { set_cgs(x); }
  void set_cgs(const double& x) 
    { cgs_=x; natural_=cgs_*unit.esu(); }
  void set_natural(const double& x) 
    { natural_=x; cgs_=natural_*unit.charge(); }
};

class Speed : public PhysicalQuantity
{
public:
  Speed() {}
  Speed(const double& x) { set_cgs(x); }
  void set_cgs(const double& x) 
    { cgs_=x; natural_=cgs_*unit.cm()/unit.sec(); }
  void set_natural(const double& x) 
    { natural_=x; cgs_=(natural_*unit.c()); }
};

class Momentum : public PhysicalQuantity
{
public:
  Momentum() {}
  Momentum(const double& x) { set_cgs(x); }
  void set_cgs(const double& x) 
    { cgs_=x; natural_=(cgs_*unit.gm()*unit.cm())/unit.sec(); }
  void set_natural(const double& x) 
    { natural_=x; cgs_=(natural_*unit.eV())/unit.c(); }
};

class Force : public PhysicalQuantity
{
public:
  Force() {}
  Force(const double& x) { set_cgs(x); }
  void set_cgs(const double& x) 
    { cgs_=x; natural_=(cgs_*unit.gm()*unit.cm())/(unit.sec()*unit.sec()); }
  void set_natural(const double& x) 
    { natural_=x; cgs_=(natural_*unit.eV()*unit.eV())/(unit.hbar()*unit.c()); }
};

class Energy : public PhysicalQuantity
{
public:
  Energy() {}
  Energy(const double& x) { set_cgs(x); }
  void set_cgs(const double& x) 
    { cgs_=x; natural_=(cgs_*unit.gm()*unit.cm()*unit.cm())/(unit.sec()*unit.sec()); }
  void set_natural(const double& x) 
    { natural_=x; cgs_=natural_*unit.eV(); }
};

class ElectricField : public PhysicalQuantity
{
public:
  ElectricField() {}
  ElectricField(const double& x) { set_voltpcm(x); }
  void set_voltpcm(const double& x) 
    { cgs_=x; natural_=(cgs_*std::sqrt(137.035999139))/unit.cm(); }
  void set_natural(const double& x) 
    { 
      natural_=x; 
      double hc = unit.hbar()*unit.c();
      cgs_=natural_*unit.eV()*unit.eV()/std::sqrt(hc*hc*hc); 
    }
};

class MassDensity : public PhysicalQuantity
{
public:
  MassDensity() {}
  MassDensity(const double& x) { set_cgs(x); }
  void set_cgs(const double& x) 
    { cgs_=x; natural_=(cgs_*unit.gm())/(unit.cm()*unit.cm()*unit.cm()); }
  void set_natural(const double& x) 
    { 
      natural_=x; 
      // cgs = (eV/hbar*c)^4*(hbar/c)
      double eV_by_hc = unit.eV()/(unit.hbar()*unit.c());
      double c2 = unit.c()*unit.c();
      cgs_=(natural_/c2)*unit.eV()*eV_by_hc*eV_by_hc*eV_by_hc; 
    }
};

class Temperature : public PhysicalQuantity //in Kelvin
{
public:
  Temperature() {}
  Temperature(const double& x) { set_kelvin(x); } 
  void set_kelvin(const double& x) 
    { cgs_=x; natural_=x; }
};

// constant quantities
class LightSpeed : public PhysicalQuantity
{
public:
  LightSpeed() { cgs_=unit.c(); natural_=1.0; }
};

class PlanckHbar : public PhysicalQuantity
{
public:
  PlanckHbar() { cgs_=unit.hbar(); natural_=1.0; }
};

class ElectronCharge : public PhysicalQuantity
{
public:
  ElectronCharge() { cgs_=4.80320427e-10; natural_=1.0/std::sqrt(137.035999139); }
};

class ElectronMass : public PhysicalQuantity
{
public:
  ElectronMass() { cgs_=9.10938356e-28; natural_=5.110e+5; }
};

class BoltzmannConst : public PhysicalQuantity
{
public:
  BoltzmannConst() { cgs_=1.38064852e-16; natural_=8.617330e-5; }
};

} // end namespace phy

#endif
