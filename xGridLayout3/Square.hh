#ifndef SQUARE_HH_
#define SQUARE_HH_

#include <QLabel>
#include <QPalette>
#include <QString>

class Square: public QLabel
{
  Q_OBJECT
public:

  int _Row;
  int _Col;

  Square(QWidget *aParent,QPalette aPalette,int aRow,int aCol,
      QString aText);
  ~Square();
  QLabel *getLabel();

public slots:

  void onClick();

protected:

  QPalette _Palette;
  QLabel _Label;
  QString _Text;

  virtual void mouseReleaseEvent(QMouseEvent * ev);
};

#endif /* SQUARE_HH_ */
