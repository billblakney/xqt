#include <cstdio>
#include <iostream>
#include <QString>
#include <QVBoxLayout>
#include <QGridLayout>
#include "MainWindow.hh"
#include "Square.hh"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *aParent)
: QWidget(aParent)
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::setupView()
{
  std::cout << "setupView" << std::endl;
  setMinimumSize(QSize(640,600));

  QFrame *tGrid[RANKS][FILES];

  QPalette tBlackPalette = palette();
//  tBlackPalette.setColor(QPalette::Background, Qt::black);
  tBlackPalette.setColor(QPalette::Background, QColor(90,90,90));
  tBlackPalette.setColor(QPalette::Foreground, Qt::white);
  QPalette tWhitePalette = palette();
  tWhitePalette.setColor(QPalette::Background, Qt::white);
  tWhitePalette.setColor(QPalette::Foreground, Qt::black);

  /*
   * Create the squares.
   */
  for (int i = 0; i < RANKS; i++)
    for (int j = 0; j < FILES; j++)
    {
      Square *tSquare = new Square(this,tWhitePalette,i,j,
          _FileNames[i] + _RankNames[j]);

      _Squares[i][j] = tSquare;
    }

  QGridLayout *tGridLayout = new QGridLayout(this);
  tGridLayout->setHorizontalSpacing(0);
  tGridLayout->setVerticalSpacing(0);
  tGridLayout->setContentsMargins(0,0,0,0);

  for (int i = 0; i < RANKS; i++)
    for (int j = 0; j < FILES; j++)
    {
      // frame shape/style
      QFrame *tFrame = new QFrame(this);
      tFrame->setFrameShape(QFrame::Box);
      tFrame->setLineWidth(20);
      tFrame->setFrameStyle(QFrame::Box | QFrame::Plain);

      // frame size
      tFrame->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

      tFrame->setMinimumSize(QSize(60,60));

      if (i == 0 && j == 0)
      {
        tFrame->setContentsMargins(2,2,2,2);
      }
      else if (i == 0)
      {
        tFrame->setContentsMargins(0,2,2,2);
      }
      else if (j == 0)
      {
        tFrame->setContentsMargins(2,0,2,2);
      }
      else
      {
        tFrame->setContentsMargins(0,0,2,2);
      }
#define SHOW_HIGHLIGHTED_MARGIN
#ifdef SHOW_HIGHLIGHTED_MARGIN
      if (i == 0 && j == 0)
      {
        tFrame->setPalette(QPalette(Qt::blue));
        tFrame->setContentsMargins(10,10,10,10);
        tFrame->setAutoFillBackground(true);
      }
#endif
      QVBoxLayout *tBL = new QVBoxLayout(tFrame);
      tBL->setContentsMargins(0,0,0,0);

      bool tUseWhitePerspective = true;
      if (tUseWhitePerspective)
      {
        tBL->addWidget(_Squares[j][FILES-1-i]);
      }
      else
      {
        tBL->addWidget(_Squares[RANKS-1-j][i]);
      }

      std::cout << "Adding to layout " << i << ", " << j <<std::endl;
      tGridLayout->addWidget(tFrame,i,j);
    }

  QWidget *tEditorsWidget = new QWidget(this);
  tEditorsWidget->setLayout(tGridLayout);

  QVBoxLayout *tBoxLayout = new QVBoxLayout(this);
  tBoxLayout->addWidget(tEditorsWidget);

  //  resize(200,120);

  setLayout(tBoxLayout);
}
