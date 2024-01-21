#ifndef CTM_HPP
#define CTM_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <fstream>
#include <filesystem>

class Ctm
{
private:
    std::vector<std::string> args;
    std::string mode;
    std::string type;
    struct
    {
        std::vector<std::string> dirs;
        std::vector<std::string> binDir;
        std::vector<std::string> srcDir;
    }MakeTemplate;

    enum Modes
    {
        newtemp,
        help
    };

    enum Types
    {
        makefile,
        cmake
    };

    enum ErrorType{
        ModeError,
        TypeError
    };

    enum DirType{
        bin,
        include,
        lib,
        src
    };

    std::map<Modes,std::string> ModeList;
    std::map<Types,std::string> TypeList;

    std::map<ErrorType,std::string> ErrorList;

    std::map<DirType,std::string> DirList;

    void createMakeTemplate();
    void writeFile(const std::string &path,const std::string &data);
    std::string readFile(const std::string &path);
    void helpMode();
    std::string CreateDirCommand;
    std::string CreateFileCommand;

    std::string cppFilePath;
    std::string makefileFilePath;

public:
    Ctm(int argSize, char *args[]);
    void run();
    
};

#endif
