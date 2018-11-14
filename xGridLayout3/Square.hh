#ifndef SQUARE_HH_
#define SQUARE_HH_

#include <QLabel>
#include <QPalette>
#include <QString>

class Square: public QLabel
{
  Q_OBJECT
public:

  class Coord
  {
  public:
    int file;
    int rank;

    Coord();
    Coord(int aFile,int aRank);
    virtual ~Coord();
    bool isValid();
  };

  Square(QWidget *aParent,QPalette aPalette,int aFile,int aRank,
      QString aText);
  ~Square();
  void setPalette(QPalette aPalette);
  Coord getCoord();
  int getFile();
  int getRank();

signals:
	void squareClicked(int aFile,int aRank,bool aIsLeft);

public slots:

  void onClick();

protected:

  Coord _Coord;
  QPalette _Palette;
  QLabel _Label;
  QString _Text;

  virtual void mouseReleaseEvent(QMouseEvent * ev);
};

#endif /* SQUARE_HH_ */
