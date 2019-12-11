#include "Menu.h"
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8

void Menu::Initialize() {
	Mix_HaltMusic(); //stop the music
	fontTextureID = Util::LoadTexture("images/pixel_font.png");
	state.nextLevel = -1;
}
void Menu::Update(float deltaTime) {
	
}
void Menu::Render(ShaderProgram* program) {
	/*state.map->Render(program);*/
	//player.Render(program);
	Util::DrawText(program, fontTextureID, "WHY did the", 1.0f, -0.1f, glm::vec3(-0.3f, -0.75f, 0));
	Util::DrawText(program, fontTextureID, "CHICKEN", 1.0f, -0.1f, glm::vec3(2.0f,-2.25f, 0));
	Util::DrawText(program, fontTextureID, "cross the GPU?", 1.0f, -0.15f, glm::vec3(-0.4f, -3.50f, 0));
	Util::DrawText(program, fontTextureID, "< Press Enter >", 0.6f, -0.05f, glm::vec3(1.4f, -6.50f, 0));
}