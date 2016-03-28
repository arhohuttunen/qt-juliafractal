QT += opengl
QT += multimedia
HEADERS += \
    FractalWidget.h \
    JuliaFractal.h
SOURCES += \
    main.cpp \
    JuliaFractal.cpp \
    FractalWidget.cpp
OTHER_FILES += fractal.vsh \
    fractal.fsh
RESOURCES += Fractal.qrc

DISTFILES += \
    README.md
