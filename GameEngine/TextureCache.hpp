#pragma once

#include <map>
#include "GLTexture.hpp"
namespace GameEngine {
    class TextureCache
    {
    public:
        TextureCache(void);
        ~TextureCache(void);

        GLTexture getTexture(std::string texturePath);

    private:
        std::map<std::string, GLTexture> _textureMap;
    };

}
