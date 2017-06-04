#ifndef TestStyle_hh
#define TestStyle_hh

#include <QProxyStyle>
#include <QStyleOption>

class TestStyle : public QProxyStyle
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
};

#endif /* TestStyle_hh */
