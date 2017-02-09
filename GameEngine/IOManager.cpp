#include "IOManager.hpp"

#include <fstream>
namespace GameEngine {
        bool IOManager::readFileToBuffer(std::string filepath, std::vector<unsigned char>& buffer){
        std::ifstream file(filepath, std::ios::binary);
        if(file.fail()){
            perror(filepath.c_str());
            return false;
        }

        // ans Ende der Datei gehen
        file.seekg(0, std::ios::end);

        // Dateigr��e
        int fileSize= file.tellg();

        // An Anfang der Datei zur�cksetzen
        file.seekg(0, std::ios::beg);

        // nicht unbedingt n�tig
        // Reduce the file size by any header bytes that might be present
        fileSize -= file.tellg();

        buffer.resize(fileSize);
        file.read((char *)&(buffer[0]),fileSize);
        file.close();

        return true;
    }
}
