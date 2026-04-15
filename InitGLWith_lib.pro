QT = core

CONFIG += c++17 cmdline



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        shader.cpp \
        testengine.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../GLFrameWork/build/Desktop-Debug/release/ -lGLFrameWork
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../GLFrameWork/build/Desktop-Debug/debug/ -lGLFrameWork
else:unix: LIBS += -L$$PWD/../GLFrameWork/build/Desktop-Debug/ -lGLFrameWork
#else:unix: LIBS += -L/home/paul/workspace/GLFrameWork/build/Desktop-Desktop-Release/ -lGLFrameWork

INCLUDEPATH += $$PWD/../GLFrameWork
DEPENDPATH += $$PWD/../GLFrameWork

INCLUDEPATH += $$PWD/../GLFrameWork

HEADERS += \
    shader.h \
    testengine.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib64/release/ -lSDL2_image
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib64/debug/ -lSDL2_image
else:unix: LIBS += -L$$PWD/../../../../usr/lib64/ -lSDL2_image

INCLUDEPATH += $$PWD/../../../../usr/include/SDL2
DEPENDPATH += $$PWD/../../../../usr/include/SDL2

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libs/Logger/release/ -lLogger
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libs/Logger/debug/ -lLogger
else:unix: LIBS += -L$$PWD/../libs/Logger/ -lLogger

INCLUDEPATH += $$PWD/../includes
DEPENDPATH += $$PWD/../includes

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libs/imageloader/release/ -lImageLoader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libs/imageloader/debug/ -lImageLoader
else:unix: LIBS += -L$$PWD/../libs/imageloader/ -lImageLoader

INCLUDEPATH += $$PWD/../includes
DEPENDPATH += $$PWD/../includes

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib64/release/ -lfreetype
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib64/debug/ -lfreetype
else:unix: LIBS += -L$$PWD/../../../../usr/lib64/ -lfreetype

INCLUDEPATH += $$PWD/../../../../usr/include/
DEPENDPATH += $$PWD/../../../../usr/include/

INCLUDEPATH += /usr/include/glm
DEPENDPATH += /usr/include/glm

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib64/release/ -lGL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib64/debug/ -lGL
else:unix: LIBS += -L$$PWD/../../../../usr/lib64/ -lGL

INCLUDEPATH += $$PWD/../../../../usr/include/GL
DEPENDPATH += $$PWD/../../../../usr/include/GL

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib64/release/ -lGLEW
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib64/debug/ -lGLEW
else:unix: LIBS += -L$$PWD/../../../../usr/lib64/ -lGLEW

INCLUDEPATH += $$PWD/../../../../usr/include/GL
DEPENDPATH += $$PWD/../../../../usr/include/GL
