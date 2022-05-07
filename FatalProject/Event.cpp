#include "Event.h"


Event::Event(int x, int z, void (*evento)())
{
	pos = glm::vec3(x, 0, z);
	this->evento = evento;
	isRunning = false;
}

void Event::Iterate()
{
	evento();
}

void Event::Start()
{
	isRunning = true;
	currentSeq = 0;
}
