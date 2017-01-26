/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-08 11:07:44
* Last Modified by:   amedhi
* Last Modified time: 2017-01-19 11:13:31
* Copyright (C) Amal Medhi, amedhi@iisertvm.ac.in
*----------------------------------------------------------------------------*/

#ifndef LATTICE_H
#define LATTICE_H

#include <iostream>
#include <string>
#include <tuple>
#include <set>
#include <stdexcept>
#include "../scheduler/task.h"
#include <boost/graph/adjacency_list.hpp>
#include "matrix.h"
#include "constants.h"

namespace lattice {

/*---------------lattice types-----------------*/
enum class lattice_id {
  UNDEFINED, SQUARE, SIMPLECUBIC
};

/*---------------Unitcell class-----------------*/
class Unitcell 
{
public:
  // ctors
  Unitcell() {}
  Unitcell(const Vector3d& av1, const Vector3d& av2, const Vector3d& av3)
    { set_basis(av1,av2,av3); }
  ~Unitcell() {}
  void set_basis(const Vector3d& av1, const Vector3d& av2, const Vector3d& av3)
  {
    a1 = av1; a2 = av2; a3 = av3;
  }
  // getter functions
  const Vector3d& vector_a1(void) const { return a1; }
  const Vector3d& vector_a2(void) const { return a2; }
  const Vector3d& vector_a3(void) const { return a3; }
private:
  Vector3d a1 {Vector3d(1.0, 0.0, 0.0)};
  Vector3d a2 {Vector3d(0.0, 1.0, 0.0)};
  Vector3d a3 {Vector3d(0.0, 0.0, 1.0)};
};

/*---------------spatial dimension type-----------------*/
enum class boundary_type {open, periodic, antiperiodic};

class Lattice : public Unitcell
{
public:
  // ctors
  Lattice() {}
  Lattice(const input::Parameters& parms) { construct(parms); }
  ~Lattice() {}
  // setter functions
  int construct(const input::Parameters& parms);
  void set_basis_vectors(const Vector3d& av1, const Vector3d& av2, const Vector3d& av3);
  // getter functions
  const unsigned& num_unitcells(void) const { return num_total_cells; }
  Vector3d basis_vector_a1(void) const { return Unitcell::vector_a1(); }
  Vector3d basis_vector_a2(void) const { return Unitcell::vector_a2(); }
  Vector3d basis_vector_a3(void) const { return Unitcell::vector_a3(); }
  int size1(void) const { return static_cast<int>(extent[dim1].size); }
  int size2(void) const { return static_cast<int>(extent[dim2].size); }
  int size3(void) const { return static_cast<int>(extent[dim3].size); }
  boundary_type bc1(void) const { return extent[dim1].bc; }
  boundary_type bc2(void) const { return extent[dim2].bc; }
  boundary_type bc3(void) const { return extent[dim3].bc; }

  // other methods 
  std::pair<Vector3i, int> boundary_wrap(const Vector3i& cell_idx) const;
  Vector3i get_next_bravindex(const Vector3i& current_index) const;
private:
  struct Extent {unsigned size; boundary_type bc; boundary_type periodicity;};
  enum Dimension {dim1, dim2, dim3};
  std::string lname {""};

  // lattice dimensions
  Extent extent[3] = {Extent{1, boundary_type::open, boundary_type::open}, 
                      Extent{1, boundary_type::open, boundary_type::open},
                      Extent{1, boundary_type::open, boundary_type::open}
                     };
  
  // number of unit cells in total and in one layer (for symmetrized lattice)
  unsigned num_total_cells {1};
  unsigned num_layer_cells {1};
  unsigned num_total_sites {0};

  // helper functions
  int define_lattice(void); 
  int finalize_lattice(void); 
  //int construct_graph(void); 
  boundary_type boundary_condition(std::string& bc) const;
};


} // end namespace lattice

#endif







