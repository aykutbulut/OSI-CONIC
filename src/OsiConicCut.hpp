// A conic cut is fundamentally different than a cut for linear problem.
// For most of the work in literature a conic cut comes with a conic
// constraint and plus some linear constraints. This means a conic cut
// is more than just a conic constraint. Moreover a conic cut may introduce
// new variables to the model. We keep additional row and column information
// in this class along the conic cut information.
// For now we assume the new rows are dense in the conic space,
// (it is in CglConicGD2 case at least) we keep these rows as arrays.
// We assume the columns that corresponds to new variables in the new rows
// are sparce  (it is in CglConicGD2 case at least), so we keep this portion
// of the new rows as CoinPackedMatrix type.

// TODO(aykut): Decide who frees the data we store here.
// TODO(aykut): Can rows have columns corresponding to variables that
// are not a member of the resulting conic cut? We assume answer is no.

#ifndef OsiConicCut_H
#define OsiConicCut_H

// Conic Osi headers
#include "OsiConicSolverInterface.hpp"

class OsiConicCut {
public:
  // default constructor
  OsiConicCut();
  // constructor with row and col dimensions
  OsiConicCut(int num_new_rows, int cone_size);
  // copy constructor
  OsiConicCut(const OsiConicCut & other);
  // copy assignment operator
  OsiConicCut & operator=(const OsiConicCut & rhs);
  // destructor
  ~OsiConicCut();
  // CUT RETRIVAL FUNCTIONS
  // number of new rows to be added to model
  int numCutRows() const;
  // number of new columns to be added to model
  int numCutCols() const;
  // get new rows
  double const * const * cutRowPtr() const;
  // get new row i
  double const * cutRowPtr(int i) const;
  // get new columns
  CoinPackedMatrix const & cutCol() const;
  // get lower bound for new rows
  double const * cutRowLb() const;
  double cutRowLb(int i) const;
  double const * cutRowUb() const;
  double cutRowUb(int i) const;
  // get column bound for new variables cut introduced
  double const * cutColLb() const;
  double cutColLb(int i) const;
  double const * cutColUb() const;
  double cutColUb(int i) const;
  // size of conic cut
  int coneSize() const;
  // type of conic cut
  OsiConeType coneType() const;
  // members of the conic cut
  int const * coneMembers() const;
  // SETTING CUT DATA
  // set cut row
  void setCutRow(double const * const * row, int num_rows, int cone_size);
  // set cut col
  void setCutCol(const CoinPackedMatrix & col);
  // set bounds for new rows
  void setCutRowLb(double const * lb, int num_rows);
  void setCutRowLb(int i, double lb);
  void setCutRowUb(double const * ub, int num_rows);
  void setCutRowUb(int i, double ub);
  // set bounds for new cols
  void setCutColLb(double const * lb, int num_cols);
  void setCutColLb(int i, double lb);
  void setCutColUb(double const * ub, int num_cols);
  void setCutColUb(int i, double ub);
  // set type of the cone we are using for cut generation
  void setConeType(OsiConeType type);
  // set members of the cone we are using for cut generation
  void setConeMembers(int const *  members, int size);
  // clone cut
  OsiConicCut * clone() const;
  // SOME USEFULL FUNCTIONS
  void print() const;
  bool consistent() const;
  bool consistent(const OsiConicSolverInterface & si) const;
  bool infeasible(const OsiConicSolverInterface & si) const;
  double violated(const double * solution) const;
  //EFFECTIVENESS AND VALIDITY
  void setEffectiveness(double e);
  double effectiveness() const;
  void setGloballyValid(bool validity);
  void setGloballyValid();
  void setNotGloballyValid();
  bool globallyValid() const;
  // nonzero is valid
  void setGloballyValidAsInteger(int validity);
  int globallyValidAsInteger() const;
private:
  // size of resulting conic cut
  int size_;
  // indices of the resulting conic cut
  int * members_;
  // resulting conic cut type
  OsiConeType type_;
  // number of resulting new rows that comes with the cut
  int num_new_rows_;
  // for now we assume the new rows are dense in the conic space,
  // (it is in CglConicGD2 case at least) we keep these rows as arrays.
  double ** rows_;
  // row bounds, size is num_new_rows_
  double * row_lb_;
  double * row_ub_;
  // new columns, we assume they are sparse, size is size is num_new_rows_
  // times num_new_cols_
  CoinPackedMatrix * cols_;
  // column bounds corresponding to new variables, size is num_new_cols_
  double * col_lb_;
  double * col_ub_;
  // effectiveness
  double effectiveness_;
  // global validity
  int globallyValid_;
};

#endif
