QT += opengl
HEADERS += \
    FractalWidget.h \
    JuliaFractal.h \
    OscillatingAnimation.h
SOURCES += \
    main.cpp \
    JuliaFractal.cpp \
    FractalWidget.cpp \
    OscillatingAnimation.cpp
OTHER_FILES += fractal.vsh \
    fractal.fsh
RESOURCES += Fractal.qrc

DISTFILES += \
    README.md
