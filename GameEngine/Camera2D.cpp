#include "GameEngine/Camera2D.hpp"
namespace GameEngine{
    Camera2D::Camera2D() : _position(0.0f , 0.0f) ,_cameraMatrix(1.0f),_scale(1.0f) ,_needsMatrixUpdate(true)
    {

    }

    Camera2D :: ~Camera2D() {

    }

    void Camera2D::init(int screenWidth,int screenHeight)
    {
        _screenHeight = screenHeight;
        _screenWidth = screenWidth;
        _orthoMatrix = glm::ortho(0.0f, (float) _screenWidth , 0.0f , (float) _screenHeight);

    }
    void Camera2D::update() {
        if(_needsMatrixUpdate) {
            glm::vec3 translate(-_position.x,-position.y,0.0f);
            glm:: vec3 scale(_scale,_scale, 0.0f);
            _cameraMatrix = glm::translate(_orthoMatrix ,translate);
            _cameraMatrix = glm :: scale(_cameraMatrix , scale);
        }
    }

}
