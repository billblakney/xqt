#ifndef TestStyle_hh
#define TestStyle_hh

#ifdef QT_V4
#include <QMotifStyle>
#else
#include <QProxyStyle>
#endif
#include <QStyleOption>

#ifdef QT_V4
class TestStyle : public QMotifStyle
#else
class TestStyle : public QProxyStyle
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
