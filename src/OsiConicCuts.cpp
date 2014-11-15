#include "OsiConicCuts.hpp"

//------------------------------------------------------------
//
// Embedded iterator class implementations
//
//------------------------------------------------------------
OsiConicCuts::iterator::iterator(OsiConicCuts & cuts) :
  cuts_(cuts),
  cutIndex_(-1),
  cutP_(NULL) {
  this->operator++();
}

OsiConicCuts::iterator::iterator(const OsiConicCuts::iterator & src) :
  cuts_(src.cuts_),
  cutIndex_(src.cutIndex_),
  cutP_(src.cutP_) {
  // nothing to do here
}

OsiConicCuts::iterator & OsiConicCuts::iterator::operator=(const OsiConicCuts::iterator &rhs) {
  if (this != &rhs) {
    cuts_=rhs.cuts_;
    cutIndex_=rhs.cutIndex_;
    cutP_=rhs.cutP_;
  }
  return *this;
}

OsiConicCuts::iterator::~iterator() {
  //nothing to do
}

OsiConicCuts::iterator OsiConicCuts::iterator::begin() {
  cutIndex_=-1;
  this->operator++();
  return *this;
}

OsiConicCuts::iterator OsiConicCuts::iterator::end() {
  cutIndex_=cuts_.sizeCuts();
  cutP_=NULL;
  return *this;
}

OsiConicCuts::iterator OsiConicCuts::iterator::operator++() {
  cutP_ = NULL;
  // Are there any more cuts to consider?
  if ((cutIndex_+1)<cuts_.sizeCuts()) {
    cutIndex_++;
    cutP_=cuts_.cutPtr(cutIndex_);
  }
  return *this;
}

//------------------------------------------------------------
//
// Embedded const_iterator class implementation
//
//------------------------------------------------------------
OsiConicCuts::const_iterator::const_iterator(const OsiConicCuts & cuts):
  cutsPtr_(&cuts),
  cutIndex_(-1),
  cutP_(NULL) {
  this->operator++();
}

OsiConicCuts::const_iterator::const_iterator(const OsiConicCuts::const_iterator & src):
  cutsPtr_(src.cutsPtr_),
  cutIndex_(src.cutIndex_),
  cutP_(src.cutP_) {
  // nothing to do here
}

OsiConicCuts::const_iterator &
OsiConicCuts::const_iterator::operator=(const OsiConicCuts::const_iterator & rhs) {
  if (this != &rhs) {
    cutsPtr_=rhs.cutsPtr_;
    cutIndex_=rhs.cutIndex_;
    cutP_=rhs.cutP_;
  }
  return *this;
}

OsiConicCuts::const_iterator::~const_iterator() {
  //nothing to do
}

OsiConicCuts::const_iterator OsiConicCuts::const_iterator::begin() {
  cutIndex_=-1;
  this->operator++();
  return *this;
}

OsiConicCuts::const_iterator OsiConicCuts::const_iterator::end() {
  cutIndex_=cutsPtr_->sizeCuts();
  cutP_=NULL;
  return *this;
}


OsiConicCuts::const_iterator OsiConicCuts::const_iterator::operator++() {
  cutP_ = NULL;
  // Are there any more row cuts to consider?
  if (cutIndex_<cutsPtr_->sizeCuts()) {
    cutIndex_++;
    cutP_=cutsPtr_->cutPtr(cutIndex_);
  }
  return *this;
}

// Default constructor
OsiConicCuts::OsiConicCuts(): cutPtrs_() {
}

/// Copy constructor
OsiConicCuts::OsiConicCuts (const OsiConicCuts & other): cutPtrs_() {
  gutsOfCopy(other);
}


/// Copy Assignment operator
OsiConicCuts & OsiConicCuts::operator=(const OsiConicCuts & rhs) {
  if (this != &rhs) {
    gutsOfDestructor();
    gutsOfCopy(rhs);
  }
  return *this;
}

/// copy function
void OsiConicCuts::gutsOfCopy(const OsiConicCuts & source) {
  assert(sizeCuts()==0);
  int num_cuts = source.sizeCuts();
  for (int i=0; i<num_cuts; ++i) {
    insert(source.cut(i));
  }
}

/// Destructor
OsiConicCuts::~OsiConicCuts () {
  gutsOfDestructor();
}

void OsiConicCuts::gutsOfDestructor() {
  int i;
  int num_cuts = static_cast<int>(cutPtrs_.size());
  for (i=0; i<num_cuts; i++) {
    if (cutPtrs_[i]->globallyValidAsInteger()!=2)
      delete cutPtrs_[i];
  }
  cutPtrs_.clear();
  assert(sizeCuts()==0);
}


// insert cuts
void OsiConicCuts::insert(const OsiConicCut & cut) {
  OsiConicCut * new_cut_ptr = cut.clone();
  cutPtrs_.push_back(new_cut_ptr);
}

void OsiConicCuts::insert(OsiConicCut * & cutPtr) {
  cutPtrs_.push_back(cutPtr);
  cutPtr = NULL;
}

void OsiConicCuts::insert(const OsiConicCuts & cuts) {
  OsiConicCuts::const_iterator it;
  for(it=cuts.begin(); it!=cuts.end(); ++it) {
    insert(**it);
  }
}

void OsiConicCuts::insertIfNotDuplicate(OsiConicCut & cut,
					CoinAbsFltEq treatAsSame) {
  bool notDuplicate=true;
  if (notDuplicate) {
    insert(cut);
  }
}

void OsiConicCuts::insertIfNotDuplicate(OsiConicCut & cut, CoinRelFltEq treatAsSame) {
  bool notDuplicate=true;
  if (notDuplicate) {
    insert(cut);
  }
}

int OsiConicCuts::sizeCuts() const {
  return cutPtrs_.size();
}

void OsiConicCuts::printCuts() const {
  std::cerr << "Not implemented yet." << std::endl;
}

/// Get pointer to i'th cut
OsiConicCut * OsiConicCuts::cutPtr(int i) {
  return cutPtrs_[i];
}

/// Get const pointer to i'th row cut
OsiConicCut const * OsiConicCuts::cutPtr(int i) const {
  return cutPtrs_[i];
}

/// Get i'th cut
OsiConicCut & OsiConicCuts::cut(int i) {
  return *cutPtr(i);
}

/// Get const reference to i'th cut
OsiConicCut const & OsiConicCuts::cut(int i) const {
  return *cutPtr(i);
}

/// Get pointer to the most effective cut
OsiConicCut * OsiConicCuts::mostEffectiveCutPtr() {
  iterator b=begin();
  iterator e=end();
  OsiConicCut * retVal = NULL;
  double maxEff = COIN_DBL_MIN;
  for (OsiConicCuts::iterator it=b; it!=e; ++it) {
    if (maxEff < (*it)->effectiveness() ) {
      maxEff = (*it)->effectiveness();
      retVal = *it;
    }
  }
  return retVal;
}

/// Get const pointer to the most effective cut
OsiConicCut const * OsiConicCuts::mostEffectiveCutPtr() const {
  const_iterator b=begin();
  const_iterator e=end();
  return *(std::min_element(b, e, OsiCutCompare()));
}

/// Remove i'th cut from collection
void OsiConicCuts::eraseCut(int i) {
  delete cutPtrs_[i];
  cutPtrs_.erase(cutPtrs_.begin()+i);
}

/// Get pointer to i'th cut and remove ptr from collection
OsiConicCut * OsiConicCuts::cutPtrAndZap(int i) {
  OsiConicCut * cut = cutPtrs_[i];
  cutPtrs_[i]=NULL;
  cutPtrs_.erase(cutPtrs_.begin()+i);
  return cut;
}

/*! \brief Clear all row cuts without deleting them

  Handy in case one wants to use CGL without managing cuts in one of
  the OSI containers. Client is ultimately responsible for deleting the
  data structures holding the row cuts.
*/
void OsiConicCuts::dumpCuts() {
  cutPtrs_.clear();
}

void OsiConicCuts::eraseAndDumpCuts(const std::vector<int> to_erase) {
  for (unsigned i=0; i<to_erase.size(); i++) {
    delete cutPtrs_[to_erase[i]];
  }
  cutPtrs_.clear();
}

void OsiConicCuts::sort() {
  std::sort(cutPtrs_.begin(), cutPtrs_.end(), OsiCutCompare());
}

