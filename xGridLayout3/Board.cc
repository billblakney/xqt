#include <iostream>
#include <QGridLayout>
#include "Board.hh"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Board::Board(QWidget *aParent)
: QWidget(aParent),
  _Perspective(eWhite)
{
  _LastClickedSquare = Square::Coord(-1,-1);
  setup();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Board::~Board()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Board::setPerspective(Perspective aPerspective)
{
  _Perspective = aPerspective;
  loadPerspective();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Board::setup()
{
  /*
   * Configure palettes.
   */
  configurePalettes();

  /*
   * Create the squares.
   */
  for (int tFile = 0; tFile < FILES; tFile++)
    for (int tRank = 0; tRank < RANKS; tRank++)
    {
      Square *tSquare = new Square(this,_WhitePalette,tFile,tRank,
          _FileNames[tFile] + _RankNames[tRank]);

      QObject::connect(tSquare, SIGNAL(squareClicked(int,int,bool)),
          this, SLOT(onSquareClick(int,int,bool)) );

      _Squares[tFile][tRank] = tSquare;
    }

  /*
   * Create the grid that holds the squares.
   */
  QGridLayout *tGridLayout = new QGridLayout(this);
  tGridLayout->setHorizontalSpacing(0);
  tGridLayout->setVerticalSpacing(0);
  tGridLayout->setContentsMargins(0,0,0,0);

  for (int tRow = 0; tRow < ROWS; tRow++)
    for (int tCol = 0; tCol < COLS; tCol++)
    {
      // frame shape/style
      QFrame *tFrame = new QFrame(this);
      tFrame->setFrameShape(QFrame::Box);
      tFrame->setLineWidth(20);
      tFrame->setFrameStyle(QFrame::Box | QFrame::Plain);

      // frame size
      tFrame->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

      tFrame->setMinimumSize(QSize(60,60));

      if (tRow == 0 && tCol == 0)
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

  highlightFrame(GridCoord(0,0));

  loadPerspective();

  setLayout(tGridLayout);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Board::onSquareClick(int aFile,int aRank,bool aIsLeft)
{
  Q_UNUSED(aIsLeft);
  std::cout << "click on " << aFile << "," << aRank << std::endl;
  highlightFrame(mapSquareToGrid(Square::Coord(aFile,aRank)));
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool Board::isLightSquare(Square::Coord aSquare)
{
  if ((aSquare.rank + aSquare.file)%2 != 0)
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
void Board::showSquareColors(bool aShow)
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
        Square::Coord tSquareCoord(i,j);
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
void Board::loadPerspective()
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
void Board::loadWhitePerspective()
{
  std::cout << "loading white perspective" << std::endl;
  for (int tRow = 0; tRow < ROWS; tRow++)
    for (int tCol = 0; tCol < COLS; tCol++)
    {
      GridCoord tGridCoord(tRow,tCol);
      Square::Coord tSquareCoord = mapGridToSquare(tGridCoord);
      _SquareHolders[tRow][tCol]->addWidget(
          _Squares[tSquareCoord.file][tSquareCoord.rank]);
    }
}

//-----------------------------------------------------------------------------
//TODO coords
//-----------------------------------------------------------------------------
void Board::loadBlackPerspective()
{
  std::cout << "loading black perspective" << std::endl;
  for (int tRow = 0; tRow < ROWS; tRow++)
    for (int tCol = 0; tCol < COLS; tCol++)
    {
      GridCoord tGridCoord(tRow,tCol);
      Square::Coord tSquareCoord = mapGridToSquare(tGridCoord);
      _SquareHolders[tRow][tCol]->addWidget(
          _Squares[tSquareCoord.file][tSquareCoord.rank]);
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Board::highlightFrame(GridCoord aGridCoord)
{
  std::cout << "highlighting frame with grid coords "
     << aGridCoord._Row << "," << aGridCoord._Col << std::endl;
  QFrame *tFrame =
      (QFrame*)_SquareHolders[aGridCoord._Row][aGridCoord._Col]->parent();

  tFrame->setPalette(QPalette(Qt::blue));
  tFrame->setContentsMargins(5,5,5,5);
  tFrame->setAutoFillBackground(true);
}

//-----------------------------------------------------------------------------
// Notes for mapSquareToGrid and mapGridToSquare:
// For white, row inverts rank, col equals file.
// For black, row equals rank, col inverts file.
//-----------------------------------------------------------------------------
GridCoord Board::mapSquareToGrid(Square::Coord aSquareCoord)
{
  GridCoord tGridCoord;
  if (_Perspective == eWhite)
  {
    tGridCoord._Row = RANKS-1-aSquareCoord.rank;
    tGridCoord._Col = aSquareCoord.file;
    std::cout << "White perspective: "
        << "square(" << aSquareCoord.rank << "," << aSquareCoord.file << ") "
        << "maps to "
        << "grid(" << tGridCoord._Row << "," << tGridCoord._Col << ");" << std::endl;
  }
  else
  {
    tGridCoord._Row = aSquareCoord.rank;
    tGridCoord._Col = FILES-1-aSquareCoord.file;
  }
  return tGridCoord;
}

//-----------------------------------------------------------------------------
// Notes for mapSquareToGrid and mapGridToSquare:
// For white, row inverts rank, col equals file.
// For black, row equals rank, col inverts file.
//-----------------------------------------------------------------------------
Square::Coord Board::mapGridToSquare(GridCoord aGridCoord)
{
  Square::Coord tSquareCoord;
  if (_Perspective == eWhite)
  {
    tSquareCoord.rank = ROWS-1-aGridCoord._Row;
    tSquareCoord.file = aGridCoord._Col;
  }
  else
  {
    tSquareCoord.rank = aGridCoord._Row;
    tSquareCoord.file = COLS-1-aGridCoord._Col;
  }
  return tSquareCoord;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Board::configurePalettes()
{
  _BlackPalette = palette();
  //  _BlackPalette.setColor(QPalette::Background, Qt::black);
  _BlackPalette.setColor(QPalette::Background, QColor(90,90,90));
  _BlackPalette.setColor(QPalette::Foreground, Qt::white);
  _WhitePalette = palette();
  _WhitePalette.setColor(QPalette::Background, Qt::white);
  _WhitePalette.setColor(QPalette::Foreground, Qt::black);
}
