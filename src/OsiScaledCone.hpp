#ifndef LorentzCone_H
#define LorentzCone_H

#include "OsiCone.hpp"

// Implements Scaled cone ||Ax-b|| <= d^T x -h
class OsiScaledCone: public OsiCone {
public:
  OsiScaledCone(): OsiCone(OSI_SCALED) {}
  ~OsiScaledCone() {}
  // check whether a given point is feasible
  virtual bool feasible(double const * point) const {
    std::cerr << "Work in process!" << std::endl;
    throw std::exception();
  }
  // project a given point to the cone
  // return 0 if projection was successful,
  // 1 if point is already on the cone boundry,
  // 2 if point is inside the cone.
  virtual int project(double const * point, double * projection) const {
    std::cerr << "Work in process!" << std::endl;
    throw std::exception();
    return 0;
  }
};

#endif
