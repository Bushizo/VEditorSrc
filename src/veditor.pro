QT+= widgets
QT += printsupport

QMAKE_RPATHDIR += /opt/VEditor/lib/

SOURCES += \
    main.cpp \
    widgetveditor.cpp \
    aboutveditor.cpp \
    license.cpp \
    windowveditor.cpp

HEADERS += \
    widgetveditor.h \
    aboutveditor.h \
    license.h \
    windowveditor.h
