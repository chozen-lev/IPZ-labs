TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/main.cpp \
    src/scanner.cpp \
    src/listing.cpp

HEADERS += \
    src/token.h \
    src/scanner.h \
    src/listing.h
