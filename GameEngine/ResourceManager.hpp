#pragma once

#include <string>

#include "TextureCache.hpp"
namespace GameEngine {
    class ResourceManager
    {
    public:
        static GLTexture getTexture(std::string texturePath);

    private:
        static TextureCache _textureCache;
    };

}
