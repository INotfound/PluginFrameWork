/*
 * @File: Generator.cpp
 * @Author: INotFound
 * @Date: 2020-07-08 13:45:19
 * @LastEditTime: 2020-08-01 10:04:24
 */ 
#if defined(_WIN32) || defined(_WIN64)

#include <io.h>
#include <direct.h> 
#define ACCESS(fileName,accessMode) _access(fileName,accessMode)
#define MKDIR(path) _mkdir(path)

#else

#include <unistd.h>
#include <sys/stat.h>
#define ACCESS(fileName,accessMode) access(fileName,accessMode)
#define MKDIR(path) mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)

#endif

#include <string>
#include <cstdlib>
#include <fstream>
#include <stdint.h>

void createDirectory(const std::string& path){
    if(ACCESS(path.c_str(), 0) != 0){
       MKDIR(path.c_str());
    }
}

void generatorMANIFEST(char* fileName){
    std::string file("./");
    file += fileName;
    createDirectory(file);
    file += "/";
    file += "MANIFEST.MF";

    std::fstream fileStream;
    fileStream.open(file,std::ios_base::out);
    if(!fileStream.is_open()){
        std::printf("File path error!!!\n");
    }
    fileStream << "Plugin-Version:"
               << "0.0.1\n"
               << "Plugin-SymbolicName:" 
               << fileName;
    fileStream.close();
}

void generatorMakeLists(char* fileName){
    std::string file("./");
    file += fileName;
    createDirectory(file);
    file += "/";
    file += "CMakeLists.txt";

    std::fstream fileStream;
    fileStream.open(file,std::ios_base::out);
    if(!fileStream.is_open()){
        std::printf("File path error!!!\n");
    }
    fileStream  << "cmake_minimum_required(VERSION 3.0)\n";
    fileStream  << "project(" << fileName << ")\n\n"
                << "set(Resouce MANIFEST)\n"
                << "set(CMAKE_CXX_STANDARD 11)\n"
                << "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n\n"
                << "########################################ENV################################################\n"
                << "set(MagicLibrary {Magic Library Path})\n"
                << "########################################ENV################################################\n\n"
                << "link_libraries(Magic)\n"
                << "link_directories(${MagicLibrary}/Lib)\n"
                << "include(${MagicLibrary}/Library.cmake)\n"
                << "include_directories(\n"
                << "    Include\n"
                << "    ${MagicLibrary}/Include/Core\n"
                << "    ${MagicLibrary}/Include/Utility\n"
                << "    ${MagicLibrary}/Include/PluginFramework\n"
                << ")\n"
                << "set(SRC\n"
                << "    Source/" << fileName << "Impl.cpp\n"
                << "    Source/" << fileName << "Activator.cpp\n"
                << ")\n\n"
                << "function(EMBEDFILE OUTFILE)\n"
                << "    execute_process(\n"
                << "        RESULT_VARIABLE ERROR\n"
                << "        COMMAND ${MagicLibrary}/Bin/EmbedFile ${CMAKE_BINARY_DIR}/${OUTFILE} ${PROJECT_SOURCE_DIR}/${OUTFILE}.MF\n"
                << "    )\n"
                << "    message(\"${MagicLibrary}/Bin/EmbedFile\")\n"
                << "    message(\"Now Generating EmbedFile{ ${ERROR} }...\")\n"
                << "    add_library(" << fileName << " MODULE ${SRC} ${CMAKE_BINARY_DIR}/${OUTFILE}.cpp)\n"
                << "endfunction(EMBEDFILE)\n\n"
                << "EMBEDFILE(${Resouce})";
    fileStream.close();
}

void generatorImplInclude(char* fileName){
    std::string file("./");
    file += fileName;
    file += "/Include";
    createDirectory(file);
    file += "/";
    file += fileName;
    file += "Impl.h";

    std::fstream fileStream;
    fileStream.open(file,std::ios_base::out);
    if(!fileStream.is_open()){
        std::printf("File path error!!!\n");
    }
    fileStream  << "#pragma once\n"
                << "#include \""<< fileName << "Service.h\"\n\n"
                << "namespace " << fileName <<"{\n"
                << "    class "<< fileName <<"Impl :public "<< fileName <<"Service"<< "{\n"
                << "    public:\n"
                << "        "<< fileName <<"Impl();\n"
                << "    };\n"
                << "}";
    fileStream.close();
}

void generatorImplCppFile(char* fileName){
    std::string file("./");
    file += fileName;
    file += "/Source";
    createDirectory(file);
    file += "/";
    file += fileName;
    file += "Impl.cpp";

    std::fstream fileStream;
    fileStream.open(file,std::ios_base::out);
    if(!fileStream.is_open()){
        std::printf("File path error!!!\n");
    }
    fileStream  << "#include \""<< fileName <<"Impl.h\"\n\n"
                << "namespace " << fileName <<"{\n"
                << "    " << fileName << "Impl::"<< fileName <<"Impl(){\n"
                << "    }\n"
                << "}";
    fileStream.close();
}

void generatorServiceInclude(char* fileName){
    std::string file("./");
    file += fileName;
    file += "/Include";
    createDirectory(file);
    file += "/";
    file += fileName;
    file += "Service.h";

    std::fstream fileStream;
    fileStream.open(file,std::ios_base::out);
    if(!fileStream.is_open()){
        std::printf("File path error!!!\n");
    }
    fileStream  << "#pragma once\n"
                << "#include <PluginFramework.h>\n\n"
                << "namespace " << fileName <<"{\n"
                << "    class "<< fileName <<"Service{\n"
                << "    public:\n"
                << "        virtual ~" << fileName << "Service(){}\n"
                << "    };\n"
                << "}\n"
                << "MAGIC_SERVICE("<< fileName <<"::"<< fileName <<"Service,"<< "\"com." << fileName <<"."<< fileName <<"Service\"" << ")\n";
    fileStream.close();
}

void generatorActivatorInclude(char* fileName){
    std::string file("./");
    file += fileName;
    file += "/Include";
    createDirectory(file);
    file += "/";
    file += fileName;
    file += "Activator.h";

    std::fstream fileStream;
    fileStream.open(file,std::ios_base::out);
    if(!fileStream.is_open()){
        std::printf("File path error!!!\n");
    }
    fileStream  << "#pragma once\n"
                << "#include <PluginActivator.h>\n\n"
                << "namespace " << fileName <<"{\n"
                << "    class "<< fileName <<"Activator: public Magic::IPluginActivator{\n"
                << "    public:\n"
                << "        void onStart(Safe<Magic::PluginContext>&) override;\n"
                << "        void onStop(Safe<Magic::PluginContext>&) override;\n"
                << "    };\n"
                << "}\n"
                << "MAGIC_PLUGIN("<< fileName <<"::"<< fileName <<"Activator)\n";
    fileStream.close();
}

void generatorActivatorCppFile(char* fileName){
    std::string file("./");
    file += fileName;
    file += "/Source";
    createDirectory(file);
    file += "/";
    file += fileName;
    file += "Activator.cpp";

    std::fstream fileStream;
    fileStream.open(file,std::ios_base::out);
    if(!fileStream.is_open()){
        std::printf("File path error!!!\n");
    }
    fileStream  << "#include <PluginContext.h>\n\n"
                << "#include \""<< fileName <<"Service.h\"\n"
                << "#include \""<< fileName <<"Activator.h\"\n\n"
                << "namespace " << fileName <<"{\n"
                << "    void " << fileName << "Activator::onStart(Safe<Magic::PluginContext>& ctx){\n"
                << "    }\n\n"
                << "    void " << fileName << "Activator::onStop(Safe<Magic::PluginContext>& ctx){\n"
                << "    }\n"
                << "}";
    fileStream.close();
}

int main(int argc, char** argv){
    if(argc < 2){
        std::printf("Bad parameters!!!\n");
        return EXIT_FAILURE;
    }
    generatorMANIFEST(argv[1]);
    generatorMakeLists(argv[1]);
    generatorImplInclude(argv[1]);
    generatorImplCppFile(argv[1]);
    generatorServiceInclude(argv[1]);
    generatorActivatorInclude(argv[1]);
    generatorActivatorCppFile(argv[1]);
    return EXIT_SUCCESS;
}