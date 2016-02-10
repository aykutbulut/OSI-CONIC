#ifndef LorentzCone_H
#define LorentzCone_H

#include <iostream>
#include "OsiCone.hpp"

/*!
  Implements Lorentz cone, can be regular (x_1 >= ||x_{2:n}||) or
  rotated cone (2x_1 x_2 >= ||x_{3:n}||, x_1 >=0, x_2>=0).
 */
class OsiLorentzCone: public OsiCone {
  OsiLorentzConeType const lType_;
  int const size_;
  int * members_;
public:
  OsiLorentzCone(OsiLorentzConeType type, int size, int const * members);
  OsiLorentzCone(OsiLorentzCone const & other);
  virtual ~OsiLorentzCone();
  OsiLorentzConeType lorentzType() const;
  int size() const;
  int const * members() const;
  // check whether a given point is feasible
  virtual bool feasible(double const * point) const;
  // project a given point to the cone
  // return 0 if projection was successful,
  // 1 if point is already on the cone boundry,
  // 2 if point is inside the cone.
  virtual int project(double const * point, double * projection) const;
private:
  OsiLorentzCone();
  OsiLorentzCone & operator=(OsiLorentzCone const & rhs);
};

#endif
