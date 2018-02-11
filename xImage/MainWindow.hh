#ifndef MAINWINDOW_HH_
#define MAINWINDOW_HH_

#include <string>
//#include <QCheckBox>
#include <QLabel>
//#include <QLineEdit>
//#include <QPushButton>
#include <QWidget>
#include <QSlider>
#include <QPixmap>
#include <QImage>
//#include "Board.hh"
#include "Square.hh"

class Board;

class MainWindow: public QWidget
{
  Q_OBJECT
public:

//  enum Direction {eLeft, eRight, eUp, eDown};

  MainWindow(QWidget *aParent);

  virtual ~MainWindow();

	void setupView(std::string aFilename);
  void setupConnections();

public slots:

  void onSliderValueChanged(int aValue);
//  void onSend();

protected:

//  QCheckBox *_checkBox;
//  QLabel *_label1;
//  QLabel *_label2;
//  QLineEdit *_lineEdit1;
//  QLineEdit *_lineEdit2;
//  QPushButton *_startButton;
  QSlider *_Slider;
  QLabel *_Label2;

  Board *_Board;
  void loadImage(std::string aFilename);

#if 0
  void normalizeColors(QImage &aImage);
  void normalizeSquareBorderColor(QImage &aImage,Square &aSquare);
  void eliminateIslands(QImage &aImage);
  QPoint getSquareCenter(QSize aBoardSize,int aRow,int aCol);
  QPoint getNeighborSquareCenter(QRect aFromSquare,int aRowOffset,int aColOffset);
  QRect getSquareAt(QImage &aImage,QPoint aSeed);
  void addSquareAt(int aRow,int aCol,QImage &aImage,QPoint aCenter);
  void generateSimilarRowSquares(QImage &aImage,int aSeedRow,int aSeedCol,int aOffset,int aNumSquares);
  QColor *getPieceColor(QImage &aImage,QRect aSquare,QColor *aSquareColor);
  void contrastPiece(QImage &aImage,QRect aSquare,Board::BoardElement aSquareType);
  void removeImageSpeckles();
  int colorDiff(QColor *aColor1,QColor *aColor2);
  QColor *getNormalizedColor(QColor &aColor);

  bool findColorAbove(QColor *aColor,
      QImage &aImage,int aX,int aY,int &aFoundAtY);
  bool findColorBelow(QColor *aColor,
      QImage &aImage,int aX,int aY,int &aFoundAtY);
  bool findColorLeft(QColor *aColor,
      QImage &aImage,int aX,int aY,int &aFoundAtX);
  bool findColorRight(QColor *aColor,
      QImage &aImage,int aX,int aY,int &aFoundAtX);

  void emphasizePoint(QImage &aImage,QPoint aPoint,QColor aColor,int aRadius = 1);
  void emphasizePoint(QImage &aImage,int aX,int aY,QColor aColor,int aRadius = 1);
#endif
};

#endif /* MAINWINDOW_HH_ */
