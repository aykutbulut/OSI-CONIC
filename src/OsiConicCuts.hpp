#ifndef OsiConicCuts_H
#define OsiConicCuts_H

#include <OsiCuts.hpp>
#include <OsiConicCut.hpp>

typedef std::vector<OsiConicCut *> OsiVectorConicCutPtr;

///
/// Holds Conic cuts. Col and linear row cuts are hold thru OsiCuts
/// interface.
///

class OsiConicCuts: public OsiCuts {
public:

private:
  OsiVectorConicCutPtr conicCutPtr_;
};

#endif
