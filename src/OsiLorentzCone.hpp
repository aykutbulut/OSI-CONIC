#ifndef LorentzCone_H
#define LorentzCone_H

#include <Cone.hpp>

// Implements Lorentz cone, can be regular (x_1 >= ||x_{2:n}||) or
// rotated cone (2x_1 x_2 >= ||x_{3:n}||, x_1 >=0, x_2>=0)
class LorentzCone: public Cone {
  OsiLorentzConeType const lType_;
  int const size_;
  int * members_;
public:
  OsiLorentzConeType type() const { return type_; }
  int size() const { return size_; }
  int const * members() const { return members_; }
  LorentzCone(OsiLorentzConeType type, int size, int const * members):
    type_(type), size_(size) {
    if (size<2) {
      std::cerr << "Cones should be size 2 at least!" << std::endl;
      throw std::exception();
    }
    if (type==OSI_RQUAD && size<3) {
      std::cerr << "Rotated cones should be size 3 at least!" << std::endl;
      throw std::exception();
    }
    std::copy(members, members+size, members_);
  }
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
private:
  LorentzCone();
  LorentzCone(LorentzCone const & other);
  LorentzCone & operator=(LorentzCone const & rhs);
};

#endif
