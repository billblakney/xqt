#include <iostream>
#include <QApplication>
#ifdef QT_V5
#include <QStyleFactory>
#else
#include <QWindowsStyle>
#include <QMotifStyle>
#endif
#include "MainWindow.hh"
#include "TestStyle.hh"

using namespace std;

int main(int argc, char *argv[])
{
#ifndef QT_V5
  QApplication::setStyle(new QMotifStyle);
//  QApplication::setStyle(new QWindowsStyle);
#else
  QApplication::setStyle(QStyleFactory::create("motif"));
//  QApplication::setStyle(QStyleFactory::create("windows"));
#endif
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
