#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>

#include "GameEngine/Sprite.hpp"
#include "GameEngine/GLSLProgram.hpp"
#include "GameEngine/GLTexture.hpp"

#include "GameEngine/Window.hpp"
#include "GameEngine/Camera2D.hpp"



enum class GameState { MAIN_MENU, PLAY, EXIT };

class MainEngine
{
public:
	MainEngine();
	~MainEngine();
	void run();

private:
	GameEngine::Window _window;
	int _screenWidth;
	int _screenHeight;
	float _fps;
	float _frameTime;
	float _time;
    float _maxFPS;
	GameState _gameState;

	std::vector<GameEngine::Sprite*> _sprites;

	GameEngine::Camera2D _camera;

	GameEngine::GLSLProgram _colorProgram;


	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawScene();
	void calculateFPS();
};

