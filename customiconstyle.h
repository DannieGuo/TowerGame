#ifndef CUSTOMICONSTYLE_H
#define CUSTOMICONSTYLE_H

#include <QCommonStyle>

class CustomIconStyle : public QCommonStyle
{
 Q_OBJECT

public:
 CustomIconStyle();
 ~CustomIconStyle();

 void SetCustomSize(int);

 //protected:
 virtual int pixelMetric(PixelMetric metric, const QStyleOption * option, const QWidget * widget) const;

private:
 int mSize;
};

#endif // CUSTOMICONSTYLE_H
