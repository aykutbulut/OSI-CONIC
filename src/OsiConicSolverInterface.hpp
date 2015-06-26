/**
For now it reads problem in mps format.
Manipulating/building functions will be supported later.


 **/


#ifndef OsiConicSolverInterface_H
#define OsiConicSolverInterface_H

// OSI headers
#include <OsiSolverInterface.hpp>

class OsiConicCuts;

typedef enum {
  OSI_LORENTZ=0,
  OSI_SCALED
} OsiConeType;

typedef enum {
  OSI_QUAD=0,
  OSI_RQUAD
} OsiLorentzConeType;

class OsiConicSolverInterface: virtual public OsiSolverInterface {
public:
  // void read(const char * data_file);
  // get conic constraints
  virtual void getConicConstraint(int index, OsiLorentzConeType & type,
				  int & numMembers,
				  int *& members) const = 0;
  // add conic constraints
  // add conic constraint in lorentz cone form
  virtual void addConicConstraint(OsiLorentzConeType type,
				  int numMembers,
				  const int * members) = 0;
  // add conic constraint in |Ax-b| <= dx-h form
  virtual void addConicConstraint(CoinPackedMatrix const * A, CoinPackedVector const * b,
				  CoinPackedVector const * d, double h) = 0;
  virtual void removeConicConstraint(int index) = 0;
  virtual void modifyConicConstraint(int index, OsiLorentzConeType type,
				     int numMembers,
				     const int * members) = 0;
  virtual int getNumCones() const = 0;
  virtual int getConeSize(int i) const = 0;
  virtual OsiConeType getConeType(int i) const = 0;
  virtual void getConeSize(int * size) const = 0;
  virtual void getConeType(OsiConeType * type) const = 0;
  virtual void getConeType(OsiLorentzConeType * type) const = 0;
  virtual OsiConicSolverInterface * clone(bool copyData = true) const = 0;
  virtual void writeMps (const char *filename, const char *extension="mps",
			 double objSense=0.0) const = 0;
  virtual ~OsiConicSolverInterface() {};
  virtual int readMps(const char * filename, const char * extension="mps");
  // un-hide OsiSolverInterfaces applyCuts function
  // todo(aykut): It is usefull for what? Explain
  // using OsiSolverInterface::applyCuts;
  // virtual OsiSolverInterface::ApplyCutsReturnCode applyCuts (
  // 	const OsiCuts & cs,
  //       double effectivenessLb=0.0);
  // overloads applyCuts for linear cuts with conic cut argument
  // for applying row cuts we use methods inherited from OsiSolverInterface
  using OsiSolverInterface::applyCuts;
  virtual OsiSolverInterface::ApplyCutsReturnCode applyCuts (
   	const OsiConicCuts & cs,
	double effectivenessLb=0.0);
};

#endif
