cmake_minimum_required(VERSION 3.16)

project(
    SmartCalc
    VERSION 0.1.0
    DESCRIPTION "Engineering scientific calculator"
    LANGUAGES CXX
)
if(MSVC)
    add_compile_options(/utf-8)
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SMARTCALC_ENABLE_QT "Build the Qt Widgets GUI module when Qt is available" ON)
option(SMARTCALC_BUILD_TESTS "Build the placeholder test executables" OFF)

set(SMARTCALC_CORE_SOURCES
    src/core/Token.cpp
    src/core/Token.h
    src/core/Lexer.cpp
    src/core/Lexer.h
    src/core/Parser.cpp
    src/core/Parser.h
    src/core/ASTNode.cpp
    src/core/ASTNode.h
    src/core/Evaluator.cpp
    src/core/Evaluator.h
    src/core/OperatorTable.cpp
    src/core/OperatorTable.h
    src/core/CalcException.cpp
    src/core/CalcException.h
)

set(SMARTCALC_MATH_SOURCES
    src/math/ComplexNumber.cpp
    src/math/ComplexNumber.h
    src/math/Matrix.cpp
    src/math/Matrix.h
    
    src/math/MatrixSolver.h
    src/math/ScientificFunction.cpp
    src/math/ScientificFunction.h
    src/math/FunctionSampler.cpp
    src/math/FunctionSampler.h
    src/math/UnitConverter.cpp
    src/math/UnitConverter.h
)

set(SMARTCALC_STORAGE_SOURCES
    src/storage/HistoryRecord.cpp
    src/storage/HistoryRecord.h
    src/storage/HistoryManager.cpp
    src/storage/HistoryManager.h
    src/storage/SettingsManager.cpp
    src/storage/SettingsManager.h
    src/storage/JsonStorage.cpp
    src/storage/JsonStorage.h
)

set(SMARTCALC_UTILS_SOURCES
    src/utils/StringUtil.cpp
    src/utils/StringUtil.h
    src/utils/NumberFormat.cpp
    src/utils/NumberFormat.h
    src/utils/TimeUtil.cpp
    src/utils/TimeUtil.h
)

set(SMARTCALC_GUI_SOURCES
    src/gui/MainWindow.cpp
    src/gui/MainWindow.h
    src/gui/BasicCalcPage.cpp
    src/gui/BasicCalcPage.h
    src/gui/UnitPage.cpp
    src/gui/UnitPage.h
    src/gui/MatrixPage.cpp
    src/gui/MatrixPage.h
    src/gui/PlotPage.cpp
    src/gui/PlotPage.h
    src/gui/HistoryPage.cpp
    src/gui/HistoryPage.h
    src/gui/SettingsDialog.cpp
    src/gui/SettingsDialog.h
)

add_library(SmartCalcCore STATIC ${SMARTCALC_CORE_SOURCES} "src/math/MatrixSolver.cpp")
add_library(SmartCalc::Core ALIAS SmartCalcCore)
target_include_directories(SmartCalcCore PUBLIC "${PROJECT_SOURCE_DIR}/src")

add_library(SmartCalcMath STATIC ${SMARTCALC_MATH_SOURCES} "src/math/MatrixSolver.cpp")
add_library(SmartCalc::Math ALIAS SmartCalcMath)
target_include_directories(SmartCalcMath PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(SmartCalcMath PUBLIC SmartCalc::Core)

add_library(SmartCalcStorage STATIC ${SMARTCALC_STORAGE_SOURCES} "src/math/MatrixSolver.cpp")
add_library(SmartCalc::Storage ALIAS SmartCalcStorage)
target_include_directories(SmartCalcStorage PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(SmartCalcStorage PUBLIC SmartCalc::Core)

add_library(SmartCalcUtils STATIC ${SMARTCALC_UTILS_SOURCES} "src/math/MatrixSolver.cpp")
add_library(SmartCalc::Utils ALIAS SmartCalcUtils)
target_include_directories(SmartCalcUtils PUBLIC "${PROJECT_SOURCE_DIR}/src")

set(SMARTCALC_QT_AVAILABLE OFF)
if(SMARTCALC_ENABLE_QT)
    find_package(QT NAMES Qt6 Qt5 QUIET COMPONENTS Widgets)

    if(WIN32 AND NOT QT_FOUND)
        file(
            GLOB SMARTCALC_QT_KITS
            LIST_DIRECTORIES TRUE
            "C:/Qt/*/msvc*_64"
            "D:/Qt/*/msvc*_64"
            "E:/Qt/*/msvc*_64"
        )
        list(SORT SMARTCALC_QT_KITS COMPARE NATURAL ORDER DESCENDING)

        foreach(SMARTCALC_QT_KIT IN LISTS SMARTCALC_QT_KITS)
            if(
                EXISTS "${SMARTCALC_QT_KIT}/lib/cmake/Qt6/Qt6Config.cmake"
                OR EXISTS "${SMARTCALC_QT_KIT}/lib/cmake/Qt5/Qt5Config.cmake"
            )
                list(PREPEND CMAKE_PREFIX_PATH "${SMARTCALC_QT_KIT}")
                break()
            endif()
        endforeach()

        find_package(QT NAMES Qt6 Qt5 QUIET COMPONENTS Widgets Charts)
    endif()

    if(QT_FOUND)
        find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

        set(CMAKE_AUTOMOC ON)
        set(CMAKE_AUTOUIC ON)
        set(CMAKE_AUTORCC ON)
        set(SMARTCALC_QT_AVAILABLE ON)
    else()
        message(WARNING "Qt Widgets was not found; GUI files will not have Qt include paths.")
    endif()
endif()

add_library(SmartCalcGui STATIC ${SMARTCALC_GUI_SOURCES} "src/math/MatrixSolver.cpp")
add_library(SmartCalc::Gui ALIAS SmartCalcGui)
target_include_directories(SmartCalcGui PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(
    SmartCalcGui
    PUBLIC
        SmartCalc::Core
        SmartCalc::Math
        SmartCalc::Storage
        SmartCalc::Utils
)

if(SMARTCALC_QT_AVAILABLE)
    target_link_libraries(SmartCalcGui PUBLIC 
Qt${QT_VERSION_MAJOR}::Widgets
Qt${QT_MAJOR_VERSION}::Charts
)
endif()

set_property(
    DIRECTORY
    APPEND
    PROPERTY CMAKE_CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/main.cpp"
)

file(READ "${PROJECT_SOURCE_DIR}/src/main.cpp" SMARTCALC_MAIN_CONTENT)
string(
    REGEX MATCH
    "main[ \t\r\n]*\\("
    SMARTCALC_HAS_MAIN
    "${SMARTCALC_MAIN_CONTENT}"
)

if(NOT SMARTCALC_HAS_MAIN)
    set(SMARTCALC_PLACEHOLDER_MAIN
        "${CMAKE_CURRENT_BINARY_DIR}/generated/smartcalc_placeholder_main.cpp"
    )
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/generated")
    file(WRITE "${SMARTCALC_PLACEHOLDER_MAIN}" "int main() { return 0; }\n")

    add_executable(SmartCalc src/main.cpp "${SMARTCALC_PLACEHOLDER_MAIN}" "src/math/MatrixSolver.cpp")
    message(STATUS "src/main.cpp has no main function; SmartCalc uses a generated placeholder entry point.")
else()
    add_executable(SmartCalc src/main.cpp)
endif()

target_link_libraries(
    SmartCalc
    PRIVATE
        SmartCalc::Core
        SmartCalc::Math
        SmartCalc::Storage
        SmartCalc::Utils
        SmartCalc::Gui
)

if(SMARTCALC_QT_AVAILABLE AND QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartCalc)
endif()

source_group(TREE "${PROJECT_SOURCE_DIR}/src" PREFIX "Source Files" FILES
    src/main.cpp
    ${SMARTCALC_CORE_SOURCES}
    ${SMARTCALC_MATH_SOURCES}
    ${SMARTCALC_STORAGE_SOURCES}
    ${SMARTCALC_UTILS_SOURCES}
    ${SMARTCALC_GUI_SOURCES}
)

if(SMARTCALC_BUILD_TESTS)
    enable_testing()

    add_executable(test_expression EXCLUDE_FROM_ALL tests/test_expression.cpp "src/math/MatrixSolver.cpp")
    target_link_libraries(test_expression PRIVATE SmartCalc::Core SmartCalc::Math)
    add_test(NAME expression COMMAND test_expression)

    add_executable(test_matrix EXCLUDE_FROM_ALL tests/test_matrix.cpp "src/math/MatrixSolver.cpp")
    target_link_libraries(test_matrix PRIVATE SmartCalc::Math)
    add_test(NAME matrix COMMAND test_matrix)

    add_executable(test_math EXCLUDE_FROM_ALL tests/test_math.cpp)
    target_link_libraries(test_math PRIVATE SmartCalc::Math)
    add_test(NAME math COMMAND test_math)

    add_executable(test_exception EXCLUDE_FROM_ALL tests/test_exception.cpp "src/math/MatrixSolver.cpp")
    target_link_libraries(test_exception PRIVATE SmartCalc::Core SmartCalc::Math)
    add_test(NAME exception COMMAND test_exception)

    add_executable(test_storage EXCLUDE_FROM_ALL tests/test_storage.cpp)
    target_link_libraries(test_storage PRIVATE SmartCalc::Storage SmartCalc::Utils)
    add_test(NAME storage COMMAND test_storage)
endif()
