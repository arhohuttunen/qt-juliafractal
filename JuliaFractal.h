#ifndef JULIA_FRACTAL_H
#define JULIA_FRACTAL_H

#include <QObject>
#include <QVector>
#include <QVector2D>

class QGLShader;
class QGLShaderProgram;

class JuliaFractal : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float aspect READ aspect WRITE setAspect)
    Q_PROPERTY(float zoom READ zoom WRITE setZoom)
    Q_PROPERTY(QVector2D pan READ pan WRITE setPan)
    Q_PROPERTY(QVector2D seed READ seed WRITE setSeed)

public:
    JuliaFractal(QObject *parent = 0);
    ~JuliaFractal();

    float aspect() const;
    float zoom() const;
    QVector2D pan() const;
    QVector2D seed() const;

    void setAspect(float aspect);
    void setZoom(float zoom);
    void setPan(const QVector2D &pan);
    void setSeed(const QVector2D &seed);

    void render();

private:
    QVector<QVector3D> m_vertices;
    QVector<QVector2D> m_texCoords;
    float m_aspect;
    float m_zoom;
    QVector2D m_pan;
    QVector2D m_seed;
    QGLShaderProgram *m_program;

    void setupGeometry();
    void setupShader();

    QMatrix4x4 createOrthogonalMatrix();

    QGLShader * createVertexShader();
    QGLShader * createFragmentShader();
    QGLShaderProgram * createShaderProgram(QGLShader *fshader, QGLShader *vshader);
};

#endif // JULIA_FRACTAL_H
