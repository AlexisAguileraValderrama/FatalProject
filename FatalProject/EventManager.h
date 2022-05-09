#pragma once

#include "Event.h"
#include "Window.h"
#include "Camera.h"

#include <vector>

class EventManager
{
public:

	std::vector<Event> eventos;
	std::vector<Event> actions;

	EventManager();
	~EventManager();

	void Update(bool actionState, glm::vec3 cameraPos);

	void AddEvent(int x, int z, int (*evento)(int));
	void AddAction(int x, int z,int numAcitons, int (*evento)(int));

private:

	bool lastActionState;

};