#include "Scene.h"
class Level1 : public Scene {
	void drawInfo(ShaderProgram* program);
	glm::vec3 textPosition;
	glm::vec3 textDistanceFromPlayer;
public:
	static const int ENEMY_COUNT = 25;
	Entity enems[ENEMY_COUNT];
	//GLuint fontTextureID;
	//Level1(GLuint* playerTexID, GLuint* bgTextID);
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render(ShaderProgram* program) override;
	void initializePlayer();
	void initializeEnemies();
	void updateText();
};