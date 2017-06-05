#include <iostream>
#include <QApplication>
#include <QWindowsStyle>
#include "MainWindow.hh"
#include "TestStyle.hh"

using namespace std;

int main(int argc, char *argv[])
{
  QApplication::setStyle(new QMotifStyle);
//  QApplication::setStyle(new QWindowsStyle);
//  QApplication::setStyle(new TestStyle);
  QApplication app(argc, argv);

  //layout.resize(200,120);

  std::cout << "creating MainWindow" << std::endl;
  MainWindow *window = new MainWindow(0);
  window->setupView();
  window->setVisible(true);
  //     window->setGeometry(1920      ,135,500,900);
  window->show();

  return app.exec();
}
