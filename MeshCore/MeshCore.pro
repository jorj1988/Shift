#-------------------------------------------------
#
# Project created by QtCreator 2011-01-29T15:56:15
#
#-------------------------------------------------
TARGET = ShiftMeshCore
TEMPLATE = lib

include("../../Eks/EksCore/GeneralOptions.pri")

HEADERS += MeshCore.h \
    MCKernel.h \
    MCPolyhedron.h \
    MCCGALSetup.h \
    MCGeometry.h \
    MCCuboid.h \
    MCDensityShape.h \
    MCSphere.h \
    MCSphere.h \
    MCShape.h

INCLUDEPATH += $$ROOT/shift/GraphicsCore \
    $$ROOT/Eks/EksCore/include \
    $$ROOT/Eks/Eks3D/include \
    $$ROOT/Eks/EksScript \
    $$ROOT/Shift/ShiftCore/include \
    $$ROOT/shift/MeshCore

LIBS += -lShiftCore -lEksCore -lEks3D -lEksScript -lShiftGraphicsCore

SOURCES += \
    MeshCore.cpp \
    MCPolyhedron.cpp \
    MCGeometry.cpp \
    MCCuboid.cpp \
    MCCGALCore.cpp \
    MCCGALRandom.cpp \
    MCCGALTimer.cpp \
    MCDensityShape.cpp \
    MCSphere.cpp \
    MCShape.cpp





