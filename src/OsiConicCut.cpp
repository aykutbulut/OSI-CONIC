// OsiConic headers
#include "OsiConicCut.hpp"
// STDLIB headers
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>

OsiConicCut::OsiConicCut(): size_(-1),
			    members_(0),
			    type_(OSI_QUAD),
			    num_new_rows_(-1),
			    rows_(0),
			    row_lb_(0),
			    row_ub_(0),
			    cols_(0),
			    col_lb_(0),
			    col_ub_(0) {
}

OsiConicCut::OsiConicCut(int num_new_rows, int cone_size):
     size_(cone_size),
     members_(0),
     num_new_rows_(num_new_rows),
     rows_(0),
     row_lb_(0),
     row_ub_(0),
     cols_(0),
     col_lb_(0),
     col_ub_(0) {
  // allocate memory for members_
  members_ = new int[size_];
  // allocate memory for rows_
  rows_ = new double*[num_new_rows_];
  for (int i=0; i<num_new_rows_; ++i) {
    rows_[i] = new double[size_];
  }
  // allocate memory for row bounds
  row_lb_ = new double[num_new_rows_];
  row_ub_ = new double[num_new_rows_];
}

// copy constructor
OsiConicCut::OsiConicCut(const OsiConicCut & other) {
  setCutRow(other.cutRowPtr(), other.numCutRows(), other.coneSize());
  setCutCol(other.cutCol());
  setCutRowLb(other.cutRowLb(), other.numCutRows());
  setCutRowUb(other.cutRowUb(), other.numCutRows());
  setCutColLb(other.cutColLb(), other.numCutCols());
  setCutColUb(other.cutColUb(), other.numCutCols());
  setConeMembers(other.coneMembers(), other.coneSize());
  setConeType(other.coneType());
}

// copy assignment operator
OsiConicCut & OsiConicCut::operator=(const OsiConicCut & rhs) {
  setCutRow(rhs.cutRowPtr(), rhs.numCutRows(), rhs.coneSize());
  setCutCol(rhs.cutCol());
  setCutRowLb(rhs.cutRowLb(), rhs.numCutRows());
  setCutRowUb(rhs.cutRowUb(), rhs.numCutRows());
  setCutColLb(rhs.cutColLb(), rhs.numCutCols());
  setCutColUb(rhs.cutColUb(), rhs.numCutCols());
  setConeMembers(rhs.coneMembers(), rhs.coneSize());
  setConeType(rhs.coneType());
  return *this;
}

OsiConicCut::~OsiConicCut() {
  if (members_)
    delete[] members_;
  if (rows_) {
    for (int i=0; i<num_new_rows_; ++i) {
      delete[] rows_[i];
    }
    delete[] rows_;
  }
  if (row_lb_) {
    delete[] row_lb_;
  }
  if (row_ub_) {
    delete[] row_ub_;
  }
  if (cols_) {
    delete cols_;
  }
  if (col_lb_) {
    delete[] col_lb_;
  }
  if (col_ub_) {
    delete[] col_ub_;
  }
}

// CUT RETRIVAL FUNCTIONS
// number of new rows to be added to model
// this will return -1 if num_new_rows is not set yet.
int OsiConicCut::numCutRows() const {
  return num_new_rows_;
}

// number of new columns to be added to model
int OsiConicCut::numCutCols() const {
  return cols_->getNumCols();
}

// get new rows
double const * const * OsiConicCut::cutRowPtr() const {
  return rows_;
}

// get new row i
double const * OsiConicCut::cutRowPtr(int i) const {
  if (num_new_rows_==-1) {
    std::cerr << "OsiConic: Number of rows is not initialized."
	      << std::endl;
    throw "";
  }
  if (i>=num_new_rows_) {
    std::cerr << "OsiConic: There is no row with the given index."
	      << std::endl;
    throw "";
  }
  return rows_[i];
}

// get new columns
// returns 0 if not initialized.
CoinPackedMatrix const & OsiConicCut::cutCol() const {
  return *cols_;
}

// get lower bound for new rows
double const * OsiConicCut::cutRowLb() const {
  return row_lb_;
}

double OsiConicCut::cutRowLb(int i) const {
  if (num_new_rows_==-1) {
    std::cerr << "OsiConic: Number of rows is not initialized."
	      << std::endl;
    throw "";
  }
  if (i>=num_new_rows_) {
    std::cerr << "OsiConic: There is no row with the given index."
	      << std::endl;
    throw "";
  }
  if (row_lb_==0) {
    std::cerr << "OsiConic: Row lower bounds are not initialized."
	      << std::endl;
    throw "";
  }
  return row_lb_[i];
}

double const * OsiConicCut::cutRowUb() const {
  return row_ub_;
}

double OsiConicCut::cutRowUb(int i) const {
  if (num_new_rows_==-1) {
    std::cerr << "OsiConic: Number of rows is not initialized."
	      << std::endl;
    throw "";
  }
  if (i>=num_new_rows_) {
    std::cerr << "OsiConic: There is no row with the given index."
	      << std::endl;
    throw "";
  }
  if (row_ub_==0) {
    std::cerr << "OsiConic: Row upper bounds are not initialized."
	      << std::endl;
    throw "";
  }
  return row_ub_[i];
}

// get column bound for new variables cut introduced
double const * OsiConicCut::cutColLb() const {
  return col_lb_;
}

double OsiConicCut::cutColLb(int i) const {
  if (cols_==0) {
    std::cerr << "OsiConic: Columns are not initialized."
	      << std::endl;
    throw "";
  }
  int num_cols = cols_->getNumCols();
  if (i>=num_cols) {
    std::cerr << "OsiConic: There is no column with the given index."
	      << std::endl;
    throw "";
  }
  if (col_lb_==0) {
    std::cerr << "OsiConic: Column lower bounds are not initialized."
	      << std::endl;
    throw "";
  }
  return col_lb_[i];
}

double const * OsiConicCut::cutColUb() const {
  return col_ub_;
}

double OsiConicCut::cutColUb(int i) const {
  if (cols_==0) {
    std::cerr << "OsiConic: Columns are not initialized."
	      << std::endl;
    throw "";
  }
  int num_cols = cols_->getNumCols();
  if (i>=num_cols) {
    std::cerr << "OsiConic: There is no column with the given index."
	      << std::endl;
    throw "";
  }
  if (col_ub_==0) {
    std::cerr << "OsiConic: Column upper bounds are not initialized."
	      << std::endl;
    throw "";
  }
  return col_ub_[i];
}

int OsiConicCut::coneSize() const {
  return size_;
}

OsiConeType OsiConicCut::coneType() const {
  return type_;
}

int const * OsiConicCut::coneMembers() const {
  return members_;
}

// SETTING CUT DATA
// set cut row
void OsiConicCut::setCutRow(double const * const * row,
			    int num_rows, int cone_size) {
  num_new_rows_ = num_rows;
  size_ = cone_size;
  // delete old rows_
  if (rows_) {
    for (int i=0; i<num_new_rows_; ++i)
      delete[] rows_[i];
    delete[] rows_;
  }
  rows_ = new double*[num_new_rows_];
  for (int i=0; i<num_new_rows_; ++i) {
    rows_[i] = new double[size_];
    std::copy(row[i], row[i]+size_, rows_[i]);
  }
}

// set cut col
void OsiConicCut::setCutCol(const CoinPackedMatrix & col) {
  if (cols_)
    delete cols_;
  cols_ = new CoinPackedMatrix(col);
}

// set bounds for new rows
void OsiConicCut::setCutRowLb(double const * lb, int num_rows) {
  num_new_rows_=num_rows;
  // free old bounds
  if (row_lb_) {
    delete[] row_lb_;
  }
  row_lb_ = new double[num_new_rows_];
  std::copy(lb, lb+num_new_rows_, row_lb_);
}

void OsiConicCut::setCutRowLb(int i, double lb) {
  if (row_lb_==0) {
    std::cerr << "OsiConic: Row bounds for other indices are not present."
	      << " I do not know how to set the bounds for other rows."
	      << std::endl;
    throw "";
  }
  if (i>=num_new_rows_) {
    std::cerr << "OsiConic: There is no row with index i."
	      << std::endl;
    throw "";
  }
  row_lb_[i] = lb;
}

void OsiConicCut::setCutRowUb(double const * ub, int num_rows) {
  num_new_rows_=num_rows;
  // free old bounds
  if (row_ub_) {
    delete[] row_ub_;
  }
  row_ub_ = new double[num_new_rows_];
  std::copy(ub, ub+num_new_rows_, row_ub_);
}

void OsiConicCut::setCutRowUb(int i, double ub) {
  if (row_ub_==0) {
    std::cerr << "OsiConic: Row bounds for other indices are not present."
	      << " I do not know how to set the bounds for other rows."
	      << std::endl;
    throw "";
  }
  if (i>=num_new_rows_) {
    std::cerr << "OsiConic: There is no row with index i."
	      << std::endl;
    throw "";
  }
  row_ub_[i] = ub;
}

// set bounds for new cols
void OsiConicCut::setCutColLb(double const * lb, int num_cols) {
  if (col_lb_)
    delete[] col_lb_;
  col_lb_ = new double[num_cols];
  std::copy(lb, lb+num_cols, col_lb_);
}

void OsiConicCut::setCutColLb(int i, double lb) {
  if (col_lb_==0) {
    std::cerr << "OsiConic: Column bounds for other indices are not present."
	      << " I do not know how to set the bounds for other columns."
	      << std::endl;
    throw "";
  }
  col_lb_[i] = lb;
}

void OsiConicCut::setCutColUb(double const * ub, int num_cols) {
  if (col_ub_)
    delete[] col_ub_;
  col_ub_ = new double[num_cols];
  std::copy(ub, ub+num_cols, col_ub_);
}

void OsiConicCut::setCutColUb(int i, double ub) {
  if (col_ub_==0) {
    std::cerr << "OsiConic: Column bounds for other indices are not present."
	      << " I do not know how to set the bounds for other columns."
	      << std::endl;
    throw "";
  }
  col_ub_[i] = ub;
}

// set type of the cone we are using for cut generation
void OsiConicCut::setConeType(OsiConeType type) {
  type_ = type;
}

// set members of the cone we are using for cut generation
void OsiConicCut::setConeMembers(int const *  members, int size) {
  if (size_==-1)
    size_=size;
  if (size_!=size) {
    delete[] members_;
    members_ = new int[size];
  }
  if (members_==0)
    members_ = new int[size_];
  std::copy(members, members+size_, members_);
}

void OsiConicCut::print() const {
  // print rows
  for (int i=0; i<num_new_rows_; ++i) {
    for (int j=0; j<size_; ++j) {
      std::cout << rows_[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "Col matrix: " <<std::endl;
  cols_->dumpMatrix();
  // print conic constraint
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
  // todo(aykut): consistency of other data elements?
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
  // todo(aykut): consistency of other data elements?
  return true;
}

bool OsiConicCut::infeasible (const OsiConicSolverInterface & si) const {
  // todo(aykut): implement this considering all data available.
  return false;
}

// returns infeasiblity of the cut with respect to solution passed.
// returns positive if cuts of that solution.
double OsiConicCut::violated (const double * solution) const {
  double violation = 0.0;
  // compute the violtion of the conic cut
  // first check the members  of the cone to see whether they are all
  // old variables (ie we know their value at solution). It is easy if
  // they are. If not then compute the value of the new columns using the
  // rows and then compute the violation.
  return violation;
}


//EFFECTIVENESS AND VALIDITY
void OsiConicCut::setEffectiveness(double e) {
  effectiveness_ = e;
}

double OsiConicCut::effectiveness() const {
  return effectiveness_;
}

void OsiConicCut::setGloballyValid(bool validity) {
  globallyValid_ = validity;
}

void OsiConicCut::setGloballyValid() {
  globallyValid_ = 1;
}

void OsiConicCut::setNotGloballyValid() {
  globallyValid_ = 0;
}

bool OsiConicCut::globallyValid() const {
  return bool(globallyValid_);
}

// nonzero is valid
void OsiConicCut::setGloballyValidAsInteger(int validity) {
  globallyValid_ = validity;
}

int OsiConicCut::globallyValidAsInteger() const {
  return globallyValid_;
}

OsiConicCut * OsiConicCut::clone() const {
  OsiConicCut * new_cut = new OsiConicCut();
  new_cut->setConeMembers(coneMembers(), coneSize());
  new_cut->setConeType(coneType());
  new_cut->setCutRow(cutRowPtr(), numCutRows(), coneSize());
  new_cut->setCutRowLb(cutRowLb(), numCutRows());
  new_cut->setCutRowUb(cutRowUb(), numCutRows());
  new_cut->setCutCol(cutCol());
  new_cut->setCutColLb(cutColLb(), numCutCols());
  new_cut->setCutColUb(cutColUb(), numCutCols());
  new_cut->setEffectiveness(effectiveness());
  new_cut->setGloballyValid(globallyValid());
}
