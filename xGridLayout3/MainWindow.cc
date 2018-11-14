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
void MainWindow::onFlipBoardToggled(bool aChecked)
{
  if (aChecked)
  {
    std::cout << "Using BLACK perspective" << std::endl;
    _FlipBoardToggle->setText("Perspective: BLACK");
    _Board->setPerspective(Board::eBlack);
_Board->showSquareColors(true);
  }
  else
  {
    std::cout << "Using white perspective" << std::endl;
    _FlipBoardToggle->setText("Perspective: WHITE");
    _Board->setPerspective(Board::eWhite);
_Board->showSquareColors(false);
  }
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

  tBoxLayout->addWidget(_FlipBoardToggle);

  /*
   * Configure the find label.
   */
  _FindLabel =
      new QLabel("<square_to_find>",this);
  tBoxLayout->addWidget(_FindLabel);

  /*
   * Configure the board.
   */
  _Board = new Board(this);

#ifdef OLD
  QWidget *tEditorsWidget = new QWidget(this);
  tEditorsWidget->setLayout(tGridLayout);

  tBoxLayout->addWidget(tEditorsWidget);
#endif

  tBoxLayout->addWidget(_Board);

  //  resize(200,120);

  setLayout(tBoxLayout);

  //TODO move?
  QObject::connect(_FlipBoardToggle, SIGNAL(toggled(bool)),
      this, SLOT(onFlipBoardToggled(bool)) );
}
