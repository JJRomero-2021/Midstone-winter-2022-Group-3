#include "SceneManager.h"
#include "Timer.h"
#include "Window.h"
#include "Scene0.h"
#include "Scene1.h"
#include "Scene2.h"
#include <iostream>



SceneManager::SceneManager(): 
	currentScene(nullptr), window(nullptr), timer(nullptr),
	fps(60), isRunning(false), fullScreen(false) {}

SceneManager::~SceneManager() {
	if (currentScene) {
		currentScene->OnDestroy();
		delete currentScene;
		currentScene = nullptr;
	}
	
	if (timer) {
		delete timer;
		timer = nullptr;
	}

	if (window) {
		delete window;
		window = nullptr;
	}
	Debug::Info("Deleting the GameSceneManager", __FILE__, __LINE__);

}

bool SceneManager::Initialize(std::string name_, int width_, int height_) {
	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Failed to initialize Window object", __FILE__, __LINE__);
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		Debug::FatalError("Failed to initialize Timer object", __FILE__, __LINE__);
		return false;
	}
	/********************************   Default first scene   ***********************/
	BuildScene(SCENE0);
	/********************************************************************************/
		
	//create some user defined event
	changeSceneEventType = SDL_RegisterEvents(1);
	if (changeSceneEventType == ((Uint32)-1))
	{
		currentScene->OnDestroy();
		return false;
	}
	return true;
}


void SceneManager::Run() 
{
	timer->Start();
	isRunning = true;
	while (isRunning)
	{
		timer->UpdateFrameTicks();
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();
		GetEvents();
		
		//SDL_GL_SwapWindow(window->getWindow());
		SDL_Delay(timer->GetSleepTime(60));
	}
}

void SceneManager::GetEvents() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		const Uint8* state = SDL_GetKeyboardState(nullptr); /// Do not free this! Read the docs
		if (sdlEvent.type == SDL_EventType::SDL_QUIT) {
			isRunning = false;
			return;
		}
		else if (sdlEvent.type == changeSceneEventType)
		{
			// switch scene
			currentScene->OnDestroy();
			delete currentScene;
			currentScene = new Scene1(window->getWindow(), this);
			if (currentScene->OnCreate())
			{
				isRunning = false;
			}
		}
		else if (sdlEvent.type == SDL_KEYDOWN) {
			switch (sdlEvent.key.keysym.scancode) {
			case SDL_SCANCODE_ESCAPE:
			case SDL_SCANCODE_Q:
				isRunning = false;
				return;

			case SDL_SCANCODE_F1:
				if (state[SDL_SCANCODE_RSHIFT] || state[SDL_SCANCODE_LSHIFT]) {

				}
				else {
					BuildScene(SCENE0);
				}
				break;

			case SDL_SCANCODE_F2:
				if (state[SDL_SCANCODE_RSHIFT] || state[SDL_SCANCODE_LSHIFT]) {
					
				} else {
					BuildScene(SCENE1);
				}
				break;

			case SDL_SCANCODE_F3:
				if (state[SDL_SCANCODE_RSHIFT] || state[SDL_SCANCODE_LSHIFT]) {
					
				}
				else {
					BuildScene(SCENE2);
				}
				break;

			case SDL_SCANCODE_RETURN:
				if (fullScreen == false) {
					fullScreen = true;
					SDL_SetWindowFullscreen(window->getWindow(), SDL_WINDOW_FULLSCREEN);
				}
				break;

			default:
				currentScene->HandleEvents(sdlEvent);
				break;
			}
		}
		if (currentScene == nullptr) {
			Debug::FatalError("Failed to initialize Scene", __FILE__, __LINE__);
			isRunning = false;
			return;
		}
		currentScene->HandleEvents(sdlEvent);
	}
}

Body* SceneManager::getPlayer()
{
	return nullptr;
}

Uint32 SceneManager::getChangeScene()
{
	return changeSceneEventType;
}

void SceneManager::BuildScene(SCENE_NUMBER scene) {
	bool status; 

	if (currentScene != nullptr) {
		currentScene->OnDestroy();
		delete currentScene;
		currentScene = nullptr;
	}

	switch (scene) {
	case SCENE0:  
		currentScene = new Scene0(window->getWindow(), this);
		status = currentScene->OnCreate();
		break;

	
	case SCENE1:
		currentScene = new Scene1(window->getWindow(), this);
		status = currentScene->OnCreate();
		break;
	
	case SCENE2:
		currentScene = new Scene2(window->getWindow(), this);
		status = currentScene->OnCreate();
		break;

	default:
		Debug::Error("Incorrect scene number assigned in the manager", __FILE__, __LINE__);
		currentScene = nullptr;
		break;
	}	
}


