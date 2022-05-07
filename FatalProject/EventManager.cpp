#include "Event.h"
#include "EventManager.h"
#include "Window.h"
#include "Camera.h"

#include <vector>

EventManager::EventManager()
{

	actionState = false;

}

EventManager::~EventManager()
{
}

void EventManager::AddEvent(int x, int z, void (*evento)())
{

	Event eve(x,z,evento);

	eventos.push_back(eve);

}

void  EventManager::Update(Window mainWindow, Camera camera) {

	float dist = 0;
	glm::vec3 playerpos (camera.getCameraPosition().z);

	if (mainWindow.getAction() != actionState) {
		for (Event e : eventos) {
		
			dist = glm::distance(playerpos, e.pos);

			if (dist < 5.0f && !e.isRunning) {
				e.Start();
			}
		}

	}

	actionState = mainWindow.getAction();


}



