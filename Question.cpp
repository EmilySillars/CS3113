#include "Question.h"
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8

void Question::Initialize() {
	fontTextureID = Util::LoadTexture("images/pixel_font.png");
	state.nextLevel = -1;
}
void Question::Update(float deltaTime) {

}
void Question::Render(ShaderProgram* program) {
	Util::DrawText(program, fontTextureID, "...Across  the GPU?", 0.8f, -0.05f, glm::vec3(-2.0f, -0.75f, 0));
	Util::DrawText(program, fontTextureID, "Nothing's over there.", 0.8f, -0.05f, glm::vec3(-2.0f, -2.25f, 0));
	Util::DrawText(program, fontTextureID, "Seriously, nothing.", 0.8f, -0.05f, glm::vec3(-2.0f, -3.50f, 0));
	Util::DrawText(program, fontTextureID, "You still wanna go?", 0.6f, -0.05f, glm::vec3(0.0f, -6.50f, 0));
}