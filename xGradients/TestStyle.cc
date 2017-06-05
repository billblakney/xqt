#include <iostream>
#include <QString>
#include <QStringList>
#include <QPainter>
#include <QPainterPath>
#include <QPolygon>
#include <QStyleOptionButton>
#include <QStyleFactory>
#include "TestStyle.hh"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
TestStyle::TestStyle()
//  : QProxyStyle(QStyleFactory::create("windowsxp"))
  : QProxyStyle(QStyleFactory::create("fusion"))
{
#define SHOW_STYLES
#ifdef SHOW_STYLES
  QStringList tList = QStyleFactory::keys();
  for (int i = 0; i < tList.size(); i++ )
  {
    std::cout << tList[i].toStdString() << std::endl;
  }
  // on ubuntu: Windows, GTK+, Fusion
#endif
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
TestStyle::~TestStyle()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStyle::drawControl(ControlElement control, const QStyleOption *option,
    QPainter *painter, const QWidget *widget) const
{
  switch (control)
  {
  case CE_PushButton:
    std::cout << std::endl;
    std::cout << "drawControl CE_PushButton" << std::endl;
    // exiting at this point leaves nothing drawn
    break;
  case CE_PushButtonBevel:
    std::cout << "drawControl CE_PushButtonBevel" << std::endl;
//return;
    break;
  case CE_PushButtonLabel: // I think any custom drawing of label should be done here
// maybe useful note
//    subopt.rect = subElementRect(SE_PushButtonContents, btn, widget);
//    proxy()->drawControl(CE_PushButtonLabel, &subopt, p, widget);
// end maybe useful note
    std::cout << "drawControl CE_PushButtonLabel" << std::endl;
//return; // label will not be drawn
    break;
  default:
    {
    std::cout << "drawControl DEFAULT" << std::endl;
    break;
    }
  }

  QProxyStyle::drawControl(control, option, painter, widget);//TODO
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStyle::drawPrimitive(PrimitiveElement element,
    const QStyleOption *opt,
    QPainter *painter,
    const QWidget *widget) const
{
  switch (element)
  {
  case PE_FrameDefaultButton:
    {
    std::cout << "drawPrimitive PE_FrameDefaultButton" << std::endl;
    return;
    }
    break;
  case PE_FrameButtonBevel:
    std::cout << "drawPrimitive PE_FrameButtonBevel" << std::endl;
return;
    break;
//  case PE_PanelButtonCommand: // draw background here
//    std::cout << "drawPrimitive PE_PanelButtonCommand" << std::endl;
//QProxyStyle::drawPrimitive(element, option, painter, widget);
//return;
////    painter->fillRect(option->rect, Qt::cyan);
//    break;

  case PE_PanelButtonCommand: //drawing of button background HERE!!!
    {
//    QProxyStyle::drawPrimitive(element, opt, painter, widget);
    QBrush fill;
//fill = opt->palette.brush(QPalette::Mid);
//return;
    if (opt->state & State_Sunken) // press in progress
    {
std::cout << "drawPrimitive PE_PanelButtonCommand fillFor(SUNKEN)" << std::endl;
      fill = opt->palette.brush(QPalette::Mid);
    }
    else if ((opt->state & State_On) && (opt->state & State_Enabled)) // checked
    {
std::cout << "drawPrimitive PE_PanelButtonCommand fillFor(ON && ENABLED)" << std::endl;
//      fill = QBrush(opt->palette.mid().color(), Qt::Dense4Pattern);
      fill = QBrush(opt->palette.brush(QPalette::Highlight)/*, Qt::Dense4Pattern*/);
    }
    else // normal nothing going on
    {
std::cout << "drawPrimitive PE_PanelButtonCommand fillFor(--OTHER--)" << std::endl;
      fill = opt->palette.brush(QPalette::Button);
    }
    if ((opt->state & State_Enabled || opt->state & State_On) || !(opt->state & State_AutoRaise))
std::cout << "drawPrimitive PE_PanelButtonCommand shadingFor(ON || ENABLED and !autoraise)" << std::endl;
    {
//      qDrawShadePanel(p, opt->rect, opt->palette, bool(opt->state & (State_Sunken | State_On)),
//          proxy()->pixelMetric(PM_DefaultFrameWidth), &fill);
    }
//    painter->fillRect(opt->rect,Qt::cyan);
    painter->fillRect(opt->rect,fill);
    painter->setPen(QPen(Qt::black));
    QRect tRect = opt->rect;
    tRect.setWidth(tRect.width()-1);
    tRect.setHeight(tRect.height()-1);
    painter->drawRect(tRect);
//QProxyStyle::drawPrimitive(element, opt, painter, widget);
return;
    break;
    }
  case PE_PanelButtonBevel:
    {
//    QProxyStyle::drawPrimitive(element, opt, painter, widget);
    break;
    }
  case PE_PanelButtonTool:
    {
return;
    }

  case PE_FrameFocusRect:
    std::cout << "drawPrimitive PE_FrameFocusRect" << std::endl;
    break;
  default:
    std::cout << "drawPrimitive default" << std::endl;
  }
  QProxyStyle::drawPrimitive(element, opt, painter, widget);
}

#if 0
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
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
    QProxyStyle::drawPrimitive(element, option, painter, widget);
  }
}
#endif
