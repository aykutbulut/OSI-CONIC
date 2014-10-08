#ifndef OsiConicCut_H
#define OsiConicCut_H

// Osi headers
#include <OsiCut.hpp>
// Conic Osi headers
#include "OsiConicSolverInterface.hpp"

// holds the indices of cone members and cone type.

class OsiConicCut: OsiCut {
public:
  // default constructor
  OsiConicCut();
  OsiConicCut(int size, int const * members, OsiConeType type);
  // destractor
  virtual ~OsiConicCut();
  int size() const;
  OsiConeType type() const;
  int const * members() const;
  // virtual functions inherited
  virtual void print () const;
  virtual bool operator== (const OsiConicCut & rhs) const;
  virtual bool operator!= (const OsiConicCut & rhs) const;
  virtual bool operator< (const OsiConicCut & rhs) const;
  virtual bool operator> (const OsiConicCut & rhs) const;
  virtual bool consistent () const;
  virtual bool consistent (const OsiConicSolverInterface & si) const;
  virtual bool infeasible (const OsiConicSolverInterface & si) const;
  virtual double violated (const double * solution) const;
private:
  int * members_;
  int size_;
  OsiConeType type_;
};

#endif
