cmake_minimum_required(VERSION 3.1)

project(Nome)

#Add prefix paths for Homebrew
list(APPEND CMAKE_PREFIX_PATH /usr/local/opt/flex)
list(APPEND CMAKE_PREFIX_PATH /usr/local/opt/bison)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_subdirectory(Math)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

find_package(BISON 3)
find_package(FLEX 2.6)

set(PARSER_SOURCES
    compilerBank/parserBank.y
    compilerBank/lexerBank.l
    compilerNome/parser.y
    compilerNome/lexer.l
    compilerStl/parserStl.y
    compilerStl/lexerStl.l
    compilerObj/parserObj.y
    compilerObj/lexerObj.l)

if(BISON_FOUND AND FLEX_FOUND)
    BISON_TARGET(bank compilerBank/parserBank.y ${CMAKE_CURRENT_SOURCE_DIR}/compilerBank/parserBank.cpp COMPILE_FLAGS "-pbank -dy")
    FLEX_TARGET(bank compilerBank/lexerBank.l ${CMAKE_CURRENT_SOURCE_DIR}/compilerBank/lexerBank.cpp)
    BISON_TARGET(nom compilerNome/parser.y ${CMAKE_CURRENT_SOURCE_DIR}/compilerNome/parser.cpp COMPILE_FLAGS "-pnom -dy")
    FLEX_TARGET(nom compilerNome/lexer.l ${CMAKE_CURRENT_SOURCE_DIR}/compilerNome/lexer.cpp)
    BISON_TARGET(stl compilerStl/parserStl.y ${CMAKE_CURRENT_SOURCE_DIR}/compilerStl/parserStl.cpp COMPILE_FLAGS "-pstl -dy")
    FLEX_TARGET(stl compilerStl/lexerStl.l ${CMAKE_CURRENT_SOURCE_DIR}/compilerStl/lexerStl.cpp)
    BISON_TARGET(obj compilerObj/parserObj.y ${CMAKE_CURRENT_SOURCE_DIR}/compilerObj/parserObj.cpp COMPILE_FLAGS "-pobj -dy")
    FLEX_TARGET(obj compilerObj/lexerObj.l ${CMAKE_CURRENT_SOURCE_DIR}/compilerObj/lexerObj.cpp)
else()
    message(STATUS "Flex and Bison not found, skip regenerating parsers.")
endif()

set(SOURCES
        main.cpp
        edge.cpp
        vertex.cpp
        face.cpp
        mesh.cpp
        polyline.cpp
        merge.cpp
        transformation.cpp
        makeMesh.cpp
        subdivision.cpp
        offset.cpp
        stl.cpp
        zipper.cpp
        makePolyline.cpp
        myselection.cpp
        controlpanel.cpp
        mainwindow.cpp
        group.cpp
        makegroup.cpp
        sliderpanel.cpp
        parameter.cpp
        myslider.cpp
        parameterbank.cpp
        utils.cpp
        nomeparser.cpp
        nomeglwidget.cpp
        bspline.cpp
        newNOME/Data.cpp
        newNOME/IO.cpp
        newNOME/Reader.cpp
        newNOME/Session.cpp
        testpolyline.cpp
        newNOME/GroupNew.cpp
        newNOME/InstanceNew.cpp
        newNOME/MeshNew.cpp
        newNOME/Node.cpp
        newNOME/TransformationNew.cpp
        newNOME/BankNew.cpp
        newNOME/SliderNew.cpp
        newNOME/PolylineNew.cpp
        newNOME/CircleNew.cpp
        newNOME/FunnelNew.cpp
        newNOME/TunnelNew.cpp
        newNOME/ConsolidateWindow.cpp
        newNOME/SubdivisionNew.cpp
        newNOME/SliderSubdivisionNew.cpp
        newNOME/OffsetNew.cpp
        newNOME/SliderOffsetNew.cpp
        nomeFlexBison.cpp
        compilerNome/parser.cpp
        compilerNome/lexer.cpp
        stlFlexBison.cpp
        compilerStl/parserStl.cpp
        compilerStl/lexerStl.cpp
        newNOME/BSplineNew.cpp
        newNOME/BezierCurveNew.cpp
        objFlexBison.cpp
        compilerObj/parserObj.cpp
        compilerObj/lexerObj.cpp
        compilerBank/parserBank.cpp
        compilerBank/lexerBank.cpp
        bankFlexBison.cpp
        newNOME/GroupWindow.cpp
        newNOME/Octree.cpp
        newNOME/OctreeProxy.cpp)

set(HEADERS
        edge.h
        vertex.h
        face.h
        mesh.h
        polyline.h
        transformation.h
        merge.h
        makeMesh.h
        subdivison.h
        offset.h
        stl.h
        zipper.h
        makePolyline.h
        myselection.h
        controlpanel.h
        mainwindow.h
        group.h
        makegroup.h
        sliderpanel.h
        parameter.h
        myslider.h
        parameterbank.h
        utils.h
        nomeparser.h
        nomeglwidget.h
        bspline.h
        newNOME/Data.h
        newNOME/IO.h
        newNOME/Reader.h
        newNOME/Session.h
        testpolyline.h
        newNOME/GroupNew.h
        newNOME/InstanceNew.h
        newNOME/MeshNew.h
        newNOME/Node.h
        newNOME/TransformationNew.h
        newNOME/BankNew.h
        newNOME/SliderNew.h
        newNOME/PolylineNew.h
        newNOME/CircleNew.h
        newNOME/FunnelNew.h
        newNOME/TunnelNew.h
        newNOME/ConsolidateWindow.h
        newNOME/SubdivisionNew.h
        newNOME/SliderSubdivisionNew.h
        newNOME/OffsetNew.h
        newNOME/SliderOffsetNew.h
        compilerNome/parser.hpp
        compilerStl/parserStl.hpp
        newNOME/BSplineNew.h
        newNOME/BezierCurveNew.h
        compilerObj/parserObj.hpp
        compilerBank/parserBank.hpp
        newNOME/GroupWindow.h
        newNOME/Octree.h
        newNOME/OctreeProxy.h)

add_executable(Nome MACOSX_BUNDLE ${SOURCES} ${HEADERS} ${PARSER_SOURCES} nome_resource.rc)

set_target_properties(Nome PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME Nome MACOSX_BUNDLE_BUNDLE_VERSION 1.0)

if(MSVC)
	#Enable multithreaded building on MSVC
	target_compile_options(Nome PRIVATE /MP)
endif()

target_link_libraries(Nome PRIVATE Math)

target_link_libraries(Nome PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL)

message(STATUS "OpenGL include:${OPENGL_INCLUDE_DIR} lib:${OPENGL_LIBRARIES}")
target_include_directories(Nome PRIVATE ${OPENGL_INCLUDE_DIR})
target_link_libraries(Nome PRIVATE ${OPENGL_LIBRARIES})

target_link_libraries(Nome PRIVATE glm)
target_compile_definitions(Nome PRIVATE GLM_ENABLE_EXPERIMENTAL)

install(TARGETS Nome RUNTIME DESTINATION . BUNDLE DESTINATION .)
install(DIRECTORY examples DESTINATION .)
