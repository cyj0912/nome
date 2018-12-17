cmake_minimum_required(VERSION 3.1)

project(Nome)

#Add prefix paths for Homebrew
list(APPEND CMAKE_PREFIX_PATH /usr/local/opt/flex)
list(APPEND CMAKE_PREFIX_PATH /usr/local/opt/bison)

#Do not run AUTOMOC on generated code
cmake_policy(SET CMP0071 OLD)

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
find_package(Boost REQUIRED COMPONENTS regex)

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

set(GENERATED_PARSERS)

if(BISON_FOUND AND FLEX_FOUND)
    BISON_TARGET(bankParser compilerBank/parserBank.y ${CMAKE_CURRENT_SOURCE_DIR}/compilerBank/parserBank.cpp COMPILE_FLAGS "-pbank -dy")
    FLEX_TARGET(bankLexer compilerBank/lexerBank.l ${CMAKE_CURRENT_SOURCE_DIR}/compilerBank/lexerBank.cpp)
    ADD_FLEX_BISON_DEPENDENCY(bankLexer bankParser)
    BISON_TARGET(nomParser compilerNome/parser.y ${CMAKE_CURRENT_SOURCE_DIR}/compilerNome/parser.cpp COMPILE_FLAGS "-pnom -dy")
    FLEX_TARGET(nomLexer compilerNome/lexer.l ${CMAKE_CURRENT_SOURCE_DIR}/compilerNome/lexer.cpp)
    ADD_FLEX_BISON_DEPENDENCY(nomLexer nomParser)
    BISON_TARGET(stlParser compilerStl/parserStl.y ${CMAKE_CURRENT_SOURCE_DIR}/compilerStl/parserStl.cpp COMPILE_FLAGS "-pstl -dy")
    FLEX_TARGET(stlLexer compilerStl/lexerStl.l ${CMAKE_CURRENT_SOURCE_DIR}/compilerStl/lexerStl.cpp)
    ADD_FLEX_BISON_DEPENDENCY(stlLexer stlParser)
    BISON_TARGET(objParser compilerObj/parserObj.y ${CMAKE_CURRENT_SOURCE_DIR}/compilerObj/parserObj.cpp COMPILE_FLAGS "-pobj -dy")
    FLEX_TARGET(objLexer compilerObj/lexerObj.l ${CMAKE_CURRENT_SOURCE_DIR}/compilerObj/lexerObj.cpp)
    ADD_FLEX_BISON_DEPENDENCY(objLexer objParser)
    set(GENERATED_PARSERS
            ${BISON_bankParser_OUTPUTS}
            ${FLEX_bankLexer_OUTPUTS}
            ${BISON_nomParser_OUTPUTS}
            ${FLEX_nomLexer_OUTPUTS}
            ${BISON_stlParser_OUTPUTS}
            ${FLEX_stlLexer_OUTPUTS}
            ${BISON_objParser_OUTPUTS}
            ${FLEX_objLexer_OUTPUTS}
            )
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
		newNOME/TorusKnotNew.cpp
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
        newNOME/OctreeProxy.cpp
        newNOME/Sweep.cpp
		commonDialogs.cpp
        MacroExpander.cpp)

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
		newNOME/TorusKnotNew.h
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
        newNOME/OctreeProxy.h
        newNOME/Sweep.h
		commonDialogs.h
        MacroExpander.h)

add_executable(Nome MACOSX_BUNDLE ${SOURCES} ${HEADERS} ${PARSER_SOURCES} ${GENERATED_PARSERS} nome_resource.rc)

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

target_link_libraries(Nome PRIVATE Boost::regex)

install(TARGETS Nome RUNTIME DESTINATION . BUNDLE DESTINATION .)
install(DIRECTORY examples DESTINATION .)
