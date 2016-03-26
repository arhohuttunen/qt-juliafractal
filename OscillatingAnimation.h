#ifndef OSCILLATING_ANIMATION_H
#define OSCILLATING_ANIMATION_H

#include <QSequentialAnimationGroup>
#include <QEasingCurve>
#include <QVariant>

class QPropertyAnimation;

class OscillatingAnimation : public QSequentialAnimationGroup
{
public:
    OscillatingAnimation(QObject* target, const QByteArray& propertyName,
                         QEasingCurve easingCurve, QObject* parent = 0);

    void setDuration(int msecs);
    void setStartValue(const QVariant& value);
    void setEndValue(const QVariant& value);

protected:
    QPropertyAnimation *firstHalf;
    QPropertyAnimation *secondHalf;
};

#endif // OSCILLATING_ANIMATION_H
