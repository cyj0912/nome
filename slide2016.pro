#-------------------------------------------------
#
# Project created by QtCreator 2016-02-23T18:34:19
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NOME
TEMPLATE = app
CONFIG += c++11
CONFIG += static
CONFIG += console

SOURCES += main.cpp\
    edge.cpp \
    vertex.cpp \
    face.cpp \
    mesh.cpp \
    polyline.cpp \
    merge.cpp \
    transformation.cpp \
    makeMesh.cpp \
    subdivision.cpp \
    offset.cpp \
    stl.cpp \
    zipper.cpp \
    makePolyline.cpp \
    myselection.cpp \
    controlpanel.cpp \
    mainwindow.cpp \
    group.cpp \
    makegroup.cpp \
    sliderpanel.cpp \
    parameter.cpp \
    myslider.cpp \
    parameterbank.cpp \
    utils.cpp \
    nomeparser.cpp \
    nomeglwidget.cpp \
    bspline.cpp \
    Lewis/Data.cpp \
    Lewis/IO.cpp \
    Lewis/Reader.cpp \
    Lewis/Session.cpp \
    lexer.cpp \
    parser.cpp \
    testpolyline.cpp \
    Lewis/GroupNew.cpp \
    Lewis/InstanceNew.cpp \
    Lewis/MeshNew.cpp \
    Lewis/Node.cpp \
    Lewis/TransformationNew.cpp \
    Lewis/BankNew.cpp \
    Lewis/SliderNew.cpp

HEADERS  += \
    edge.h \
    vertex.h \
    face.h \
    mesh.h \
    polyline.h \
    transformation.h \
    merge.h \
    makeMesh.h \
    subdivison.h \
    offset.h \
    stl.h \
    zipper.h \
    makePolyline.h \
    myselection.h \
    controlpanel.h \
    mainwindow.h \
    group.h \
    makegroup.h \
    sliderpanel.h \
    parameter.h \
    myslider.h \
    parameterbank.h \
    utils.h \
    nomeparser.h \
    nomeglwidget.h \
    bspline.h \
    lexer.l \
    parser.y \
    Lewis/Data.h \
    Lewis/IO.h \
    Lewis/Reader.h \
    Lewis/Session.h \
    parser.hpp \
    testpolyline.h \
    Lewis/GroupNew.h \
    Lewis/InstanceNew.h \
    Lewis/MeshNew.h \
    Lewis/Node.h \
    Lewis/TransformationNew.h \
    Lewis/BankNew.h \
    Lewis/SliderNew.h

linux{
    LIBS += -lglut -lGLU
}

mac{
    INCLUDEPATH = /usr/local/include
    LIBS += -framework GLUT -framework OpenGL
}

win32{
    LIBS += -lopengl32 -lglu32 -lglut32
    INCLUDEPATH = $$PWD/../include
    RC_ICONS += nomeIcon.ico
}
