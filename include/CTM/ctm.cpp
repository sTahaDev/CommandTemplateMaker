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

    this->cppFilePath = "../include/Template/main.cpp";
    this->makefileFilePath = "../include/Template/Makefile";
}

void Ctm::writeFile(const std::string &path, const std::string &data)
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
std::string Ctm::readFile(const std::string &path){
    std::ifstream file(path);
    // Dosya var mı kontrol et
    if (!file) {
        std::cerr << "File Cant Open!" << std::endl;
        std::exit(0);
    }
    // Dosyadan veriyi oku
    std::string data = "";
    std::string word;
    while (std::getline(file, word)) {
        data += word + "\n";
    }

    // Dosyayı kapat
    file.close();
    return data;

}
void Ctm::run()
{
    //Modu Alma
    if (this->args.size() > 1)
        this->mode = this->args[1];
    else
    {
        std::cout << this->ErrorList[this->ErrorType::ModeError] << std::endl;
        return;
    }
    //Mod İşlemleri
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
        std::filesystem::create_directory(this->MakeTemplate.dirs[i]);
    }

    // create bin files
    for (int i = 0; i < this->MakeTemplate.binDir.size(); i++)
    {
        command = "./bin/" + this->MakeTemplate.binDir[i];
        std::ofstream file(command.c_str());
        file.close();
    }

    // create src files
    for (int i = 0; i < this->MakeTemplate.srcDir.size(); i++)
    {
        command = "./src/" + this->MakeTemplate.srcDir[i];
        std::ofstream file(command.c_str());
        file.close();
    }

    // Write Main.cpp
    Ctm::writeFile("./src/main.cpp", this->readFile(cppFilePath));

    // Write Makefile
    Ctm::writeFile("./bin/Makefile", this->readFile(makefileFilePath));
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