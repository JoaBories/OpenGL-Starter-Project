#include "ShaderFiles.h"

#include <iostream>
#include <fstream>

using std::ifstream;
using std::cerr;
using std::cout;
using std::endl;

std::string ShaderFiles::ReadFile(std::string filepath)
{
    std::string Shader;
    std::string line;

    //Open file of this name
    ifstream myFile;
    myFile.open(filepath);

    //Check for errors
    if (myFile.fail()) {
        cerr << "Error - Failed to open " << filepath << endl;
    }
    else
    {
        cout << "INFO - Success opening " << filepath << endl;
    }

    while (std::getline(myFile, line)) {
        Shader += line + "\n";
    }

    myFile.close();

    return Shader;
}
