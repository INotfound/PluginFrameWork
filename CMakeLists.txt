cmake_minimum_required(VERSION 3.0)

project(Magic)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include(Library.cmake)
include_directories(Include)
include_directories(Include/Core)
include_directories(Include/Utility)
include_directories(Include/PluginFramework)

set(SRC
    Source/Core/Logger.cpp
    Source/Core/Thread.cpp

    Source/Platform/Linux/Mutex.cpp
    Source/Platform/Linux/Library.cpp
    Source/Platform/Linux/FileUtils.cpp
    Source/Platform/Linux/TimerUtils.cpp
    Source/Platform/Linux/ThreadUtils.cpp
    Source/Platform/Linux/SystemUtils.cpp

    Source/Platform/Windows/Mutex.cpp
    Source/Platform/Windows/Library.cpp
    Source/Platform/Windows/FileUtils.cpp
    Source/Platform/Windows/TimerUtils.cpp
    Source/Platform/Windows/ThreadUtils.cpp
    Source/Platform/Windows/SystemUtils.cpp

    Source/PluginFramework/Plugin.cpp
    Source/PluginFramework/Plugins.cpp
    Source/PluginFramework/Services.cpp
    Source/PluginFramework/PluginLoader.cpp
    Source/PluginFramework/PluginArchive.cpp
    Source/PluginFramework/PluginContext.cpp
    Source/PluginFramework/PluginStorage.cpp
    Source/PluginFramework/PluginManifest.cpp
    Source/PluginFramework/PluginFramework.cpp
    Source/PluginFramework/ServiceReference.cpp
    Source/PluginFramework/ServiceRegistration.cpp
    Source/PluginFramework/PluginFrameworkContext.cpp
)

add_library(Magic ${SRC})

#Tool
    add_executable(EmbedFile Tool/EmbedFile.cpp)
    add_executable(Generator Tool/Generator.cpp)

   install(TARGETS EmbedFile Generator Magic
      RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/Bin
      ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/Lib
   )