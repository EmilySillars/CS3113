#include "Win.h"
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8
//unsigned int level1_data[] =
//{
// 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
// 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
// 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
//};

void Win::Initialize() {
	winSound = Mix_LoadWAV("sounds/win.wav");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	fontTextureID = Util::LoadTexture("images/pixel_font.png");
	Mix_PlayChannel(-1, winSound, 0); //play chunk once and do not loop

	state.nextLevel = -1;
}
void Win::Update(float deltaTime) {
}
void Win::Render(ShaderProgram* program) {
	Util::DrawText(program, fontTextureID, "You Made it!", 1.0f, -0.1f, glm::vec3(0.4f, -1.75f, 0));
	//Util::DrawText(program, fontTextureID, "Press enter for menu.", 0.4f, -0.05f, glm::vec3(1.7f, -5.0f, 0));
	//Util::DrawText(program, fontTextureID, "< Press Enter >", 0.4f, -0.05f, glm::vec3(2.5f, -5.80f, 0));
	//Util::DrawText(program, fontTextureID, "...WHY?", 0.7f, -0.1f, glm::vec3(1.8f, -1.75f, 0));
	//Util::DrawText(program, fontTextureID, "WHY DI", 0.7f, -0.1f, glm::vec3(3.2f, -2.75f, 0));
	//Util::DrawText(program, fontTextureID, "... WHY?", 0.7f, -0.1f, glm::vec3(1.8f, -3.75f, 0));
	Util::DrawText(program, fontTextureID, "< Press Enter >", 0.4f, -0.05f, glm::vec3(2.5f, -5.80f, 0));
}