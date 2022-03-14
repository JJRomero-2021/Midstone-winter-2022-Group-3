#ifndef SCENE0_H
#define SCENE0_H
#include "Scene.h"
#include <SDL.h>
#include "Vector.h"
#include "Matrix.h"
#include "Body.h"
#include "SceneManager.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class GameObject;
class PhysicsObject;
class Mesh;
class Shader;
class Texture;

class Scene0 : public Scene {
private:
	Body* spaceShip, * planet, * obstacle;
	GameObject* gameObject;
	Vec3 lightSource;
	Mesh* meshPtr;
	Shader* shaderPtr;
	Texture* texturePtr;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	SceneManager* scene;
	SDL_Window* window;
	SDL_Renderer* renderer;


public:
	explicit Scene0(SDL_Window* sdlWindow, SceneManager* scene);
	virtual ~Scene0();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE0_H