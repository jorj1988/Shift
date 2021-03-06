# -------------------------------------------------
# Project created by QtCreator 2010-06-09T09:04:56
# -------------------------------------------------

TARGET = ShiftCore
TEMPLATE = lib

QT -= core gui

include("../../Eks/EksCore/GeneralOptions.pri")

INCLUDEPATH += $$ROOT/Shift/ShiftCore/include \
    $$ROOT/Shift/ShiftCore/src \
    $$ROOT/Eks/EksCore/include

LIBS += -lEksCore

SOURCES += \
    src/sentity.cpp \
    src/sdatabase.cpp \
    src/Properties/sproperty.cpp \
    src/Properties/sbaseproperties.cpp \
    src/Properties/sbasepointerproperties.cpp \
    src/Properties/sattribute.cpp \
    src/QtExtensions/sexternalpointer.cpp \
    src/Changes/sobserver.cpp \
    src/Changes/shandler.cpp \
    src/QtExtensions/UI/sentityui.cpp \
    src/QtExtensions/UI/sdatabasemodel.cpp \
    src/Utilities/sprocessmanager.cpp \
    src/Utilities/sresourcedescription.cpp \
    src/TypeInformation/spropertyinformation.cpp \
    src/TypeInformation/styperegistry.cpp \
    src/QtExtensions/sinterfaces.cpp \
    src/TypeInformation/spropertyinstanceinformation.cpp \
    src/TypeInformation/spropertytraits.cpp \
    src/Serialisation/JsonParser/JSON_parser.c \
    src/Serialisation/sxmlio.cpp \
    src/Serialisation/sbinaryio.cpp \
    src/Serialisation/sjsonio.cpp \
    src/Serialisation/sloader.cpp \
    src/Utilities/spropertyname.cpp \
    src/TypeInformation/spropertyinformationhelpers.cpp \
    src/QtExtensions/UI/sdebugger.cpp \
    src/Utilities/satomichelper.cpp \
    src/Changes/spropertychanges.cpp \
    src/Properties/scontainer.cpp \
    src/Properties/sset.cpp \
    src/Properties/sarray.cpp \
    src/Serialisation/ssaver.cpp \
    src/Serialisation/sattributeio.cpp \
    src/Utilities/smetatype.cpp \
    src/Serialisation/sattributeinterface.cpp \
    src/Serialisation/sioblock.cpp \
    src/QtExtensions/sqtproperties.cpp \
    src/TypeInformation/smodule.cpp

HEADERS += \
    include/shift/sglobal.h \
    include/shift/sentity.h \
    include/shift/sdatabase.h \
    include/shift/Properties/sproperty.h \
    include/shift/Properties/sbaseproperties.h \
    include/shift/Properties/sbasepointerproperties.h \
    include/shift/Properties/spropertymacros.h \
    include/shift/QtExtensions/sexternalpointer.h \
    include/shift/Changes/schange.h \
    include/shift/Changes/sobserver.h \
    include/shift/Changes/shandler.h \
    include/shift/Changes/shandler.inl \
    include/shift/Changes/spropertychanges.h \
    include/shift/UI/sentityui.h \
    include/shift/Serialisation/sloader.h \
    src/Serialisation/JsonParser/JSON_parser.h \
    include/shift/Serialisation/sxmlio.h \
    include/shift/Serialisation/sbinaryio.h \
    include/shift/Serialisation/sjsonio.h \
    include/shift/TypeInformation/styperegistry.h \
    include/shift/TypeInformation/sinterface.h \
    include/shift/TypeInformation/spropertyinformation.h \
    include/shift/TypeInformation/spropertyinstanceinformation.h \
    include/shift/QtExtensions/sinterfaces.h \
    include/shift/TypeInformation/spropertyinformationhelpers.h \
    include/shift/Utilities/sentityweakpointer.h \
    include/shift/Utilities/sprocessmanager.h \
    include/shift/Utilities/siterator.h \
    include/shift/Utilities/sresourcedescription.h \
    include/shift/Utilities/spropertyname.h \
    include/shift/TypeInformation/spropertytraits.h \
    include/shift/QtExtensions/UI/spropertydefaultui.h \
    include/shift/QtExtensions/UI/sdatabasemodel.h \
    include/shift/QtExtensions/UI/sdebugger.h \
    include/shift/Utilities/satomichelper.h \
    include/shift/Properties/sattribute.h \
    include/shift/Properties/sattribute.inl \
    include/shift/Properties/scontainer.h \
    include/shift/Properties/scontainer.inl \
    include/shift/Properties/scontaineriterators.h \
    include/shift/Properties/sdata.inl \
    include/shift/Properties/sdata.h \
    include/shift/Properties/scontainerinternaliterators.h \
    include/shift/Properties/sset.h \
    include/shift/Properties/sarray.h \
    include/shift/Serialisation/ssaver.h \
    include/shift/Serialisation/sattributeio.h \
    include/shift/Utilities/smetatype.h \
    include/shift/Serialisation/sattributeinterface.h \
    include/shift/Serialisation/sioblock.h \
    include/shift/QtExtensions/sqtproperties.h \
    include/shift/TypeInformation/smodule.h




