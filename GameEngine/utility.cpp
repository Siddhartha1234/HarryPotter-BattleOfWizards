#include "utility.hpp"

#include "Errors.hpp"

#include <string>
#include <fstream>
#include <iostream>
namespace GameEngine {
        const std::string readFile(const std::string &filename){
        // Datei öffnen
        std::string fileContent;
        std::ifstream file(filename);
        //file.open(filename.c_str(),std::ios_base::in);
        if(!file.fail()){
            // Dateinhalt in Variable "fileContent" speichern
            // erstes Argument gibt an, wo gestartet werden soll
            // zweites Argument: lesen bis Nullterminator gelesen wird
            fileContent.assign(( std::istreambuf_iterator<char>(file) ), std::istreambuf_iterator<char>() );
        } else {
            perror(filename.c_str());
            fatalError("Error opening file: "+filename);
        }
        file.close();
        return fileContent;
    }
}
