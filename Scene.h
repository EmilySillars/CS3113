#pragma once
#define GL_SILENCE_DEPRECATION
#ifdef _WINDOWS
#include <GL/glew.h>
#endif
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Util.h"
#include "Entity.h"
#include "Map.h"
#include <SDL_mixer.h>
struct GameState {
	Entity player;
	//Entity dummy;
	Entity* enemies;
	Map *map;
	Map *fg_2;
	int nextLevel;
};

class Scene {
public:
	GLuint enemyTextureID;
	GLuint mapTextureID;
	GLuint fontTextureID;

	Entity sign;
	Entity bg;
	//Entity collider;
	Mix_Music *music;
	Mix_Chunk *winSound;
	Mix_Chunk *loseSound;
	float cameraXMax;
	float cameraXMin;
	float cameraYMax;
	float cameraYMin;
	GameState state;
	virtual void Initialize() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(ShaderProgram *program) = 0;
};
