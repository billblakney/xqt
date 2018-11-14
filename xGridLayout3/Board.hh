#ifndef BOARD_HH
#define BOARD_HH

#include <QWidget>

class Board: public QWidget
{
  Q_OBJECT
public:
  Board(QWidget *aParent);
  virtual ~Board();
  void setup();
};

#endif //BOARD_HH
