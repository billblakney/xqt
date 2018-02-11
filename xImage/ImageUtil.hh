#ifndef IMAGEUTIL_HH_
#define IMAGEUTIL_HH_

#include <QColor>
#include <QImage>
#include <QPoint>

namespace imgu {

bool findColorAbove(QColor *aColor,QImage &aImage,int aX,int aY,
    int &aFoundAtY);
bool findColorBelow(QColor *aColor,QImage &aImage,int aX,int aY,
    int &aFoundAtY);
bool findColorLeft(QColor *aColor,QImage &aImage,int aX,int aY,
    int &aFoundAtX);
bool findColorRight(QColor *aColor,QImage &aImage,int aX,int aY,
    int &aFoundAtX);

void emphasizePoint(QImage &aImage,QPoint aPoint,QColor aColor,int aRadius =1);
void emphasizePoint(QImage &aImage,int aX,int aY,QColor aColor,int aRadius =1);

void eliminateIslands(QImage &aImage);

}

#endif /* IMAGEUTIL_HH_ */
