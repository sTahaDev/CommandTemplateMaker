#include "ctm.hpp"

Ctm::Ctm(int argSize, char *args[])
{
    for (int i = 0; i < argSize; i++)
    {
        this->args.push_back(args[i]);
    }

    this->ModeList[this->Modes::newtemp] = "new";
    this->ModeList[this->Modes::help] = "help";

    this->TypeList[this->Types::makefile] = "-make";
    this->TypeList[this->Types::cmake] = "-cmake";

    this->ErrorList[this->ErrorType::ModeError] = "Error: missing argument[Mode]";
    this->ErrorList[this->ErrorType::TypeError] = "Error: missing argument[Type]";

    this->DirList[this->DirType::bin] = "bin";
    this->DirList[this->DirType::include] = "include";
    this->DirList[this->DirType::lib] = "lib";
    this->DirList[this->DirType::src] = "src";

    this->CreateDirCommand = "mkdir";
    this->CreateFileCommand = "touch";

    // Main.cpp Dosyası
    this->cppFileString = "#include <iostream> \n \n";
    this->cppFileString += "int main(){ \n \n";
    this->cppFileString += "    return 0;\n";
    this->cppFileString += "}\n";

    // Makefile Dosyası
    this->makeFileString = "APP_NAME = App \n";
    this->makeFileString += "MAIN_FILE = main.cpp \n";
    this->makeFileString += "SRC_DIR = ../src";
    this->makeFileString += "INCLUDE_DIR = ../include \n";
    this->makeFileString += "LIB_DIR = ../lib  \n";
    this->makeFileString += "FLAGS = -std=c++11 \n";
    this->makeFileString += "CPP_FILES = $(INCLUDE_DIR)/CTM/ctm.cpp \n \n";
    this->makeFileString += "all: \n";
    this->makeFileString += "g++ $(SRC_DIR)/$(MAIN_FILE) $(CPP_FILES) $(FLAGS) -I$(INCLUDE_DIR) -L$(LIB_DIR) -o ./$(APP_NAME) \n";
    this->makeFileString += "./$(APP_NAME) \n";
}

void Ctm::writeFile(const std::string path, const std::string data)
{
    std::ofstream file(path);
    if (file.is_open())
    {
        file << data << std::endl;
        file.close();
    }
    else
    {
        std::cerr << "File Can't Open" << std::endl;
    }
}

void Ctm::run()
{

    if (this->args.size() > 1)
        this->mode = this->args[1];
    else
    {
        std::cout << this->ErrorList[this->ErrorType::ModeError] << std::endl;
        return;
    }

    if (this->mode == this->ModeList[this->Modes::newtemp])
    {
        if (this->args.size() > 2)
        {
            this->type = this->args[2];
            if (this->type == this->TypeList[this->Types::makefile])
            {
                this->createMakeTemplate();
            }
        }
        else
        {
            std::cout << this->ErrorList[this->ErrorType::TypeError] << std::endl;
            return;
        }
    }
    else if (this->mode == this->ModeList[this->Modes::help])
    {
        this->helpMode();
    }
}

void Ctm::createMakeTemplate()
{
    std::string command;
    this->MakeTemplate.dirs.push_back(this->DirList[this->DirType::bin]);
    this->MakeTemplate.dirs.push_back(this->DirList[this->DirType::include]);
    this->MakeTemplate.dirs.push_back(this->DirList[this->DirType::lib]);
    this->MakeTemplate.dirs.push_back(this->DirList[this->DirType::src]);

    this->MakeTemplate.binDir.push_back("Makefile");
    this->MakeTemplate.srcDir.push_back("main.cpp");

    // cretaing all folders
    for (int i = 0; i < this->MakeTemplate.dirs.size(); i++)
    {
        command = this->CreateDirCommand + " " + this->MakeTemplate.dirs[i];
        system(command.c_str());
    }

    // create bin files
    for (int i = 0; i < this->MakeTemplate.binDir.size(); i++)
    {
        command = this->CreateFileCommand + " ./bin/" + this->MakeTemplate.binDir[i];
        system(command.c_str());
    }

    // create src files
    for (int i = 0; i < this->MakeTemplate.srcDir.size(); i++)
    {
        command = this->CreateFileCommand + " ./src/" + this->MakeTemplate.srcDir[i];
        system(command.c_str());
    }

    // Write Main.cpp
    Ctm::writeFile("./src/main.cpp", this->cppFileString);

    // Write Makefile
    Ctm::writeFile("./bin/Makefile", this->makeFileString);
}

void Ctm::helpMode()
{   
    std::cout << "" << std::endl;
    std::cout << "Creating New Template: Ctm new [Type]" << std::endl;
    std::cout << "Types: " << std::endl;
    for (const auto& pair : TypeList) {
        std::cout << "    " << pair.second << std::endl;
    }
}