#ifndef TestStyle_hh
#define TestStyle_hh

#include <QCommonStyle>
#include <QStyleOption>

class TestStyle : public QCommonStyle
{
  Q_OBJECT;

public:
  TestStyle();
  virtual ~TestStyle();
void drawPrimitive(PrimitiveElement element,
    const QStyleOption *option,
    QPainter *painter,
    const QWidget *widget) const;
};

#endif /* TestStyle_hh */
