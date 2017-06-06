#include <iostream>
#include <QString>
#include <QStringList>
#include <QPainter>
#include <QPainterPath>
#include <QPolygon>
#include <QStyleOptionButton>
#ifdef QT_V5
#include <QStyleFactory>
#include <qdrawutil.h>
#else
#include <QMotifStyle>
#endif

#include <QEvent>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QFocusFrame>

#include "TestStyle.hh"

//#define INVALIDATE_TEST_STYLE

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
TestStyle::TestStyle()
#ifdef QT_V5
  : QProxyStyle(QStyleFactory::create("fusion"))
#else
  : QMotifStyle()
#endif
{
#ifdef QT_V5
#define SHOW_STYLES
  // ubuntu: Windows, GTK+, Fusion
  // work: Windows, Motif, CDE, Plastique, GTK+, Cleanlooks
#ifdef SHOW_STYLES
  QStringList tList = QStyleFactory::keys();
  for (int i = 0; i < tList.size(); i++ )
  {
    std::cout << tList[i].toStdString() << std::endl;
  }
#endif
#endif
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
TestStyle::~TestStyle()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStyle::drawControl(ControlElement control, const QStyleOption *opt,
    QPainter *p, const QWidget *widget) const
{
#ifdef INVALIDATE_TEST_STYLE
#ifdef QT_V5
    QProxyStyle::drawControl(control, opt, p, widget);
#else
    QMotifStyle::drawControl(control, opt, p, widget);
#endif
  return;
#endif

  bool tUseDefaultDraw = true;

  switch (control)
  {
  case CE_PushButton:
    std::cout << std::endl;
    // exiting at this point leaves nothing drawn
//#define USE_MOTIFSTYLE_CE_PUSHBUTTON
#ifdef USE_MOTIFSTYLE_CE_PUSHBUTTON
std::cout << "MOTIFSYTLE drawControl CE_PushButton" << std::endl;
        if (const QStyleOptionButton *btn = qstyleoption_cast<const QStyleOptionButton *>(opt)) {
            proxy()->drawControl(CE_PushButtonBevel, btn, p, widget);
            QStyleOptionButton subopt = *btn;
            subopt.rect = subElementRect(SE_PushButtonContents, btn, widget);
            proxy()->drawControl(CE_PushButtonLabel, &subopt, p, widget);
            if (btn->state & State_HasFocus) {
                QStyleOptionFocusRect fropt;
                fropt.QStyleOption::operator=(*btn);
                fropt.rect = subElementRect(SE_PushButtonFocusRect, btn, widget);
                proxy()->drawPrimitive(PE_FrameFocusRect, &fropt, p, widget);
            }
        }
        tUseDefaultDraw = false; // @added
        break;
#else
    std::cout << "Custom drawControl CE_PushButton" << std::endl;
    break;
#endif
  case CE_PushButtonBevel:
//#define USE_MOTIFSTYLE_CE_PUSHBUTTONBEVEL
#define USE_MODIFIED_MOTIFSTYLE_CE_PUSHBUTTONBEVEL
#ifdef USE_MOTIFSTYLE_CE_PUSHBUTTONBEVEL
    std::cout << "drawControl MotifStyle CE_PushButtonBevel" << std::endl;
        if (const QStyleOptionButton *btn = qstyleoption_cast<const QStyleOptionButton *>(opt)) {
            int diw, x1, y1, x2, y2;
            p->setPen(opt->palette.foreground().color());
            p->setBrush(QBrush(opt->palette.button().color(), Qt::NoBrush));
            diw = proxy()->pixelMetric(PM_ButtonDefaultIndicator);
            opt->rect.getCoords(&x1, &y1, &x2, &y2);
            if (btn->features & (QStyleOptionButton::AutoDefaultButton|QStyleOptionButton::DefaultButton)) {
                x1 += diw;
                y1 += diw;
                x2 -= diw;
                y2 -= diw;
            }
            if (btn->features & QStyleOptionButton::DefaultButton) {
                if (diw == 0) {
                    QPolygon a;
                    a.setPoints(9,
                                x1, y1, x2, y1, x2, y2, x1, y2, x1, y1+1,
                                x2-1, y1+1, x2-1, y2-1, x1+1, y2-1, x1+1, y1+1);
                    p->setPen(opt->palette.shadow().color());
                    p->drawPolygon(a);
                    x1 += 2;
                    y1 += 2;
                    x2 -= 2;
                    y2 -= 2;
                } else {
                    qDrawShadePanel(p, opt->rect.adjusted(1, 1, -1, -1), opt->palette, true);
                }
            }
            if (!(btn->features & QStyleOptionButton::Flat) ||
                (btn->state & (State_Sunken | State_On))) {
                QStyleOptionButton newOpt = *btn;
                newOpt.rect = QRect(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
                p->setBrushOrigin(p->brushOrigin());
                proxy()->drawPrimitive(PE_PanelButtonCommand, &newOpt, p, widget);
            }
            if (btn->features & QStyleOptionButton::HasMenu) {
                int mbi = proxy()->pixelMetric(PM_MenuButtonIndicator, btn, widget);
                QRect ir = btn->rect;
                QStyleOptionButton newBtn = *btn;
                newBtn.rect = QRect(ir.right() - mbi - 3, ir.y() + 4,  mbi, ir.height() - 8);
                proxy()->drawPrimitive(PE_IndicatorArrowDown, &newBtn, p, widget);
            }
tUseDefaultDraw = false;
            break;
        }
#elif defined USE_MODIFIED_MOTIFSTYLE_CE_PUSHBUTTONBEVEL
    std::cout << "drawControl Modified MotifStyle CE_PushButtonBevel" << std::endl;
        if (const QStyleOptionButton *btn = qstyleoption_cast<const QStyleOptionButton *>(opt)) {
            int diw, x1, y1, x2, y2;
            p->setPen(opt->palette.foreground().color());
            p->setBrush(QBrush(opt->palette.button().color(), Qt::NoBrush));
            diw = proxy()->pixelMetric(PM_ButtonDefaultIndicator);
            opt->rect.getCoords(&x1, &y1, &x2, &y2);
            if (btn->features & (QStyleOptionButton::AutoDefaultButton|QStyleOptionButton::DefaultButton)) {
std::cout << "%%% bbb is auto default or default" << std::endl;
                x1 += diw;
                y1 += diw;
                x2 -= diw;
                y2 -= diw;
            }
            if (btn->features & QStyleOptionButton::DefaultButton) {
                if (diw == 0) {
std::cout << "%%% bbb is default and diw is 0" << std::endl;
                    QPolygon a;
                    a.setPoints(9,
                                x1, y1, x2, y1, x2, y2, x1, y2, x1, y1+1,
                                x2-1, y1+1, x2-1, y2-1, x1+1, y2-1, x1+1, y1+1);
                    p->setPen(opt->palette.shadow().color());
                    p->drawPolygon(a);
                    x1 += 2;
                    y1 += 2;
                    x2 -= 2;
                    y2 -= 2;
                } else {
std::cout << "%%% bbb is default and diw != 0" << std::endl;
                    qDrawShadePanel(p, opt->rect.adjusted(1, 1, -1, -1), opt->palette, true);
                }
            }
            if (!(btn->features & QStyleOptionButton::Flat) ||
                (btn->state & (State_Sunken | State_On))) {
std::cout << "%%% bbb not flat and is sunken or on" << std::endl;
                QStyleOptionButton newOpt = *btn;
                newOpt.rect = QRect(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
                p->setBrushOrigin(p->brushOrigin());
                proxy()->drawPrimitive(PE_PanelButtonCommand, &newOpt, p, widget);
            }
            if (btn->features & QStyleOptionButton::HasMenu) {
std::cout << "%%% bbb has menu" << std::endl;
                int mbi = proxy()->pixelMetric(PM_MenuButtonIndicator, btn, widget);
                QRect ir = btn->rect;
                QStyleOptionButton newBtn = *btn;
                newBtn.rect = QRect(ir.right() - mbi - 3, ir.y() + 4,  mbi, ir.height() - 8);
                proxy()->drawPrimitive(PE_IndicatorArrowDown, &newBtn, p, widget);
            }
tUseDefaultDraw = false;
            break;
        }
#else
#endif
    std::cout << "drawControl CE_PushButtonBevel" << std::endl;
    break;
  case CE_PushButtonLabel: // I think any custom drawing of label should be done here
    std::cout << "drawControl CE_PushButtonLabel" << std::endl;
// maybe useful note
//    subopt.rect = subElementRect(SE_PushButtonContents, btn, widget);
//    proxy()->drawControl(CE_PushButtonLabel, &subopt, p, widget);
// end maybe useful note
//return; // label will not be drawn
    break;
  default:
    {
    break;
    }
  }
  if (tUseDefaultDraw == true)
  {
    std::cout << "drawControl DEFAULT" << std::endl;
#ifdef QT_V5
    QProxyStyle::drawControl(control, opt, p, widget);
#else
    QMotifStyle::drawControl(control, opt, p, widget);
#endif
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStyle::drawPrimitive(PrimitiveElement element,
    const QStyleOption *opt,
    QPainter *painter,
    const QWidget *widget) const
{
#ifdef INVALIDATE_TEST_STYLE
#ifdef QT_V5
  QProxyStyle::drawPrimitive(element, opt, painter, widget);
#else
  QMotifStyle::drawPrimitive(element, opt, painter, widget);
#endif
  return;
#endif

  bool tUseDefaultDraw = true;

  switch (element)
  {
  case PE_FrameDefaultButton:
    std::cout << "drawPrimitive PE_FrameDefaultButton" << std::endl;
    break;
  case PE_FrameButtonBevel:
    std::cout << "drawPrimitive PE_FrameButtonBevel" << std::endl;
    break;

  case PE_PanelButtonCommand: //drawing of button background HERE!!!
//#define USE_MOTIFSTYLE_PE_PANEL_BUTTON_COMMAND
#define USE_MODIFIED_MOTIFSTYLE_PE_PANEL_BUTTON_COMMAND
#ifdef USE_MOTIFSTYLE_PE_PANEL_BUTTON_COMMAND
    {
std::cout << "drawPrimitive MotifStyle PE_PanelButtonCommand" << std::endl;
        QBrush fill;
        if (opt->state & State_Sunken)
            fill = opt->palette.brush(QPalette::Mid);
        else if ((opt->state & State_On) && (opt->state & State_Enabled))
            fill = QBrush(opt->palette.mid().color(), Qt::Dense4Pattern);
        else
            fill = opt->palette.brush(QPalette::Button);
         if ((opt->state & State_Enabled || opt->state & State_On) || !(opt->state & State_AutoRaise))
             qDrawShadePanel(p, opt->rect, opt->palette, bool(opt->state & (State_Sunken | State_On)),
                             proxy()->pixelMetric(PM_DefaultFrameWidth), &fill);
        break;
    }
#elif defined USE_MODIFIED_MOTIFSTYLE_PE_PANEL_BUTTON_COMMAND
    {
std::cout << "drawPrimitive MODIFIED MotifStyle PE_PanelButtonCommand" << std::endl;
    QBrush fill;
    if (opt->state & State_Sunken) // press in progress
    {
std::cout << "drawPrimitive PE_PanelButtonCommand fillFor(SUNKEN)" << std::endl;
      fill = opt->palette.brush(QPalette::Mid);
    }
    else if ((opt->state & State_On) && (opt->state & State_Enabled)) // checked
    {
std::cout << "drawPrimitive PE_PanelButtonCommand fillFor(ON && ENABLED)" << std::endl;
//#define CUSTOMIZE_CHECKED_FILL
#ifdef CUSTOMIZE_CHECKED_FILL
//      fill = QBrush(opt->palette.brush(QPalette::Highlight)/*, Qt::Dense4Pattern*/);
//      fill = QBrush(opt->palette.brush(QPalette::Highlight)/*, Qt::Dense4Pattern*/);
//      fill = QBrush(opt->palette.brush(QPalette::Mid));
      fill = opt->palette.brush(QPalette::Mid);
#else
      fill = QBrush(opt->palette.mid().color(), Qt::Dense4Pattern);
#endif
    }
    else // normal nothing going on
    {
std::cout << "drawPrimitive PE_PanelButtonCommand fillFor(--OTHER--)" << std::endl;
      fill = opt->palette.brush(QPalette::Button);
    }
    if ((opt->state & State_Enabled || opt->state & State_On) || !(opt->state & State_AutoRaise))
std::cout << "drawPrimitive PE_PanelButtonCommand shadingFor(ON || ENABLED and !autoraise)" << std::endl;
    {
      qDrawShadePanel(painter, opt->rect, opt->palette, bool(opt->state & (State_Sunken | State_On)),
#define CUSTOMIZE_NO_BEVEL
#ifdef CUSTOMIZE_NO_BEVEL
          0, &fill);
#else
          proxy()->pixelMetric(PM_DefaultFrameWidth), &fill);
#endif
    }
#if 1 // a my custom
//    painter->fillRect(opt->rect,Qt::cyan);
//    painter->fillRect(opt->rect,fill);
    painter->setPen(QPen(Qt::white));
    painter->setPen(QPen(Qt::yellow));
    painter->setPen(QPen(QColor(0x527596)));
    QRect tRect = opt->rect;
    tRect.setWidth(tRect.width()-1);
    tRect.setHeight(tRect.height()-1);
    painter->drawRect(tRect);
#endif

//QProxyStyle::drawPrimitive(element, opt, painter, widget);
//return;
    tUseDefaultDraw = false;
    break;
    }
#else
  std::cout << "drawPrimitive PE_PanelButtonCommand" << std::endl;
  break;
#endif
  case PE_PanelButtonBevel:
    {
    std::cout << "drawPrimitive PE_PanelButtonCommand" << std::endl;
    break;
    }
  case PE_PanelButtonTool:
    {
    std::cout << "drawPrimitive PE_PanelButtonTool" << std::endl;
#ifdef CUSTOMIZE
return;
#endif
    }
  case PE_FrameFocusRect:
    std::cout << "drawPrimitive PE_FrameFocusRect" << std::endl;
    break;
  case PE_FrameButtonTool: //not relevant, but using to test something
    return;
    break;
  case PE_FrameWindow:
    return;
    break;
  default:
    std::cout << "drawPrimitive default" << std::endl;
  }

  if (tUseDefaultDraw == true)
  {
    std::cout << "drawPrimitive DEFAULT" << std::endl;
#ifdef QT_V5
  QProxyStyle::drawPrimitive(element, opt, painter, widget);
#else
  QMotifStyle::drawPrimitive(element, opt, painter, widget);
#endif
  }
}

#if 0
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int TestStyle::pixelMetric(PixelMetric pm, const QStyleOption *opt,
                             const QWidget *widget) const
{
  int tReturn = QMotifStyle::pixelMetric(pm,opt,widget);
std::cout << "bbb pixelMetric" << std::endl;

  if (const QStyleOptionButton *btn = qstyleoption_cast<const QStyleOptionButton *>(opt))
  {
std::cout << "bbb pixelMetric is button" << std::endl;
    if (pm == PM_DefaultFrameWidth)
    {
std::cout << "bbb pixelMetric is default frame width" << std::endl;
      tReturn = 0;
    }
//  if ((const QStyleOptionButton *btn = qstyleoption_cast<const QStyleOptionButton *>(opt)))
//      && pm == QStyle::PM_DefaultFrameWidth)
//  {
//    std::cout << "returning PM_DefaultFrameWidth of 0" << std::endl;
  }
std::cout << "bbb pixelMetric returning " << tReturn << std::endl;
    return tReturn;
}
#endif

//-----------------------------------------------------------------------------
// Handles events. In the MotifStyle implementation, it puts a frame around
// the widget with focus. In this custom implementation, we leave off that
// focus frame.
//-----------------------------------------------------------------------------
bool TestStyle::event(QEvent *e)
{
//#define USE_MOTIFSTYLE_EVENT
#ifdef USE_MOTIFSTYLE_EVENT
    if(e->type() == QEvent::FocusIn) {
        if (QWidget *focusWidget = QApplication::focusWidget()) {
#ifndef QT_NO_GRAPHICSVIEW
            if (QGraphicsView *graphicsView = qobject_cast<QGraphicsView *>(focusWidget)) {
                QGraphicsItem *focusItem = graphicsView->scene() ? graphicsView->scene()->focusItem() : 0;
                if (focusItem && focusItem->type() == QGraphicsProxyWidget::Type) {
                    QGraphicsProxyWidget *proxy = static_cast<QGraphicsProxyWidget *>(focusItem);
                    if (proxy->widget())
                        focusWidget = proxy->widget()->focusWidget();
                }
            }
#endif
            if(!focus)
                focus = new QFocusFrame(focusWidget);
            focus->setWidget(focusWidget);
        } else {
            if(focus)
                focus->setWidget(0);
        }
    } else if(e->type() == QEvent::FocusOut) {
        if(focus)
            focus->setWidget(0);
    }
    return  QCommonStyle::event(e);
#else
  return true;
#endif
}

