#include <QGLShaderProgram>
#include "JuliaFractal.h"

JuliaFractal::JuliaFractal(QObject *parent)
    : QObject(parent)
{
    setupGeometry();
    setupShader();
}

JuliaFractal::~JuliaFractal()
{
}

float JuliaFractal::aspect() const
{
    return m_aspect;
}

float JuliaFractal::zoom() const
{
    return m_zoom;
}

QVector2D JuliaFractal::pan() const
{
    return m_pan;
}

QVector2D JuliaFractal::seed() const
{
    return m_seed;
}

void JuliaFractal::setAspect(float aspect)
{
    m_aspect = aspect;
}

void JuliaFractal::setZoom(float zoom)
{
    m_zoom = zoom;
}

void JuliaFractal::setPan(const QVector2D &pan)
{
    m_pan = pan;
}

void JuliaFractal::setSeed(const QVector2D &seed)
{
    m_seed = seed;
}

void JuliaFractal::render()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 m = createOrthogonalMatrix();

    m_program->bind();
    m_program->setUniformValue("matrix", m);
    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);
    m_program->setAttributeArray(0, m_vertices.constData());
    m_program->setAttributeArray(1, m_texCoords.constData());
    m_program->setUniformValue("aspect", m_aspect);
    m_program->setUniformValue("zoom", m_zoom);
    m_program->setUniformValue("pan", m_pan);
    m_program->setUniformValue("seed", m_seed);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

QMatrix4x4 JuliaFractal::createOrthogonalMatrix()
{
    QMatrix4x4 m;
    m.ortho(-1.0f, 1.0f, 1.0f, -1.0f, 0.1f, 10.0f);
    m.translate(0.0f, 0.0f, -1.0f);

    return m;
}

void JuliaFractal::setupGeometry()
{
    m_vertices.append(QVector3D(-1, -1, 0));
    m_vertices.append(QVector3D( 1, -1, 0));
    m_vertices.append(QVector3D( 1,  1, 0));
    m_vertices.append(QVector3D(-1,  1, 0));

    m_texCoords.append(QVector2D(0, 1));
    m_texCoords.append(QVector2D(1, 1));
    m_texCoords.append(QVector2D(1, 0));
    m_texCoords.append(QVector2D(0, 0));
}

void JuliaFractal::setupShader()
{
    QGLShader *vshader = createVertexShader();
    QGLShader *fshader = createFragmentShader();

    m_program = createShaderProgram(fshader, vshader);
}

QGLShader * JuliaFractal::createVertexShader()
{
    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
    vshader->compileSourceFile(":/fractal.vsh");

    return vshader;
}

QGLShader * JuliaFractal::createFragmentShader()
{
    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);
    fshader->compileSourceFile(":/fractal.fsh");

    return fshader;
}

QGLShaderProgram * JuliaFractal::createShaderProgram(QGLShader *fshader, QGLShader *vshader)
{
    QGLShaderProgram *program = new QGLShaderProgram(this);
    program->addShader(vshader);
    program->addShader(fshader);
    program->bindAttributeLocation("vertex", 0);
    program->bindAttributeLocation("texCoord", 1);
    program->link();

    return program;
}
