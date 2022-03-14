#include <glew.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Debug.h"
#include "Scene0.h"
#include "GameObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "Physics.h"
#include "Timer.h"

using namespace std;

Scene0::Scene0(SDL_Window* sdlWindow_, SceneManager* scene_)
{
	window = sdlWindow_;
	planet = new Body(Vec3(10.0f, 20.0f, 0.0f), Vec3(11.3f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	spaceShip = new Body(Vec3(0.0f, 7.8f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	obstacle = new Body(Vec3(15.0f, 25.0f, 0.0f), Vec3(11.3f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0::~Scene0() 
{
	delete spaceShip;
	delete planet;
	delete obstacle;
}

bool Scene0::OnCreate() 
{
	renderer = SDL_GetRenderer(window);

	if (!renderer) {

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	}

	if (!renderer) {

		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;

		return false;

	}
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(-10.0f, 30.0f, -10.0f, 40.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	IMG_Init(IMG_INIT_PNG);

	SDL_Surface* planetImage = IMG_Load("textures/earth.png");
	SDL_Texture* planetTexture = SDL_CreateTextureFromSurface(renderer, planetImage);
	if (planetImage == nullptr)
	{
		printf("Can't open textures/earth.png\n");
		return false;
	}

	SDL_Surface* obstacleImage = IMG_Load("textures/Obstacle.png");
	SDL_Texture* obstacleTexture = SDL_CreateTextureFromSurface(renderer, obstacleImage);
	if (obstacleImage == nullptr)
	{
		printf("Can't open textures/Obstacle.png\n");
		return false;
	}

	SDL_Surface* spaceShipImage = IMG_Load("textures/Spaceship.png");
	SDL_Texture* spaceShipTexture = SDL_CreateTextureFromSurface(renderer, spaceShipImage);
	if (spaceShipImage == nullptr)
	{
		printf("Can't open textures/Spaceship.png\n");
		return false;
	}
	planet->setTexture(planetTexture);
	SDL_FreeSurface(planetImage);
	spaceShip->setTexture(spaceShipTexture);
	SDL_FreeSurface(spaceShipImage);
    obstacle->setTexture(obstacleTexture);
	SDL_FreeSurface(obstacleImage);
	return true;
}

void Scene0::HandleEvents(const SDL_Event& sdlEvent) 
{
	if (sdlEvent.type == SDL_EventType::SDL_KEYDOWN)
	{
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D)
		{
			spaceShip->ApplyForce(Vec3(5.0f, 0.0f, 0.0f));
			spaceShip->isMoving(true);
		}
	}
	else if (sdlEvent.type == SDL_EventType::SDL_KEYUP)
	{

		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D)
		{
			spaceShip->ApplyForce(Vec3(0.0f, 0.0f, 0.0f));
		}
	}
	if (sdlEvent.type == SDL_EventType::SDL_KEYDOWN)
	{
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A)
		{
			spaceShip->ApplyForce(Vec3(-5.0f, 0.0f, 0.0f));
			spaceShip->isMoving(true);

		}
	}
	else if (sdlEvent.type == SDL_EventType::SDL_KEYUP)
	{
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A)
		{
			spaceShip->ApplyForce(Vec3(0.0f, 0.0f, 0.0f));
		}
	}

	if (sdlEvent.type == SDL_EventType::SDL_KEYDOWN)
	{
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_W)
		{
			spaceShip->ApplyForce(Vec3(0.0f, 5.0f, 0.0f));
			spaceShip->isMoving(true);

		}
	}
	else if (sdlEvent.type == SDL_EventType::SDL_KEYUP)
	{
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_W)
		{
			spaceShip->ApplyForce(Vec3(0.0f, 0.0f, 0.0f));
		}
	}


	if (sdlEvent.type == SDL_EventType::SDL_KEYDOWN)
	{
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_S)
		{
			spaceShip->ApplyForce(Vec3(0.0f,-5.0f, 0.0f));
			spaceShip->isMoving(true);

		}
	}
	else if (sdlEvent.type == SDL_EventType::SDL_KEYUP)
	{
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_S)
		{
			spaceShip->ApplyForce(Vec3(0.0f, 0.0f, 0.0f));
		}
	}

	else if (sdlEvent.type == SDL_USEREVENT)
	{
		printf("%d %s\n",sdlEvent.user.data1, sdlEvent.user.data2);
	}
}

void Scene0::Update(const float deltaTime) 
{
	spaceShip->Update(deltaTime);
	Vec3 origin(0.0f, 0.0f, 0.0f);
	if (VMath::distance(spaceShip->getPos(), origin) < 1.5f)
	{
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event));
		event.type = scene->getChangeScene();
		event.user.code = 1;
		event.user.data1 = nullptr;
		event.user.data2 = nullptr;
		SDL_PushEvent(&event);
	}
}

void Scene0::Render() const 
{
	/// Clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 50, 0);
	SDL_RenderClear(renderer);

	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;

	/// Draw your scene here
	screenCoords = projectionMatrix * planet->getPos();
	SDL_QueryTexture(planet->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 4;
	square.h = h / 4;
	SDL_RenderCopyEx(renderer, planet->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * obstacle->getPos();
	SDL_QueryTexture(obstacle->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 4;
	square.h = h / 4;
	SDL_RenderCopyEx(renderer, obstacle->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	
	screenCoords = projectionMatrix * spaceShip->getPos();
	SDL_QueryTexture(spaceShip->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w;
	square.h = h;
	if (spaceShip->getVelocity().x >= 0.0)
	{
		SDL_RenderCopyEx(renderer, spaceShip->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);
	}
	else {
		SDL_RenderCopyEx(renderer, spaceShip->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
	}
	SDL_RenderPresent(renderer);
}


void Scene0::OnDestroy() 
{

}