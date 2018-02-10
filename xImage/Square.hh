#ifndef SQUARE_HH_
#define SQUARE_HH_

#include <string>
#include <QRect>

class Square {
public:
  Square();
  Square(int aRow,int aCol,QRect aRect);
  virtual ~Square();
  Square &operator=(const Square &aSquare);
  std::string toString();
  float getWeight();

  int _Row;
  int _Col;
  QRect _Rect;

  int _PiecePixels;
  int _PieceDist[8][8];

private:
  void init();
};

#endif /* SQUARE_HH_ */
