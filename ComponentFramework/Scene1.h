#ifndef SCENE1_H
#define SCENE1_H
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

class Scene1 : public Scene {
private:
	Mesh *meshPtr;
	Shader *shaderPtr;
	Texture *texturePtr;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	SceneManager* scene;
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	explicit Scene1(SDL_Window* sdlWindow, SceneManager* scene);
	virtual ~Scene1();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE1_H