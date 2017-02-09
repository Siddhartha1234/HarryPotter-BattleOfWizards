#include "Errors.hpp"

#include <cstdlib>

#include <iostream>
#include <SDL2/SDL.h>

namespace GameEngine {
    void fatalError(std::string errorString){
        std::cout<<errorString<<std::endl;
        std::string tmp;
        std::cin >> tmp;
        std::cout<<"Press any key to quit"<<std::endl;
        SDL_Quit();
        exit(1);
    }

}
