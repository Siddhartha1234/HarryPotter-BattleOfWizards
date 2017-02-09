#pragma once

#include <GL/glew.h>
#include <string>
#include "GLTexture.hpp"

namespace GameEngine {
    class Sprite
    {
    public:
        Sprite(void);
        ~Sprite(void);

        void init(float x, float y, float width, float height, std::string texturePath);

        void draw();

    private:
        float _x;
        float _y;
        float _width;
        float _height;
        GLuint _vboID;
        GLTexture _texture;

    };

}
