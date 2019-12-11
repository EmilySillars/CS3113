#include "Scene.h"
#include "Util.h"
class Win : public Scene {
public:
	GLuint fontTextureID;
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render(ShaderProgram* program) override;
};

