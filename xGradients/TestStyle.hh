#ifndef TestStyle_hh
#define TestStyle_hh

#ifdef QT_V5
#include <QProxyStyle>
#else
#include <QMotifStyle>
#endif
#include <QStyleOption>

#ifdef QT_V5
class TestStyle : public QProxyStyle
#else
class TestStyle : public QMotifStyle
#endif
{
  Q_OBJECT;

public:

  TestStyle();

  virtual ~TestStyle();

  void drawControl(ControlElement control, const QStyleOption *option,
      QPainter *painter, const QWidget *widget) const;

  void drawPrimitive(PrimitiveElement element,
      const QStyleOption *option,
      QPainter *painter,
      const QWidget *widget) const;

#if 0
  int pixelMetric(PixelMetric pm, const QStyleOption *opt,
                             const QWidget *widget) const;
#endif

  bool event(QEvent *e);
};

#endif /* TestStyle_hh */
