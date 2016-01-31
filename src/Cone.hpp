#ifndef Cone_H
#define Cone_H

typedef enum {
  OSI_LORENTZ=0,
  OSI_SCALED
} OsiConeType;

typedef enum {
  OSI_QUAD=0,
  OSI_RQUAD
} OsiLorentzConeType;

class Cone {
  OsiConeType coneType_;
public:
  OsiConeType type() const {return coneType_; }
  // check whether a given point is feasible
  virtual bool feasible(double const * point) const = 0;
  // project a given point to the cone
  // return 0 if projection was successful,
  // 1 if point is already on the cone boundry,
  // 2 if point is inside the cone.
  virtual int project(double const * point, double * projection) const = 0;
};

#endif
