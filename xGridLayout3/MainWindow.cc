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
: QWidget(aParent),
  _Perspective(eWhite)
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
    _Perspective = eBlack;
    _FlipBoardToggle->setText("Perspective: BLACK");
    loadPerspective();
showSquareColors(true);
  }
  else
  {
    std::cout << "Using white perspective" << std::endl;
    _Perspective = eWhite;
    _FlipBoardToggle->setText("Perspective: WHITE");
    loadPerspective();
showSquareColors(false);
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::onSquareClick(int aFile,int aRank,bool aIsLeft)
{
  Q_UNUSED(aIsLeft);
  std::cout << "click on " << aFile << "," << aRank << std::endl;
  highlightFrame(mapSquareToGrid(SquareCoord(aFile,aRank)));
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool MainWindow::isLightSquare(SquareCoord aSquare)
{
  if ((aSquare._Rank + aSquare._File)%2 != 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::showSquareColors(bool aShow)
{
  for (int i = 0; i < RANKS; i++)
  {
    for (int j = 0; j < FILES; j++)
    {
      if (aShow == false)
      {
        _Squares[i][j]->setPalette(_WhitePalette);
      }
      else
      {
        SquareCoord tSquareCoord(i,j);
        if (isLightSquare(tSquareCoord))
        {
          _Squares[i][j]->setPalette(_WhitePalette);
        }
        else
        {
          _Squares[i][j]->setPalette(_BlackPalette);
        }
      }
    }
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::loadPerspective()
{
  if (_Perspective == eWhite)
  {
    loadWhitePerspective();
  }
  else // eBlack
  {
    loadBlackPerspective();
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::loadWhitePerspective()
{
  std::cout << "loading white perspective" << std::endl;
  for (int tX = 0; tX < COLS; tX++)
  {
    for (int tY = 0; tY < ROWS; tY++)
    {
      GridCoord tGridCoord(tX,tY);
      SquareCoord tSquareCoord = mapGridToSquare(tGridCoord);
      _SquareHolders[tX][tY]->addWidget(
          _Squares[tSquareCoord._File][tSquareCoord._Rank]);
    }
  }
}

//-----------------------------------------------------------------------------
//TODO coords
//-----------------------------------------------------------------------------
void MainWindow::loadBlackPerspective()
{
  std::cout << "loading black perspective" << std::endl;
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
void MainWindow::highlightFrame(GridCoord aGridCoord)
{
  std::cout << "highlighting frame with grid coords "
     << aGridCoord._x << "," << aGridCoord._y << std::endl;
  QFrame *tFrame =
      (QFrame*)_SquareHolders[aGridCoord._x][aGridCoord._y]->parent();
  tFrame->setPalette(QPalette(Qt::blue));
  tFrame->setContentsMargins(5,5,5,5);
  tFrame->setAutoFillBackground(true);
}

//-----------------------------------------------------------------------------
// Notes for mapSquareToGrid and mapGridToSquare:
// For white, x equals file, y inverts rank.
// For black, y equals rank, x inverts file.
//-----------------------------------------------------------------------------
GridCoord MainWindow::mapSquareToGrid(SquareCoord aSquareCoord)
{
  GridCoord tGridCoord;
  if (_Perspective == eBlack)
  {
    tGridCoord._x = aSquareCoord._File;
    tGridCoord._y = RANKS-1-aSquareCoord._Rank;
    std::cout << "White perspective: "
        << "square(" << aSquareCoord._Rank << "," << aSquareCoord._File << ") "
        << "maps to "
        << "grid(" << tGridCoord._x << "," << tGridCoord._y << ");" << std::endl;
  }
  else
  {
    tGridCoord._x = FILES-1-aSquareCoord._File;
    tGridCoord._y = aSquareCoord._Rank;
  }
  return tGridCoord;
}

//-----------------------------------------------------------------------------
// Notes for mapSquareToGrid and mapGridToSquare:
// For white, x equals file, y inverts rank.
// For black, y equals rank, x inverts file.
//-----------------------------------------------------------------------------
SquareCoord MainWindow::mapGridToSquare(GridCoord aGridCoord)
{
  SquareCoord tSquareCoord;
  if (_Perspective == eBlack)
  {
    tSquareCoord._File = aGridCoord._x;
    tSquareCoord._Rank = RANKS-1-aGridCoord._y;
  }
  else
  {
    tSquareCoord._Rank = aGridCoord._y;
    tSquareCoord._File = FILES-1-aGridCoord._x;
  }
  return tSquareCoord;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::configurePalettes()
{
  _BlackPalette = palette();
  //  _BlackPalette.setColor(QPalette::Background, Qt::black);
  _BlackPalette.setColor(QPalette::Background, QColor(90,90,90));
  _BlackPalette.setColor(QPalette::Foreground, Qt::white);
  _WhitePalette = palette();
  _WhitePalette.setColor(QPalette::Background, Qt::white);
  _WhitePalette.setColor(QPalette::Foreground, Qt::black);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::setupView()
{
  std::cout << "setupView" << std::endl;
  setMinimumSize(QSize(640,600));

  // Overall layout.
  QVBoxLayout *tBoxLayout = new QVBoxLayout(this);

  /*
   * Configure the flip board toggle.
   */
  _FlipBoardToggle =
      new QPushButton("Perspective: WHITE",this);
  _FlipBoardToggle->setCheckable(true);

  QObject::connect(_FlipBoardToggle, SIGNAL(toggled(bool)),
      this, SLOT(onFlipBoardToggled(bool)) );

  tBoxLayout->addWidget(_FlipBoardToggle);

  /*
   * Configure the find label.
   */
  _FindLabel =
      new QLabel("<square_to_find>",this);
  tBoxLayout->addWidget(_FindLabel);

  /*
   * Configure palettes.
   */
  configurePalettes();

  /*
   * Create the squares.
   */
  for (int tFileIdx = 0; tFileIdx < FILES; tFileIdx++)
    for (int tRankIdx = 0; tRankIdx < RANKS; tRankIdx++)
    {
      Square *tSquare = new Square(this,_WhitePalette,tFileIdx,tRankIdx,
          _FileNames[tFileIdx] + _RankNames[tRankIdx]);

      QObject::connect(tSquare, SIGNAL(squareClicked(int,int,bool)),
          this, SLOT(onSquareClick(int,int,bool)) );

      _Squares[tFileIdx][tRankIdx] = tSquare;
    }

  /*
   * Create the grid that holds the squares.
   */
  QGridLayout *tGridLayout = new QGridLayout(this);
  tGridLayout->setHorizontalSpacing(0);
  tGridLayout->setVerticalSpacing(0);
  tGridLayout->setContentsMargins(0,0,0,0);

  for (int tCol = 0; tCol < COLS; tCol++)
  {
    for (int tRow = 0; tRow < ROWS; tRow++)
    {
      // frame shape/style
      QFrame *tFrame = new QFrame(this);
      tFrame->setFrameShape(QFrame::Box);
      tFrame->setLineWidth(20);
      tFrame->setFrameStyle(QFrame::Box | QFrame::Plain);

      // frame size
      tFrame->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

      tFrame->setMinimumSize(QSize(60,60));

      if (tCol == 0 && tRow == 0)
      {
        tFrame->setContentsMargins(2,2,2,2);
      }
      else if (tRow == 0)
      {
        tFrame->setContentsMargins(0,2,2,2);
      }
      else if (tCol == 0)
      {
        tFrame->setContentsMargins(2,0,2,2);
      }
      else
      {
        tFrame->setContentsMargins(0,0,2,2);
      }

      QVBoxLayout *tBL = new QVBoxLayout(tFrame);
      tBL->setContentsMargins(0,0,0,0);

      _SquareHolders[tRow][tCol] = tBL;

      tGridLayout->addWidget(tFrame,tRow,tCol);
    }
  }

  highlightFrame(GridCoord(0,0));

  loadPerspective();

  QWidget *tEditorsWidget = new QWidget(this);
  tEditorsWidget->setLayout(tGridLayout);

  tBoxLayout->addWidget(tEditorsWidget);

  //  resize(200,120);

  setLayout(tBoxLayout);
}
