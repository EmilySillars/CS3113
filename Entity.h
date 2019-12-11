#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>
//#include <SDL_image.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Map.h"
#include <SDL_mixer.h>

enum EntityType { PLAYER, PLATFORM, ENEMY, BONE, COLLIDER };
enum AnimationState { UP_DOWN, LEFT, RIGHT, LEFT_IDLE, RIGHT_IDLE };
enum AIState { MOVING, PICKING }; //add AI states
enum AIType { MAN };

class Entity {
public:
    
    EntityType entityType;
    bool isStatic;
    bool isActive;
	
	Entity* collider;
	float colliderXOffset;
	float colliderYOffset;
    
	//AI
	AIState aiState;
	AIType aiType;
	float timer;
	glm::vec3 aiDirection;

    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    
    float width;
    float height;
    

	//sounds
	Mix_Chunk *dieSound;
	Mix_Chunk* dieSoundAlt;

	//animation
	float speed; //animation speed!!
	AnimationState animationState;
	glm::vec3 spritePosition;
	float spriteWidthFB;
	float spriteHeightFB;
	float spriteWidthW;
	float spriteHeightW;
	int cols; //# of collumns in sprite sheet
	int rows; //# of rows in sprite sheet
	int colsWalk; //# of collumns in sprite sheet
	int rowsWalk; //# of rows in sprite sheet
	//arrays of indices
	int *idleRight;
	int *idleLeft;
	int* idleDown;
	int* idleUp;
	int *walkRight;
	int *walkLeft;
	int* walkUp;
	int* walkDown;
	int *currentAnim;
	int animFrames; //# of frames in an animation
	int animFramesWalk; //# of frames in an animation
	int animIndex; //index of current animation frame
	float animTime;

    //more AI
	void AIUpdate(Entity player, float deltaTime); 
	void AIMan(Entity& player, float deltaTime);

	int lives;

    GLuint textureID;
	GLuint textureIDIdle;
	GLuint textureIDWalk;
    
    Entity();
        
    void Update(float deltaTime, Entity player, Entity *objects, int objectCount, Map *map);
	//void Update(float deltaTime, Entity player, Entity *objects, int objectCount, Entity *enemies, int enemyCount); //added in player so AI can see it
    void Render(ShaderProgram *program);
	void simpleRender(ShaderProgram* program);
    
    void Jump();

	//animation
	void DrawSpriteFromTextureAtlas(ShaderProgram *program, int index, GLuint textureID, int rows, int cols, float spriteWidth, float spriteHeight);
	void UpdateAnimation(float deltaTime);

	//collision detection  
	//mine
	static bool pointBoxCollision(glm::vec3 point, Entity box);
	static bool verticalSegmentBoxOverlap(glm::vec3 start, glm::vec3 end, Entity box);
	static bool horizontalSegmentBoxOverlap(glm::vec3 start, glm::vec3 end, Entity box);
	//my collider
	void updateCollider();
	//from class
	bool CheckCollision(Entity other);
	int CheckCollisionsX(Entity *objects, int objectCount);
	int CheckCollisionsY(Entity *objects, int objectCount);
	//map collision detection
	void CheckCollisionsX(Map* map);
	void CheckCollisionsY(Map* map);

	//collision flags
    bool collidedTop;
    bool collidedBottom;
    bool collidedLeft;
    bool collidedRight;
    
};



