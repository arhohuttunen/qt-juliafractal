#include <QTimeLine>
#include <QAbstractAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QMatrix2x2>
#include <QMatrix4x4>
#include <math.h>
#include "FractalWidget.h"
#include "JuliaFractal.h"

FractalWidget::FractalWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

FractalWidget::~FractalWidget()
{
}

void FractalWidget::initializeGL()
{
    m_fractal = new JuliaFractal;

    startFractalAnimation();

    startTimer();
}

void FractalWidget::paintGL()
{
    m_fractal->render();
}

void FractalWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    m_fractal->setAspect((float)h/(float)w);
}

void FractalWidget::startTimer()
{
    m_timer = new QTimeLine(1000, this);
    m_timer->setEasingCurve(QEasingCurve::Linear);
    m_timer->setFrameRange(0, 60);
    m_timer->setLoopCount(0);
    connect(m_timer, SIGNAL(valueChanged(qreal)), this, SLOT(render(qreal)));
    m_timer->start();
}

void FractalWidget::startFractalAnimation()
{
    m_fractalAnimation = new QParallelAnimationGroup;
    m_fractalAnimation->addAnimation(createZoomingAnimation());
    m_fractalAnimation->addAnimation(createSeedAnimation());
    m_fractalAnimation->addAnimation(createPanningAnimation());
    m_fractalAnimation->addAnimation(createRotatingAnimation());
    m_fractalAnimation->start();
}

QAbstractAnimation * FractalWidget::createZoomingAnimation()
{
    QSequentialAnimationGroup *zoomAnimation = new QSequentialAnimationGroup(this);

    QPropertyAnimation *first = new QPropertyAnimation(m_fractal, "zoom");
    first->setEasingCurve(QEasingCurve::InOutSine);
    first->setStartValue(3.0f);
    first->setEndValue(3.5f);
    first->setDuration(10000);
    zoomAnimation->addAnimation(first);

    QPropertyAnimation *second = new QPropertyAnimation(m_fractal, "zoom");
    second->setEasingCurve(QEasingCurve::InOutSine);
    second->setStartValue(3.5f);
    second->setEndValue(3.0f);
    second->setDuration(10000);
    zoomAnimation->addAnimation(second);

    QPropertyAnimation *third = new QPropertyAnimation(m_fractal, "zoom");
    third->setEasingCurve(QEasingCurve::InOutCubic);
    third->setStartValue(3.0f);
    third->setEndValue(0.1f);
    third->setDuration(10000);
    zoomAnimation->addAnimation(third);

    QPropertyAnimation *fourth = new QPropertyAnimation(m_fractal, "zoom");
    fourth->setEasingCurve(QEasingCurve::InOutCubic);
    fourth->setStartValue(0.1f);
    fourth->setEndValue(3.0f);
    fourth->setDuration(10000);
    zoomAnimation->addAnimation(fourth);

    zoomAnimation->setLoopCount(-1);

    return zoomAnimation;
}

QAbstractAnimation * FractalWidget::createSeedAnimation()
{
    QSequentialAnimationGroup *seedAnimation = new QSequentialAnimationGroup(this);

    QPropertyAnimation *first = new QPropertyAnimation(m_fractal, "seed");
    first->setEasingCurve(QEasingCurve::InOutCirc);
    first->setStartValue(QVector2D(0.242578, 0.555));
    first->setEndValue(QVector2D(0.385938, 0.1));
    first->setDuration(10000);
    seedAnimation->addAnimation(first);

    QPropertyAnimation *second = new QPropertyAnimation(m_fractal, "seed");
    second->setEasingCurve(QEasingCurve::InOutSine);
    second->setStartValue(QVector2D(0.385938, 0.1));
    second->setEndValue(QVector2D(0.386719, 0.36375));
    second->setDuration(10000);
    seedAnimation->addAnimation(second);

    QPropertyAnimation *third = new QPropertyAnimation(m_fractal, "seed");
    third->setEasingCurve(QEasingCurve::InOutBack);
    third->setStartValue(QVector2D(0.386719, 0.36375));
    third->setEndValue(QVector2D(0.0945313, 0.61625));
    third->setDuration(10000);
    seedAnimation->addAnimation(third);

    QPropertyAnimation *fourth = new QPropertyAnimation(m_fractal, "seed");
    fourth->setEasingCurve(QEasingCurve::InOutSine);
    fourth->setStartValue(QVector2D(0.0945313, 0.61625));
    fourth->setEndValue(QVector2D(0.242578, 0.555));
    fourth->setDuration(10000);
    seedAnimation->addAnimation(fourth);

    seedAnimation->setLoopCount(-1);

    return seedAnimation;
}

QAbstractAnimation * FractalWidget::createPanningAnimation()
{
    QSequentialAnimationGroup *panAnimation = new QSequentialAnimationGroup(this);

    QPropertyAnimation *first = new QPropertyAnimation(m_fractal, "pan");
    first->setEasingCurve(QEasingCurve::InOutSine);
    first->setStartValue(QVector2D(0.0, 0.0));
    first->setEndValue(QVector2D(-0.1, -0.05));
    first->setDuration(20000);
    panAnimation->addAnimation(first);

    QPropertyAnimation *second = new QPropertyAnimation(m_fractal, "pan");
    second->setEasingCurve(QEasingCurve::InOutSine);
    second->setStartValue(QVector2D(-0.1, -0.05));
    second->setEndValue(QVector2D(-0.3, 0.38));
    second->setDuration(10000);
    panAnimation->addAnimation(second);

    QPropertyAnimation *third = new QPropertyAnimation(m_fractal, "pan");
    third->setEasingCurve(QEasingCurve::InOutSine);
    third->setStartValue(QVector2D(-0.3, 0.38));
    third->setEndValue(QVector2D(0.0, 0.0));
    third->setDuration(10000);
    panAnimation->addAnimation(third);

    panAnimation->setLoopCount(-1);

    return panAnimation;
}

QAbstractAnimation * FractalWidget::createRotatingAnimation()
{
    QSequentialAnimationGroup *animation = new QSequentialAnimationGroup(this);

    QPropertyAnimation *first = new QPropertyAnimation(m_fractal, "angle");
    first->setEasingCurve(QEasingCurve::InOutBack);
    first->setStartValue(M_PI * 1.5);
    first->setEndValue(M_PI);
    first->setDuration(10000);
    animation->addAnimation(first);

    QPropertyAnimation *second = new QPropertyAnimation(m_fractal, "angle");
    second->setEasingCurve(QEasingCurve::InOutBack);
    second->setStartValue(M_PI);
    second->setEndValue(0.0);
    second->setDuration(10000);
    animation->addAnimation(second);

    QPropertyAnimation *third = new QPropertyAnimation(m_fractal, "angle");
    third->setEasingCurve(QEasingCurve::InOutBack);
    third->setStartValue(0.0);
    third->setEndValue(M_PI * 0.5);
    third->setDuration(10000);
    animation->addAnimation(third);

    QPropertyAnimation *fourth = new QPropertyAnimation(m_fractal, "angle");
    fourth->setEasingCurve(QEasingCurve::InOutBack);
    fourth->setStartValue(M_PI * 0.5);
    fourth->setEndValue(M_PI * 1.5);
    fourth->setDuration(10000);
    animation->addAnimation(fourth);

    animation->setLoopCount(-1);

    return animation;
}

void FractalWidget::render(qreal /*time*/)
{
    update();
}
