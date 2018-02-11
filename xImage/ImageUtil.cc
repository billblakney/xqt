#include "ImageUtil.hh"

namespace imgu {

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void emphasizePoint(QImage &aImage,QPoint aPoint,QColor aColor,int aRadius)
{
  emphasizePoint(aImage,aPoint.x(),aPoint.y(),aColor,aRadius);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void emphasizePoint(QImage &aImage,int aX,int aY,QColor aColor,int aRadius)
{
  QRgb tRgb = aColor.rgb();
  aImage.setPixel(aX,aY,tRgb);

  int tStartX = aX - aRadius;
  tStartX = std::max(tStartX,0);

  int tEndX = aX + aRadius;
  tEndX = std::min(tEndX,aImage.width()-1);

  int tStartY = aY - aRadius;
  tStartY = std::max(tStartY,0);

  int tEndY = aY + aRadius;
  tEndY = std::min(tEndY,aImage.height()-1);

  for (int i = tStartX; i <= tEndX; i++)
    for (int j = tStartY; j <= tEndY; j++)
    {
      aImage.setPixel(i,j,tRgb);
    }
}

}



