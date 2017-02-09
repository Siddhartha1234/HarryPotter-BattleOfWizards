#include "TextureCache.hpp"

#include <iostream>

#include "ImageLoader.hpp"
namespace GameEngine {
    TextureCache::TextureCache(void)
    {
    }


    TextureCache::~TextureCache(void)
    {
    }

    GLTexture TextureCache::getTexture(std::string texturePath){

        // auto statt std::map<std::string, GLTexture>::iterator

        //lookup the texutre and see if it's in the map
        auto mit= _textureMap.find(texturePath);

        //check if it's not in the map
        if(mit == _textureMap.end()){
            GLTexture newTexture= ImageLoader::loadPNG(texturePath);

            // insert the texture into the map
            _textureMap.emplace(texturePath, newTexture);

            std::cout << "Loaded Texture!"<<std::endl;
            return newTexture;
        }

        std::cout<< "Used Cached Texture!"<<std::endl;
        return mit->second;

    }
}
