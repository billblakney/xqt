#ifndef IMAGEUTIL_HH_
#define IMAGEUTIL_HH_

#include <QColor>
#include <QImage>
#include <QPoint>

namespace imgu {

void emphasizePoint(QImage &aImage,QPoint aPoint,QColor aColor,int aRadius =1);
void emphasizePoint(QImage &aImage,int aX,int aY,QColor aColor,int aRadius =1);

}

#endif /* IMAGEUTIL_HH_ */
