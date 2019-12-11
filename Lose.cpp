#include "Lose.h"
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8

void Lose::Initialize() {
	Mix_HaltMusic(); //stop the music
	loseSound = Mix_LoadWAV("sounds/lose.wav");
	Mix_PlayChannel(-1, loseSound, 0); //play chunk once and do not loop
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	fontTextureID = Util::LoadTexture("images/pixel_font.png");
	state.nextLevel = -1;
}
void Lose::Update(float deltaTime) {
}
void Lose::Render(ShaderProgram* program) {
	Util::DrawText(program, fontTextureID, "Looks like the", 0.7f, -0.1f, glm::vec3(1.4f, -0.75f, 0));
	Util::DrawText(program, fontTextureID, "CHICKEN", 0.7f, -0.1f, glm::vec3(3.2f, -1.75f, 0));
	Util::DrawText(program, fontTextureID, "never did", 0.7f, -0.1f, glm::vec3(2.2f, -2.75f, 0));
	Util::DrawText(program, fontTextureID, "cross the GPU...", 0.7f, -0.1f, glm::vec3(0.6f, -3.75f, 0));
	Util::DrawText(program, fontTextureID, "< Press Enter >", 0.4f, -0.05f, glm::vec3(2.5f, -5.80f, 0));
}