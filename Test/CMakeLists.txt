cmake_minimum_required(VERSION 3.0)

project(TestPlugin)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


########################################################################################
set(PLUGIN /home/magic/WorkSpace/Magic)
include_directories(
	${PLUGIN}/Include/Core
    ${PLUGIN}/Include/Utility
    ${PLUGIN}/Include/PluginFramework
)
link_directories(
    ${PLUGIN}/Lib
)
include(${PLUGIN}/Library.cmake)
########################################################################################


link_libraries(Magic)
set(CMAKE_CXX_STANDARD 11)
add_executable(Test Test.cpp)


set(Resouce MANIFEST)

function(EMBEDFILE OUTFILE)
    execute_process(
        RESULT_VARIABLE ERROR
        COMMAND ${PLUGIN}/Bin/EmbedFile ${OUTFILE} ${PROJECT_SOURCE_DIR}/${OUTFILE}.MF
    )
    message("${PLUGIN}/Bin/EmbedFile")
    message("Now Generating EmbedFile{ ${ERROR} }...")
    add_library(TestPlugins MODULE TestActivator.cpp TestService.cpp ${CMAKE_BINARY_DIR}/${OUTFILE}.cpp)
endfunction(EMBEDFILE)
EMBEDFILE(${Resouce})