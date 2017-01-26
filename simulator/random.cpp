/*---------------------------------------------------------------------------
* Copyright (C) 2015-2016 by Amal Medhi <amedhi@iisertvm.ac.in>.
* All rights reserved.
* Author: Amal Medhi
* Date:   2016-03-09 15:27:50
* Last Modified by:   amedhi
* Last Modified time: 2017-01-19 16:11:43
*----------------------------------------------------------------------------*/
#include "random.h"

namespace rng {

RandomNumber::RandomNumber() : seed_type_(0), real_generator(0.0, 1.0) 
{
  //for (auto& g : state_generators) g = int_dist(-1,-1);
}
  
RandomNumber::RandomNumber(const unsigned& seed_type) 
  : seed_type_(seed_type), real_generator(0.0, 1.0)
{
  if (seed_type_==1) time_seed();
  //for (auto& g : state_generators) g = int_dist(-1,-1);
}

void RandomNumber::seed(const int& seed_type) {
  seed_type_ = seed_type;
  if (seed_type_==1) time_seed();
} 

void RandomNumber::time_seed(void) 
{
  myclock::time_point now = myclock::now();
  myclock::duration till_now = now.time_since_epoch();
  unsigned itc = till_now.count();
  this->std::mt19937_64::seed(itc);
}









} // end namespace basis
