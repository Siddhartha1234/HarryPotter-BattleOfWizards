#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace GameEngine {
    class Camera2D
    {
    public:
        Camera2D();
        ~Camera2D();

        void init(int screenWidth,int screenHeight);
        void update;
        void setPosition(const flm::vec2& newPosition) { _position = newPosition;}
        void setScale(float newScale) {_scale = newScale;}
        float getScale () { return _scale;}
        glm::vec2 getPosition() { return _position;}

        glm::mat4 getOrthoMatrix() {return _cameraMatrix;}
    private:
        bool _needsMatrixUpdate;
        glm::vec2 _position;
        glm:mat4 _cameraMatrix;
        glm::mat4 _orthoMatrix;
        float _scale;
        int _screenWidth ,_screenHeight;
    }
}
