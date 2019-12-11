#include "Scene.h"
#include "Util.h"
class Menu : public Scene {
public:
	GLuint fontTextureID;
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render(ShaderProgram* program) override;
};