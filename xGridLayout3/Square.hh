#ifndef SQUARE_HH_
#define SQUARE_HH_

#include <QLabel>
#include <QPalette>
#include <QString>

class Square: public QLabel
{
  Q_OBJECT
public:

  int _File;
  int _Rank;

  Square(QWidget *aParent,QPalette aPalette,int aFile,int aRank,
      QString aText);
  ~Square();
  void setPalette(QPalette aPalette);

signals:
	void squareClicked(int aFile,int aRank,bool aIsLeft);

public slots:

  void onClick();

protected:

  QPalette _Palette;
  QLabel _Label;
  QString _Text;

  virtual void mouseReleaseEvent(QMouseEvent * ev);
};

#endif /* SQUARE_HH_ */
