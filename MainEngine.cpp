#include <string>
#include <iostream>
#include "GameEngine/GameEngine.hpp"
#include "MainEngine.hpp"

MainEngine::MainEngine() :
	_screenWidth(800),
	_screenHeight(600),
	_time(0),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f),
	_camera.init(_screenWidth,_screenHeight)
{
}


MainEngine::~MainEngine(){
	for(int i=0; i < _sprites.size(); i++){
		delete _sprites[i];
	}
}

void MainEngine::run(){
	initSystems();

	_sprites.push_back(new GameEngine::Sprite());
	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Jump.png");

	_sprites.push_back(new GameEngine::Sprite());
	_sprites.back()->init(0.0f, 0.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Jump.png");

	gameLoop();
}

void MainEngine::initSystems(){

    GameEngine::init();
    _window.create("Game" , _screenWidth,_screenHeight,0);


	initShaders();

}

void MainEngine::initShaders(){
	_colorProgram.compileShaders("Shaders/colorShading.vert","Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainEngine::gameLoop(){
	while(_gameState != GameState::EXIT){

        float startTicks = SDL_GetTicks();

        processInput();
		_time += 0.01;

		_camera.update();
		drawScene();
		calculateFPS();



		static int frameCounter = 0;
		frameCounter ++;
		if(frameCounter == 10) {
            std::cout << _fps <<std::endl;
            frameCounter = 0;
		}

        float frameTicks = SDL_GetTicks() - startTicks;

        if(1000.0f / _maxFPS > frameTicks) {
            SDL_Delay(1000.0f / _maxFPS  - frameTicks);
        }
	}
}

void MainEngine::processInput(){
	SDL_Event evnt;
	while(SDL_PollEvent(&evnt)){
		switch(evnt.type){
		case SDL_QUIT:
			_gameState= GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			if(evnt.key.keysym.sym == SDLK_ESCAPE){
				_gameState= GameState::EXIT;
			}
			break;
		}
	}
}

void MainEngine::drawScene(){
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();

		glActiveTexture(GL_TEXTURE0);

		GLint textureLocation= _colorProgram.getUniformLocation("fragTexture");
		glUniform1i(textureLocation, 0);

		GLint timeLocation= _colorProgram.getUniformLocation("time");
		glUniform1f(timeLocation, _time);

        GLint pLocation = _colorProgram.getUniformLocation("P");
        glm :: mat4
		// Draw the sprite
		for(int i=0; i < _sprites.size(); i++){
			_sprites[i]->draw();
		}

		glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unuse();

	// Swap buffers
    _window.swapBuffer();
}

void MainEngine::calculateFPS() {
    static const int NUM_SAMPLES = 10;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame =0;

    static float prevTicks = SDL_GetTicks();

    float currentTicks;
    currentTicks= SDL_GetTicks();


    _frameTime = currentTicks - prevTicks;
    frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;
    int count;

    currentFrame++;

    if(currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    }
    else {
        count = NUM_SAMPLES;
    }

    float frameTimeAverage = 0;
    for(int i=0 ; i < count ;i++) {
        frameTimeAverage += frameTimes[i];
    }
    frameTimeAverage /= count;


    if(frameTimeAverage >0) {
        _fps = 1000.0f / frameTimeAverage;
    }
    else {
        _fps = 60.0f;
    }

}
