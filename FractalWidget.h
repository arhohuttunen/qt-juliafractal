#ifndef FRACTAL_WIDGET_H
#define FRACTAL_WIDGET_H

#include <QOpenGLWidget>

class QTimeLine;
class QAbstractAnimation;
class QParallelAnimationGroup;
class JuliaFractal;

class FractalWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    FractalWidget(QWidget *parent = 0);
    ~FractalWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private slots:
    void render(qreal time);

private:
    void startTimer();
    void startFractalAnimation();

    QAbstractAnimation * createZoomingAnimation();
    QAbstractAnimation * createSeedAnimation();
    QAbstractAnimation * createPanningAnimation();
    QAbstractAnimation * createRotatingAnimation();

    JuliaFractal *m_fractal;
    QTimeLine *m_timer;
    QParallelAnimationGroup *m_fractalAnimation;
};

#endif // FRACTAL_WIDGET_H
