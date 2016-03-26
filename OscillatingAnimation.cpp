#include <QPropertyAnimation>
#include "OscillatingAnimation.h"

OscillatingAnimation::OscillatingAnimation(QObject* target, const QByteArray& propertyName,
                                           QEasingCurve easingCurve, QObject* parent)
    : QSequentialAnimationGroup(parent)
{
    firstHalf = new QPropertyAnimation(target, propertyName);
    firstHalf->setEasingCurve(easingCurve);

    secondHalf = new QPropertyAnimation(target, propertyName);
    secondHalf->setEasingCurve(easingCurve);

    addAnimation(firstHalf);
    addAnimation(secondHalf);
}

void OscillatingAnimation::setDuration(int msecs)
{
    firstHalf->setDuration(msecs/2);
    secondHalf->setDuration(msecs/2);
}

void OscillatingAnimation::setStartValue(const QVariant& value)
{
    firstHalf->setStartValue(value);
    secondHalf->setEndValue(value);
}

void OscillatingAnimation::setEndValue(const QVariant &value)
{
    firstHalf->setEndValue(value);
    secondHalf->setStartValue(value);
}
