#ifndef OsiConicCuts_H
#define OsiConicCuts_H

// OsiConic headers
#include "OsiConicCut.hpp"
// CoinUtils headers
#include <CoinFloatEqual.hpp>

typedef std::vector<OsiConicCut *> OsiVectorConicCutPtr;

class OsiConicCuts {
public:
  // iterator class
  class iterator {
    friend class OsiConicCuts;
  public:
    iterator(OsiConicCuts & cuts);
    iterator(const iterator & src);
    iterator & operator=(const iterator & rhs);
    ~iterator ();
    OsiConicCut * operator*() const {return cutP_;}
    iterator operator++();
    iterator operator++(int) {
      iterator temp = *this;
      ++*this;
      return temp;
    }
    bool operator==(const iterator & it) const {
      return cutIndex_==it.cutIndex_;
    }
    bool operator!=(const iterator & it) const {
      return !((*this)==it);
    }
    bool operator<(const iterator & it) const {
      return cutIndex_<it.cutIndex_;
    }
  private:
    iterator();
    iterator begin();
    iterator end();
    OsiConicCuts & cuts_;
    int cutIndex_;
    OsiConicCut * cutP_;
  };
  /// const iterator class
  class const_iterator {
    friend class OsiConicCuts;
  public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef OsiConicCut* value_type;
    typedef size_t difference_type;
    typedef OsiConicCut** pointer;
    typedef OsiConicCut*& reference;
  public:
    const_iterator(const OsiConicCuts & cuts);
    const_iterator(const const_iterator & src);
    const_iterator & operator=(const const_iterator & rhs);
    ~const_iterator();
    const OsiConicCut * operator*() const {return cutP_;}
    const_iterator operator++();
    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++*this;
      return temp;
    }
    bool operator==(const const_iterator & it) const {
      return cutIndex_==it.cutIndex_;
    }
    bool operator!=(const const_iterator & it) const {
      return !((*this)==it);
    }
    bool operator<(const const_iterator & it) const {
      return cutIndex_<it.cutIndex_;
    }
  private:
    inline const_iterator() {}
    // *THINK* : how to inline these without sticking the code here (ugly...)
    const_iterator begin();
    const_iterator end();
    const OsiConicCuts * cutsPtr_;
    int cutIndex_;
    const OsiConicCut * cutP_;
  };
  /// Default constructor
  OsiConicCuts ();
  /// Copy constructor
  OsiConicCuts (const OsiConicCuts & other);
  /// Copy Assignment operator
  OsiConicCuts & operator=(const OsiConicCuts & rhs);
  /// copy function
  void gutsOfCopy(const OsiConicCuts & source);
  /// Destructor
  ~OsiConicCuts ();
  void gutsOfDestructor();
  // insert cuts
  void insert(const OsiConicCut & cut);
  void insert(OsiConicCut * & cutPtr);
  void insert(const OsiConicCuts & cuts);
  void insertIfNotDuplicate(OsiConicCut & cut,
			    CoinAbsFltEq treatAsSame=CoinAbsFltEq(1.0e-12));
  void insertIfNotDuplicate(OsiConicCut & cut, CoinRelFltEq treatAsSame);
  int sizeCuts() const;
  void printCuts() const;
  /// Get pointer to i'th cut
  OsiConicCut * cutPtr(int i);
  /// Get const pointer to i'th row cut
  OsiConicCut const * cutPtr(int i) const;
  /// Get i'th cut
  OsiConicCut & cut(int i);
  /// Get const reference to i'th cut
  OsiConicCut const & cut(int i) const;
  /// Get pointer to the most effective cut
  OsiConicCut * mostEffectiveCutPtr();
  /// Get const pointer to the most effective cut
  OsiConicCut const * mostEffectiveCutPtr() const;
  /// Remove i'th cut from collection
  void eraseCut(int i);
  /// Get pointer to i'th cut and remove ptr from collection
  OsiConicCut * cutPtrAndZap(int i);
  /*! \brief Clear all row cuts without deleting them

    Handy in case one wants to use CGL without managing cuts in one of
    the OSI containers. Client is ultimately responsible for deleting the
    data structures holding the row cuts.
  */
  void dumpCuts();
  void eraseAndDumpCuts(const std::vector<int> to_erase);
  void sort();
  /// Get iterator to beginning of collection
  iterator begin() { iterator it(*this); it.begin(); return it; }
  /// Get const iterator to beginning of collection
  const_iterator begin() const { const_iterator it(*this); it.begin(); return it; }
  /// Get iterator to end of collection
  iterator end() { iterator it(*this); it.end(); return it; }
  /// Get const iterator to end of collection
  const_iterator end() const { const_iterator it(*this); it.end(); return it; }

private:
  class OsiCutCompare {
  public:
    bool operator()(const OsiConicCut * c1P, const OsiConicCut * c2P) {
      return c1P->effectiveness() > c2P->effectiveness();
    }
  };
  OsiVectorConicCutPtr cutPtrs_;
};

#endif
