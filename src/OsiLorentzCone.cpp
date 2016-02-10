#include "OsiLorentzCone.hpp"

OsiLorentzCone::OsiLorentzCone(OsiLorentzConeType lorentzType, int size,
			       int const * members):
  OsiCone(OSI_LORENTZ), lType_(lorentzType), size_(size) {
  if (size<2) {
    std::cerr << "Cones should be size 2 at least!" << std::endl;
    throw std::exception();
  }
  if (lorentzType==OSI_RQUAD && size<3) {
    std::cerr << "Rotated cones should be size 3 at least!" << std::endl;
    throw std::exception();
  }
  members_ = new int[size];
  std::copy(members, members+size, members_);
}

OsiLorentzCone::OsiLorentzCone(OsiLorentzCone const & other):
  OsiCone(OSI_LORENTZ), lType_(other.lorentzType()), size_(other.size()) {
  members_ = new int[size_];
  int const * other_members = other.members();
  std::copy(other_members, other_members+size_, members_);
}

OsiLorentzCone::~OsiLorentzCone() {
  if (members_) {
    delete[] members_;
  }
}

OsiLorentzConeType OsiLorentzCone::lorentzType() const {
  return lType_;
}

int OsiLorentzCone::size() const {
  return size_;
}

int const * OsiLorentzCone::members() const {
  return members_;
}

// check whether a given point is feasible
bool OsiLorentzCone::feasible(double const * point) const {
  std::cerr << "Work in process!" << std::endl;
  throw std::exception();
}

// project a given point to the cone
// return 0 if projection was successful,
// 1 if point is already on the cone boundry,
// 2 if point is inside the cone.
int OsiLorentzCone::project(double const * point, double * projection) const {
  std::cerr << "Work in process!" << std::endl;
  throw std::exception();
  return 0;
}
