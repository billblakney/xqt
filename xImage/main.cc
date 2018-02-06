#include <iostream>
#include <QApplication>
#include "MainWindow.hh"

using namespace std;

 int main(int argc, char *argv[])
 {
     QApplication app(argc, argv);

     //layout.resize(200,120);

     std::cout << "creating MainWindow" << std::endl;
     MainWindow *window = new MainWindow(0);
     window->setupView(argv[1]);
     window->setupConnections();
     window->setVisible(true);
//     window->setGeometry(1920      ,135,500,900);
     window->show();

     return app.exec();
 }
