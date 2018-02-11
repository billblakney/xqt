#include <iostream>
#include "ImageUtil.hh"

namespace imgu {

//-----------------------------------------------------------------------------
// Finds the first square color along the YAxis from specified start point.
//-----------------------------------------------------------------------------
bool findColorAbove(QColor *aColor,QImage &aImage,int aX,int aY,
    int &aFoundAtY)
{
  aFoundAtY = aY;

  while (aFoundAtY >= 0)
  {
    QColor tColor = QColor(aImage.pixel(aX,aFoundAtY));

    if (tColor == *aColor)
    {
      return true;
    }
    aFoundAtY--;
  }

  return false;
}

//-----------------------------------------------------------------------------
// Finds the first square color along the YAxis from specified start point.
//-----------------------------------------------------------------------------
bool findColorBelow(QColor *aColor,QImage &aImage,int aX,int aY,
    int &aFoundAtY)
{
  aFoundAtY = aY;

  while (aFoundAtY <= aImage.height()-1)
  {
    QColor tColor = QColor(aImage.pixel(aX,aFoundAtY));

    if (tColor == *aColor)
    {
      return true;
    }
    aFoundAtY++;
  }

  return false;
}

//-----------------------------------------------------------------------------
// Finds the first square color along the XAxis from specified start point.
//-----------------------------------------------------------------------------
bool findColorLeft(QColor *aColor,QImage &aImage,int aX,int aY,
    int &aFoundAtX)
{
  aFoundAtX = aX;

  while (aFoundAtX >= 0)
  {
    QColor tColor = QColor(aImage.pixel(aFoundAtX,aY));
    if (tColor == *aColor)
    {
      return true;
    }
    aFoundAtX--;
  }

  return false;
}

//-----------------------------------------------------------------------------
// Finds the first square color along the XAxis from specified start point.
//-----------------------------------------------------------------------------
bool findColorRight(QColor *aColor,QImage &aImage,int aX,int aY,
    int &aFoundAtX)
{
  aFoundAtX = aX;

  while (aFoundAtX <= aImage.width()-1)
  {
    QColor tColor = QColor(aImage.pixel(aFoundAtX,aY));
    if (tColor == *aColor)
    {
      return true;
    }
    aFoundAtX++;
  }

  return false;
}

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

//-----------------------------------------------------------------------------
// Sets the color of pixel islands to the surrounding color.
// Note: Doesn't bother with the edge pixels.
//-----------------------------------------------------------------------------
void eliminateIslands(QImage &aImage)
{
  QSize tSize = aImage.size();

  int tNumIslands = 0;

  for (int i = 1; i < tSize.width()-1; i++)
    for (int j = 1; j < tSize.height()-1; j++)
    {
      QRgb tRgb = aImage.pixel(i,j);

      QRgb tLeftRgb = aImage.pixel(i-1,j);
      QRgb tRightRgb = aImage.pixel(i+1,j);
      QRgb tAboveRgb = aImage.pixel(i,j-1);
      QRgb tBelowRgb = aImage.pixel(i,j+1);

      if ((tRgb != tLeftRgb)
       && (tRgb != tRightRgb)
       && (tRgb != tAboveRgb)
       && (tRgb != tBelowRgb)
       && (tLeftRgb == tRightRgb)
       && (tLeftRgb == tAboveRgb)
       && (tLeftRgb == tBelowRgb))
      {
        std::cout << "Found island pixel at " << i << "," << j << std::endl;
        tNumIslands++;
        aImage.setPixel(i,j,tLeftRgb);
      }
    }

  std::cout << "Number of island pixel removed: " << tNumIslands << std::endl;
}

}



