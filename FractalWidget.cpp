#include <QTimeLine>
#include <QAbstractAnimation>
#include <QParallelAnimationGroup>
#include "FractalWidget.h"
#include "JuliaFractal.h"
#include "OscillatingAnimation.h"

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
    m_fractalAnimation->start();
}

QAbstractAnimation * FractalWidget::createZoomingAnimation()
{
    OscillatingAnimation *zoomAnimation = new OscillatingAnimation(m_fractal, "zoom", QEasingCurve::InOutQuart);
    zoomAnimation->setDuration(40000);
    zoomAnimation->setStartValue(0.02f);
    zoomAnimation->setEndValue(4.1f);
    zoomAnimation->setLoopCount(-1);

    return zoomAnimation;
}

QAbstractAnimation * FractalWidget::createSeedAnimation()
{
    OscillatingAnimation *seedAnimation = new OscillatingAnimation(m_fractal, "seed", QEasingCurve::InOutSine);
    seedAnimation->setDuration(20000);
    seedAnimation->setStartValue(QVector2D(0.40, 0.15));
    seedAnimation->setEndValue(QVector2D(0.37, 0.27));
    seedAnimation->setLoopCount(-1);

    return seedAnimation;
}

QAbstractAnimation * FractalWidget::createPanningAnimation()
{
    OscillatingAnimation *panAnimation = new OscillatingAnimation(m_fractal, "pan", QEasingCurve::InOutSine);
    panAnimation->setDuration(20000);
    panAnimation->setStartValue(QVector2D(0.333, 0.447));
    panAnimation->setEndValue(QVector2D(0.0, -0.447));
    panAnimation->setLoopCount(-1);

    return panAnimation;
}

void FractalWidget::render(qreal /*time*/)
{
    update();
}
