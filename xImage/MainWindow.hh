#ifndef MAINWINDOW_HH_
#define MAINWINDOW_HH_

#include <string>
//#include <QCheckBox>
#include <QLabel>
//#include <QLineEdit>
//#include <QPushButton>
#include <QWidget>
#include <QSlider>

class MainWindow: public QWidget
{
  Q_OBJECT
public:

  MainWindow(QWidget *aParent);

  virtual ~MainWindow();

	void setupView();
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

  void updateCopyImage(int aValue);
  void loadOriginalImage();

  QImage *_OriginalImage;
  QImage *_CopyImage;
  QPixmap *_OriginalPixmap;
  QPixmap *_CopyPixmap;
  QSlider *_Slider;
  QLabel *_Label2;
};

#endif /* MAINWINDOW_HH_ */
