#ifndef SQUARE_HH_
#define SQUARE_HH_

#include <string>
#include <QFrame>
#include <QLabel>
#include <QPalette>
#include <QWidget>

class Square: public QFrame
{
  Q_OBJECT
public:

  int _Row;
  int _Col;

  Square(QWidget *aParent,QPalette aPalette,int aRow,int aCol,
      std::string aLabel);
  ~Square();

public slots:

  void onClick();

protected:

  QPalette _Palette;
  QLabel _Label;
  std::string _LabelText;

};

#endif /* SQUARE_HH_ */
