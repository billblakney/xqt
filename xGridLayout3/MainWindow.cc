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
  _LastClickedRank = 1;
  _LastClickedFile = 1;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::onFlipBoardToggled(bool aChecked)
{
  if (aChecked)
  {
    std::cout << "Using BLACK perspective" << std::endl;
    _FlipBoardToggle->setText("Perspective: BLACK");
    loadBlackPerspective();
  }
  else
  {
    std::cout << "Using white perspective" << std::endl;
    _FlipBoardToggle->setText("Perspective: WHITE");
    loadWhitePerspective();
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::loadWhitePerspective()
{
  for (int i = 0; i < RANKS; i++)
  {
    for (int j = 0; j < FILES; j++)
    {
      _SquareHolders[i][j]->addWidget(_Squares[j][FILES-1-i]);
    }
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::loadBlackPerspective()
{
  for (int i = 0; i < RANKS; i++)
  {
    for (int j = 0; j < FILES; j++)
    {
      _SquareHolders[i][j]->addWidget(_Squares[RANKS-1-j][i]);
    }
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::highlightFrame(int aRow, int aCol)
{
  QFrame *tFrame = (QFrame*)_SquareHolders[aRow][aCol]->parent();
  tFrame->setPalette(QPalette(Qt::blue));
  tFrame->setContentsMargins(10,10,10,10);
  tFrame->setAutoFillBackground(true);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::onSquareClick(int aRank,int aFile,bool aIsLeft)
{
  std::cout << "click on " << aRank << "," << aFile << std::endl;
  highlightFrame(aRank,aFile);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
MainWindow::Coord MainWindow::mapSquareToGrid(Coord aSquareCoord)
{
  Coord tGridCoord;
  return tGridCoord;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
MainWindow::Coord MainWindow::mapGridToSquare(Coord aGridCoord)
{
  Coord tGridCoord;
  return tGridCoord;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::setupView()
{
  std::cout << "setupView" << std::endl;
  setMinimumSize(QSize(640,600));

  QVBoxLayout *tBoxLayout = new QVBoxLayout(this);

  _FlipBoardToggle =
      new QPushButton("Perspective: WHITE",this);
  _FlipBoardToggle->setCheckable(true);

  QObject::connect(_FlipBoardToggle, SIGNAL(toggled(bool)),
      this, SLOT(onFlipBoardToggled(bool)) );

  tBoxLayout->addWidget(_FlipBoardToggle);

  _FindLabel =
      new QLabel("<square_to_find>",this);
  tBoxLayout->addWidget(_FindLabel);

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

      QObject::connect(tSquare, SIGNAL(squareClicked(int,int,bool)),
          this, SLOT(onSquareClick(int,int,bool)) );

      _Squares[i][j] = tSquare;
    }

  QGridLayout *tGridLayout = new QGridLayout(this);
  tGridLayout->setHorizontalSpacing(0);
  tGridLayout->setVerticalSpacing(0);
  tGridLayout->setContentsMargins(0,0,0,0);

  for (int i = 0; i < RANKS; i++)
  {
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

      QVBoxLayout *tBL = new QVBoxLayout(tFrame);
      tBL->setContentsMargins(0,0,0,0);

      _SquareHolders[i][j] = tBL;

      tGridLayout->addWidget(tFrame,i,j);
    }
  }

  highlightFrame(0,0);

  loadWhitePerspective();

  QWidget *tEditorsWidget = new QWidget(this);
  tEditorsWidget->setLayout(tGridLayout);

  tBoxLayout->addWidget(tEditorsWidget);

  //  resize(200,120);

  setLayout(tBoxLayout);
}
