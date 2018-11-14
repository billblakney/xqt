#ifndef SQUARECOORD_HH_
#define SQUARECOORD_HH_

class SquareCoord {
public:
  int _File;
  int _Rank;
  SquareCoord();
  SquareCoord(int aFile,int aRank);
  virtual ~SquareCoord();
};

#endif /* SQUARECOORD_HH_ */
