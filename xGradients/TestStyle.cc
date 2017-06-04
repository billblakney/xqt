#include <QPainter>
#include <QPainterPath>
#include <QPolygon>
#include <QStyleOptionButton>
#include "TestStyle.hh"

TestStyle::TestStyle()
  : QCommonStyle()
{
}

TestStyle::~TestStyle()
{
}

void TestStyle::drawPrimitive(PrimitiveElement element,
    const QStyleOption *option,
    QPainter *painter,
    const QWidget *widget) const
{
  switch (element)
  {
  case PE_PanelButtonCommand:
  {
    painter->fillRect(option->rect, Qt::cyan);
#if 0
    int delta = (option->state & State_MouseOver) ? 64 : 0;
    QColor slightlyOpaqueBlack(0, 0, 0, 63);
    QColor semiTransparentWhite(255, 255, 255, 127 + delta);
    QColor semiTransparentBlack(0, 0, 0, 127 - delta);

    int x, y, width, height;
    option->rect.getRect(&x, &y, &width, &height);

//    QPainterPath roundRect = roundRectPath(option->rect);
    QPainterPath roundRect = option->rect;

    int radius = qMin(width, height) / 2;
    QBrush brush;
    bool darker;

    const QStyleOptionButton *buttonOption =
        qstyleoption_cast<const QStyleOptionButton *>(option);
    if (buttonOption
        && (buttonOption->features & QStyleOptionButton::Flat)) {
      brush = option->palette.background();
      darker = (option->state & (State_Sunken | State_On));
    } else {
      if (option->state & (State_Sunken | State_On)) {
        brush = option->palette.mid();
        darker = !(option->state & State_Sunken);
      } else {
        brush = option->palette.button();
        darker = false;
      }
    }
  painter->save();
#endif
#if 0
  painter->setRenderHint(QPainter::Antialiasing, true);
  painter->fillPath(roundRect, brush);
  if (darker)
    painter->fillPath(roundRect, slightlyOpaqueBlack);
  int penWidth;
  if (radius < 10)
    penWidth = 3;
  else if (radius < 20)
    penWidth = 5;
  else
    penWidth = 7;

  QPen topPen(semiTransparentWhite, penWidth);
  QPen bottomPen(semiTransparentBlack, penWidth);

  if (option->state & (State_Sunken | State_On))
    qSwap(topPen, bottomPen);
  int x1 = x;
  int x2 = x + radius;
  int x3 = x + width - radius;
  int x4 = x + width;

  if (option->direction == Qt::RightToLeft) {
    qSwap(x1, x4);
    qSwap(x2, x3);
  }

  QPolygon topHalf;
  topHalf << QPoint(x1, y)
     << QPoint(x4, y)
     << QPoint(x3, y + radius)
     << QPoint(x2, y + height - radius)
     << QPoint(x1, y + height);

  painter->setClipPath(roundRect);
  painter->setClipRegion(topHalf, Qt::IntersectClip);
  painter->setPen(topPen);
  painter->drawPath(roundRect);

  QPolygon bottomHalf = topHalf;
  bottomHalf[0] = QPoint(x4, y + height);

  painter->setClipPath(roundRect);
  painter->setClipRegion(bottomHalf, Qt::IntersectClip);
  painter->setPen(bottomPen);
  painter->drawPath(roundRect);

  painter->setPen(option->palette.foreground().color());
  painter->setClipping(false);
  painter->drawPath(roundRect);

  painter->restore();
#endif
  }
  break;
  default:
    QCommonStyle::drawPrimitive(element, option, painter, widget);
  }
}
