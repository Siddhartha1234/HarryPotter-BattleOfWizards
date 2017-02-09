#pragma once

#include "GLTexture.hpp"
#include <string>
namespace GameEngine {
    class ImageLoader
    {
    public:
        static GLTexture loadPNG(std::string filePath);
    };

}
