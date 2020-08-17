/*
 * @File: EmbedFile.cpp
 * @Author: INotFound
 * @Date: 2020-07-08 13:45:19
 * @LastEditTime: 2020-08-01 09:31:04
 */ 
#include <cstdlib>
#include <fstream>
int main(int argc, char** argv){
    if(argc < 3){
        std::printf("Bad parameters!!!\n");
        return EXIT_FAILURE;
    }
    std::string cpp(argv[1]);
    cpp += ".cpp";
    
    std::fstream cppFileStream;
    std::fstream resFileStream;
    cppFileStream.open(cpp,std::ios_base::out);
    resFileStream.open(argv[2],std::ios_base::in|std::ios_base::binary);
    if(!cppFileStream.is_open()||!resFileStream.is_open()){
        std::printf("File path error: %s\nOR\nFile path error: %s\n",argv[1],argv[2]);
        return EXIT_FAILURE;
    }
    cppFileStream << "#include <stdint.h>\n\n";
    cppFileStream << "const char g_Manifest[] ={ \n\t";
    int lineCount = 0;
    auto bit = resFileStream.get();
    while(!resFileStream.eof()){
        lineCount++;
        cppFileStream << "0x" << std::hex << bit << ",";
        if(lineCount == 10){
            cppFileStream << "\n\t";
            lineCount = 0;
        }
        bit = resFileStream.get();
    }
    if(lineCount>0) 
        cppFileStream << "\n";

    cppFileStream   << "};\n\n"
                    << "extern \"C\" {\n\t"
#if (defined(_WIN32) || defined(_WIN64)) && !defined(__GNUC__)
                    << "_declspec(dllexport) const char* getManifest(uint64_t& size){ \n"
#else
                    << "const char* getManifest(uint64_t& size){ \n"
#endif
                    << "\t\tsize = sizeof(g_Manifest);\n"
                    << "\t\treturn g_Manifest;\n\t}\n"
                    << "}";
    cppFileStream.close();
    resFileStream.close();
    return EXIT_SUCCESS;
}