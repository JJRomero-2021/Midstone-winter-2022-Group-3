#include <glew.h>
#include <SDL.h>
#include "Debug.h"
#include "Scene2.h"

#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Physics.h"

Scene2::Scene2(SDL_Window* sdlWindow_, SceneManager* scene_)
{
	window = sdlWindow_;
	Debug::Info("Created Scene2: ", __FILE__, __LINE__);
}

Scene2::~Scene2() {}

bool Scene2::OnCreate() {
	
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
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	return true;
}

void Scene2::HandleEvents(const SDL_Event& sdlEvent) {

}

void Scene2::Update(const float deltaTime) {

}

void Scene2::Render() const {
	/// Clear the screen
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 50, 0, 70, 0);
	SDL_RenderClear(renderer);

	/// Draw your scene here


}


void Scene2::OnDestroy() {

}