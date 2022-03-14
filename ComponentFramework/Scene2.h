#ifndef SCENE2_H
#define SCENE2_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
#include "SceneManager.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Mesh;
class Shader;
class Texture;

class Scene2 : public Scene {
private:
	Mesh* meshPtr;
	Shader* shaderPtr;
	Texture* texturePtr;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	SceneManager* scene;
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	explicit Scene2(SDL_Window* sdlWindow, SceneManager* scene);
	virtual ~Scene2();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE2_H