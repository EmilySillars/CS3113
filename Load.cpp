#include "Load.h"
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8

void Load::Initialize() {
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	fontTextureID = Util::LoadTexture("images/pixel_font.png");
	state.nextLevel = -1;
	music = Mix_LoadMUS("sounds/chickens_load.mp3");
	Mix_PlayMusic(music, -1); //play music and loop forever
	Mix_VolumeMusic(3 * (MIX_MAX_VOLUME / 4)); //set volume from 0 10 128
}
void Load::Update(float deltaTime) {
}
void Load::Render(ShaderProgram* program) {
	Util::DrawText(program, fontTextureID, "LOADING...", 1.5f, -0.2f, glm::vec3(-0.8f, -1.75f, 0));
	Util::DrawText(program, fontTextureID, "This is fun, isn't it?", 0.8f, -0.2f, glm::vec3(-1.0f, -5.80f, 0));
	state.nextLevel = 0;
}