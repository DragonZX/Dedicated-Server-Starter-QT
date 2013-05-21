TEMPLATE = app
TARGET = start_server
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += main.h \
    config.h \
    functions.h
SOURCES += main.cpp \
    config.cpp \
    functions.cpp
TRANSLATIONS += lang/dss_en.ts \
    lang/dss_ru.ts \
    lang/dss_ua.ts
win32:RC_FILE = main-win32.rc
