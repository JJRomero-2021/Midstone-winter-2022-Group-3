#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <SDL.h>
#include <string>
#include "Body.h"
class SceneManager  {
public:
	
	SceneManager();
	~SceneManager();
	void Run();
	bool Initialize(std::string name_, int width_, int height_);
	void GetEvents();
	Body* getPlayer();
	Uint32 getChangeScene();
	
	
private:
	/// Constants and enum are traditionally capitalized
	enum SCENE_NUMBER {
		SCENE0 = 0,
		SCENE1,
		SCENE2,

	};

	class Scene* currentScene;
	class Timer* timer;
	class Window* window;
	Uint32 changeSceneEventType;

	unsigned int fps;
	bool isRunning;
	bool fullScreen;
	void BuildScene(SCENE_NUMBER scene_);
};


#endif // SCENEMANAGER_H