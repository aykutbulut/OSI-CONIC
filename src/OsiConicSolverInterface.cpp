
#include "OsiConicSolverInterface.hpp"
#include <CoinMpsIO.hpp>

int OsiConicSolverInterface::readMps(const char *filename, const char * extension) {
  CoinMpsIO m_MpsData;
  int nOfSOS;
  CoinSet ** SOS = NULL;
  int status = m_MpsData.readMps(filename, extension, nOfSOS, SOS );
  if (nOfSOS) {
    throw "Input file has SOS section!";
  }
  delete [] SOS;
  assert (!status);
  // load problem
  const CoinPackedMatrix * matrix = m_MpsData.getMatrixByCol();
  const double * collb = m_MpsData.getColLower();
  const double * colub = m_MpsData.getColUpper();
  const double * obj = m_MpsData.getObjCoefficients();
  const double * rowlb = m_MpsData.getRowLower();
  const double * rowub = m_MpsData.getRowUpper();
  loadProblem(*matrix, collb, colub, obj, rowlb, rowub);
  // set row and column names
  // todo(aykut) names are assumed to be less than 255 characters
  int name_len = 255;
  int numcols=m_MpsData.getNumCols();
  int numrows=m_MpsData.getNumRows();
  for (int i=0; i<numrows; ++i) {
    setRowName(i, m_MpsData.rowName(i));
  }
  for (int i=0; i<numcols; ++i) {
    setColName(i, m_MpsData.columnName(i));
  }
  // set variable types
  for (int i=0; i<numcols; ++i) {
    if (m_MpsData.isInteger(i)) {
      setInteger(i);
    }
  }
  // read conic part
  int nOfCones = 0;
  int * coneStart = NULL;
  int * coneIdx = NULL;
  int * coneType = NULL;
  status = m_MpsData.readConicMps(NULL, coneStart, coneIdx, coneType, nOfCones);
  // when there is no conic section status is -3.
  if (status==-3) {
    std::cout << "OsiConic: No conic section is mps file." << std::endl;
  }
  else {
    std::cerr << "OsiConic: readConicMps returned code " << status << std::endl;
    assert (!status);
  }
  int * members;
  for (int i=0; i<nOfCones; ++i) {
    if (coneType[i]!=1 and coneType[i]!=2) {
      throw "Invalid cone type!";
    }
    int num_members = coneStart[i+1]-coneStart[i];
    if (coneType[i]==2 and num_members<3) {
      throw "Rotated cones should have at least 3 members!";
    }
    // get members
    members = new int[num_members];
    int k=0;
    for (int j=coneStart[i]; j<coneStart[i+1]; ++j) {
      members[k] = coneIdx[j];
      k++;
    }
    OsiConeType type;
    if (coneType[i]==1) {
      type = OSI_QUAD;
    }
    else if (coneType[i]==2) {
      type = OSI_RQUAD;
    }
    addConicConstraint(type, num_members, members);
    delete[] members;
  }
  // check log level and print ccordingly
  if (nOfCones) {
    printf("Conic section has %d cones\n",nOfCones);
    for (int iCone=0;iCone<nOfCones;iCone++) {
      printf("Cone %d has %d entries (type %d) ",iCone,coneStart[iCone+1]-coneStart[iCone],
	     coneType[iCone]);
      for (int j=coneStart[iCone];j<coneStart[iCone+1];j++)
	printf("%d ",coneIdx[j]);
      printf("\n");
    }
  }
  delete [] coneStart;
  delete [] coneIdx;
  delete [] coneType;
  return 0;
}
