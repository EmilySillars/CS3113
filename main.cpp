#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"


#include "Util.h"
#include "Scene.h"
#include "Level1.h"
#include "Menu.h"
#include "Lose.h"
#include "Win.h"
#include "Load.h"
#include <thread>
#include "Entity.h"
#include "Map.h"
#include "Question.h"

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

//we hardcoded 0 in update so fix that
#define ENEMY_COUNT 1

#define MAIN_MENU 0
#define LEVEL_1 1
#define LOSE 2
#define WIN 3
#define LOAD 4
#define QUESTION 5

//if we wanted fonts
GLuint fontTextureID;

GLuint  * playerTexID = new GLuint;
GLuint  * bgTextID = new GLuint;
Entity test;
Scene* currentScene;
Scene* sceneList[6];

void LoadImages() {

	sceneList[1]->bg.textureID = Util::LoadTexture("images/tileMap_4200_6000_paths_FINAL.jpg");
	sceneList[1]->enemyTextureID = Util::LoadTexture("images/man_sheet.png");
	sceneList[1]->sign.textureID = Util::LoadTexture("images/nothing_sign2.png");

	sceneList[1]->state.player.textureID = Util::LoadTexture("images/chicken_front_back_skate.png");
	sceneList[1]->state.player.textureIDIdle = sceneList[1]->state.player.textureID;
	sceneList[1]->state.player.textureIDWalk = Util::LoadTexture("images/chicken_side_skate_sheet3.png");

	sceneList[1]->fontTextureID = Util::LoadTexture("images/pixel_font.png");
	sceneList[1]->mapTextureID = Util::LoadTexture("images/dummy5.jpg");
}

void SwitchToScene(Scene* scene) {
	currentScene = scene;
	currentScene->Initialize();
}


void Initialize() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); //audio AND video
    //displayWindow = SDL_CreateWindow("Why did the chicken cross the GPU?", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
	//displayWindow = SDL_CreateWindow("Why did the chicken cross the GPU?", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 420, 600, SDL_WINDOW_OPENGL);
	displayWindow = SDL_CreateWindow("Why did the chicken cross the GPU?", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 840, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    //glViewport(0, 0, 640, 480);
	//glViewport(0, 0, 420, 600);
	glViewport(0, 0, 840, 600);
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");

	fontTextureID = Util::LoadTexture("images/pixel_font.png");
	
    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    /*projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);*/
	//projectionMatrix = glm::ortho(-4.2f, 4.2f, -6.0f, 6.0f, -1.0f, 1.0f);
	projectionMatrix = glm::ortho(-8.4f, 8.4f, -6.0f, 6.0f, -1.0f, 1.0f);

    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    program.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    glUseProgram(program.programID);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Start Audio
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

	*playerTexID = 0;
	*bgTextID = 0;

	sceneList[0] = new Menu();
	sceneList[1] = new Level1();
	sceneList[LOAD] = new Load();
	sceneList[QUESTION] = new Question();
	sceneList[WIN] = new Win();
	sceneList[LOSE] = new Lose();
	//sceneList[4]->state.player.textureID = Util::LoadTexture("images/chicken_sheet2.png");
	SwitchToScene(sceneList[4]);
}

void ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                gameIsRunning = false;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        currentScene->state.player.Jump();
                        break;
					case SDLK_k:
						currentScene->state.player.lives --;
						break;
					case SDLK_l:
						/*if (currentScene != sceneList[MAIN_MENU] &&
							currentScene != sceneList[LOSE]) {
							currentScene->state.nextLevel = WIN;
						}*/
						currentScene->state.player.lives++;
						break;
					case SDLK_p:
						currentScene->state.enemies[0].aiDirection = glm::vec3(0, 0, 0);
						break;
					case SDLK_RETURN:
						if (currentScene == sceneList[MAIN_MENU]) {
							//glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
							currentScene->state.nextLevel = QUESTION;
						}
						else if (currentScene == sceneList[QUESTION]) {
							currentScene->state.nextLevel = LEVEL_1;
						}
						else if (currentScene == sceneList[WIN]) {
							currentScene->state.nextLevel = MAIN_MENU;
						}
						else if (currentScene == sceneList[LOSE]) {
							currentScene->state.nextLevel = MAIN_MENU;
						}
						break;
                }
                break;
        }
    }
    
   currentScene->state.player.velocity.x = 0;
   currentScene->state.player.velocity.y = 0;
    
    // Check for pressed/held keys below
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    if (keys[SDL_SCANCODE_A])
    {
		/*currentScene->state.dummy.position = currentScene->state.player.position;
		currentScene->state.dummy.position.x = (currentScene->state.dummy.position.x -0.15);
		currentScene->state.dummy.CheckCollisionsX(currentScene->state.map);
		if (!currentScene->state.dummy.collidedLeft) {
			currentScene->state.player.velocity.x = -6.6f;
		}*/

		currentScene->state.player.velocity.x = -6.6f;
		
    }
    else if  (keys[SDL_SCANCODE_D])
    {
		currentScene->state.player.velocity.x = 6.6f;
    }
	else if (keys[SDL_SCANCODE_W])
	{
		currentScene->state.player.velocity.y = 6.6f;
	}
	else if (keys[SDL_SCANCODE_S])
	{
		currentScene->state.player.velocity.y = -6.6f;
	}
}

#define FIXED_TIMESTEP 0.0166666f
float lastTicks = 0;
float accumulator = 0.0f;

void Update() {
	//if (currentScene == sceneList[MAIN_MENU]) {
	//	if (currentScene->bgTextureID != 0) {
	//		sceneList[1]->bg.textureID = currentScene->bg.textureID;
	//		//sceneList[1]->bgTextID = bgTextID;
	//		//test.textureID = *bgTextID;
	//		currentScene->state.nextLevel = LEVEL_1;
	//	}
	//}
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    
    deltaTime += accumulator;
    if (deltaTime < FIXED_TIMESTEP) {
        accumulator = deltaTime;
        return;
    }
    
    while (deltaTime >= FIXED_TIMESTEP) {
        
		currentScene->Update(FIXED_TIMESTEP);
        
        deltaTime -= FIXED_TIMESTEP;
    }
    
    accumulator = deltaTime;

	viewMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	if (currentScene->state.player.position.x > currentScene->cameraXMin &&
		currentScene->state.player.position.x < currentScene->cameraXMax) {
			viewMatrix = glm::translate(viewMatrix,
				glm::vec3(-currentScene->state.player.position.x, 3.75, 0));
			/*viewMatrix = glm::translate(viewMatrix,
				glm::vec3(-currentScene->state.player.position.x, -currentScene->state.player.position.y, 0));*/
	}
	else if (currentScene->state.player.position.x > currentScene->cameraXMax) {
		viewMatrix = glm::translate(viewMatrix,
			glm::vec3(-currentScene->cameraXMax, 3.75, 0));
	}
	else if (currentScene->state.player.position.x < currentScene->cameraXMin) {
		viewMatrix = glm::translate(viewMatrix,
			glm::vec3(-currentScene->cameraXMin, 3.75, 0));
	}
	else {
		viewMatrix = glm::translate(viewMatrix, glm::vec3(-5, 3.75, 0));
	}

	
	if (currentScene->state.player.position.y > currentScene->cameraYMin) {
		//if (currentScene->state.player.position.y > 0) {
			viewMatrix = glm::translate(viewMatrix, glm::vec3(0, -(currentScene->state.player.position.y+3), 0));
		//}
		/*else {
			viewMatrix = glm::translate(viewMatrix, glm::vec3(0, -(currentScene->state.player.position.y), 0));
		}*/
	}
}




void Render() {
    glClear(GL_COLOR_BUFFER_BIT);

	program.SetViewMatrix(viewMatrix);

	currentScene->Render(&program);
	//if (currentScene == sceneList[1]) {
	//	test.simpleRender(&program);
	//}
 //   
    SDL_GL_SwapWindow(displayWindow);
}

void Shutdown() {
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    Initialize();
	//std::thread first(LoadImages);
	if (gameIsRunning) {
		//ProcessInput();
		Update();
		Render();
		LoadImages();
		currentScene->state.nextLevel = MAIN_MENU;
		//bg.textureID = Util::LoadTexture("images/bg.png"); 
	}
    while (gameIsRunning) {
		if (currentScene->state.nextLevel >= 0) SwitchToScene(sceneList[currentScene->state.nextLevel]);

        ProcessInput();
        Update();
        Render();
    }
    
    Shutdown();
    return 0;
}
