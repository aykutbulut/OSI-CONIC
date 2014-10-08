// OsiConic headers
#include "OsiConicCut.hpp"
// STDLIB headers
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>

OsiConicCut::OsiConicCut(): members_(0), size_(0) {
}

OsiConicCut::OsiConicCut(int size, int const * members, OsiConeType type) {
  // copy members
  members_ = new int[size];
  std::copy(members, members+size, members_);
  // copy cone type
  type_ = type;
}

OsiConicCut::~OsiConicCut() {
  if (members_)
    delete members_;
}

void OsiConicCut::print() const {
  std::cout << std::setw(10) << "Type"
            << std::setw(10) << "Num memb."
            << std::setw(10) << "Members"
            << std::endl;
  std::cout << std::setw(10) << type_
            << std::setw(10) << size_
            << std::setw(10) << members_[0]
            << std::endl;
  for (int i=1; i<size_; ++i) {
    std::cout << std::setw(30) << members_[i] << std::endl;
  }
}

bool OsiConicCut::operator==(const OsiConicCut & rhs) const {
  // check type
  if (type_!=rhs.type())
    return false;
  // check size
  if (size_!=rhs.size())
    return false;
  // check members
  int const * rhs_members = rhs.members();
  for (int i=0; i<size_; ++i) {
    if (members_[i]!=rhs_members[i])
      return false;
  }
  return true;
}

bool OsiConicCut::operator!= (const OsiConicCut & rhs) const {
  bool flag = operator==(rhs);
  return !flag;
}

//
// A conic cut is more effective if it has the same leading variable/variables
// plus more of remaining variables.
// ie. cut1: members: 3,5,7,9,2,4 type: canonical
//     cut2: members: 3,7,5,4,2   type: canonical
// cut 1 is more effective and dominates cut2 since it has 9 as a member.
bool OsiConicCut::operator< (const OsiConicCut & rhs) const {
  int const * rhs_members = rhs.members();
  if (rhs.type()!=type_)
    return false;
  if (rhs.size()<=size_)
    return false;
  if (members_[0]!=rhs_members[0]) {
    return false;
  }
  int start = 1;
  if (type_==OSI_RQUAD) {
    if (members_[1]!=rhs_members[1])
      return false;
    start = 2;
  }
  std::set<int> rhs_tail(rhs_members+start, rhs_members+rhs.size());
  // if every element in this is also in rhs return true
  for (int i=start; i<size_; ++i) {
    if (rhs_tail.find(members_[i])==rhs_tail.end()) {
      rhs_tail.clear();
      return false;
    }
  }
  rhs_tail.clear();
  return true;
}

bool OsiConicCut::operator> (const OsiConicCut & rhs) const {
  int const * rhs_members = rhs.members();
  if (rhs.type()!=type_)
    return false;
  if (rhs.size()>=size_)
    return false;
  if (members_[0]!=rhs_members[0]) {
    return false;
  }
  int start = 1;
  if (type_==OSI_RQUAD) {
    if (members_[1]!=rhs_members[1])
      return false;
    start = 2;
  }
  std::set<int> tail(members_+start, members_+size_);
  // if every element in this is also in rhs return true
  for (int i=start; i<size_; ++i) {
    if (tail.find(rhs_members[i])==tail.end()) {
      tail.clear();
      return false;
    }
  }
  tail.clear();
  return true;
}

bool OsiConicCut::consistent () const {
  // it the conic cut is in canonical form then it should have at least 2
  // members
  if (type_==OSI_QUAD) {
    if (size_<2)
      return false;
  }
  if (type_==OSI_RQUAD) {
    if (size_<3)
      return false;
  }
  // return false if we have a negative index member
  for (int i=0; i<size_; ++i) {
    if (members_[i]<0) {
      return false;
    }
  }
  // todo(aykut): check whether there are duplicate elements? do we need this?
  return true;
}

bool OsiConicCut::consistent (const OsiConicSolverInterface & si) const {
  // check whether the members are actually existing variables in si
  int max_index = si.getNumCols()-1;
  for (int i=0; i<size_; ++i) {
    if (members_[i]>max_index) {
      return false;
    }
  }
  // return false if a member is repeating
  std::set<int> memb (members_, members_+size_);
  if (memb.size()!=size_) {
    memb.clear();
    return false;
  }
  memb.clear();
  return true;
}

bool OsiConicCut::infeasible (const OsiConicSolverInterface & si) const {
  // a conic cut is always feasible
  return false;
}

// returns infeasiblity of the cut with respect to solution passed.
// returns positive if cuts of that solution.
double OsiConicCut::violated (const double * solution) const {
  int start=0;
  double sum=0.0;
  double lhs = 0.0;
  double violation = 0.0;
  if (type_==OSI_QUAD) {
    start=1;
    lhs = solution[members_[0]];
  }
  else {
    start=2;
    lhs = 2.0*solution[members_[0]]*solution[members_[1]];
  }
  for (int i=start; i<size_; ++i) {
    sum += solution[members_[i]]*solution[members_[i]];
  }
  violation = lhs - sqrt(sum);
  return violation;
}

int OsiConicCut::size() const {
  return size_;
}

OsiConeType OsiConicCut::type() const {
  return type_;
}

int const * OsiConicCut::members() const {
  return members_;
}
