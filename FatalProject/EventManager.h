#pragma once

#include "Event.h"

#include <vector>

class EventManager
{
public:

	std::vector<Event> eventos;
	

	EventManager();
	~EventManager();

	void Update(Window mainWindow, Camera camera);

	void AddEvent(int x, int z, void (*evento)());

private:

	bool actionState;

};