#ifndef BOARD_HH_
#define BOARD_HH_

class Board
{
public:

  enum BoardElement {eNone, eDarkSquare, eLiteSquare, eDarkPiece, eLitePiece};

  static const int ROWS = 8;
  static const int COLS = 8;

  Board();

  virtual ~Board();
};

#endif /* BOARD_HH_ */
