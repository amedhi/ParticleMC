/*---------------------------------------------------------------------------
* Author: Amal Medhi
* Date:   2017-01-08 11:07:44
* Last Modified by:   amedhi
* Last Modified time: 2017-01-19 11:13:28
* Copyright (C) Amal Medhi, amedhi@iisertvm.ac.in
*----------------------------------------------------------------------------*/
#include <iomanip>
#include "lattice.h"
#include <boost/algorithm/string.hpp>

namespace lattice {

/*--------------- Implementation of 'Lattice' class-----------------*/
int Lattice::construct(const input::Parameters& parms) 
{
  // size of the lattice box
  for (unsigned dim=dim1; dim<=dim3; ++dim) {
    std::string lsize = "lsize" + std::to_string(dim+1);
    extent[dim].size = parms.set_value(lsize, 1.0);
    if (extent[dim].size<0.0) throw std::range_error("error: latticelibrary: invalid lattice size");
  }

  // boundary conditions
  int info;
  std::string bc; 
  for (unsigned dim=dim1; dim<=dim3; ++dim) {
    std::string lbc = "bc" + std::to_string(dim+1);
    bc = parms.set_value(lbc, "open", info);
    extent[dim].periodicity = boundary_condition(bc);
    extent[dim].bc = extent[dim].periodicity;
    if (extent[dim].bc == boundary_type::antiperiodic) extent[dim].bc = boundary_type::periodic;
  }

  // unitcell
  set_basis_vectors(Vector3d(1.0,0,0), Vector3d(0,1.0,0), Vector3d(0,0,1.0));

  return 0;
}

void Lattice::set_basis_vectors(const Vector3d& av1, const Vector3d& av2, const Vector3d& av3)
{
  Unitcell::set_basis(av1, av2, av3); 
}


boundary_type Lattice::boundary_condition(std::string& bc) const
{
  boost::to_upper(bc);
  if (bc=="OPEN") {
    return boundary_type::open;
  } 
  else if (bc=="PERIODIC") {
    return boundary_type::periodic;
  }
  else if (bc=="ANTIPERIODIC") {
    return boundary_type::antiperiodic;
  }
  else {
    throw std::range_error("error: latticelibrary: invalid boundary condition");
  }
}

Vector3i Lattice::get_next_bravindex(const Vector3i& current_index) const
{
  /* Returns the next Bravais lattice index. 
  ! Index for first unit cell = (0,0,0)
  ! Index for last unit cell = (N1-1, N2-1, N3-1)
   */
  Vector3i next_index = current_index;
  if (++next_index[0] >= static_cast<int>(extent[dim1].size)) {
    next_index[0] = 0;
    if (++next_index[1] >= static_cast<int>(extent[dim2].size)) {
      next_index[1] = 0;
      if (++next_index[2] >= static_cast<int>(extent[dim3].size)) {
        next_index[2] = 0;
      }
    }
  }
  return next_index;
}

std::pair<Vector3i, int> Lattice::boundary_wrap(const Vector3i& cell_idx) const
{
  Vector3i new_idx(cell_idx);
  int phase = 1;
  for (unsigned dim=dim1; dim<=dim3; ++dim) {
    if (new_idx[dim]<0 || new_idx[dim]>=static_cast<int>(extent[dim].size)) {
      if (extent[dim].bc == boundary_type::periodic) {
        new_idx[dim] = new_idx[dim] % extent[dim].size;
        if (new_idx[dim]<0) new_idx[dim] += static_cast<int>(extent[dim].size);
        /* Determine phase: 
           Phase is negative, if the edge gets wrapped across
           antiperiodic' boundary odd number of times */
        if (extent[dim].periodicity == boundary_type::antiperiodic) {
          int n = std::abs(cell_idx[dim] / static_cast<int>(extent[dim].size));
          //int n = abs(cell_idx[dim] / extent[dim].size);
          if (cell_idx[dim]<0) n++;
          if (n % 2 != 0) phase = -phase;
        }
      } 
      else new_idx[dim] = -1;
    }
  }
  return std::pair<Vector3i, int>(new_idx, phase);
}


} // end namespace lattice














