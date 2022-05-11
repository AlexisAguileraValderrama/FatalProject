#include "Event.h"


Event::Event(int x, int z, int (*evento)(int))
{
	pos = glm::vec3(x, 0, z);
	this->evento = evento;
	isRunning = false;
}

Event::Event(int x, int z, int numActions, int (*evento)(int))
{
	pos = glm::vec3(x, 2.0f, z);
	this->evento = evento;
	this->numActions = numActions;
	isRunning = false;
}

void Event::Iterate()
{
	currentSeq = evento(currentSeq);
	if (currentSeq == -1) Stop();
}

void Event::NextAction()
{
	currentSeq = ++currentSeq%numActions;
}

void Event::Start()
{
	isRunning = true;
	currentSeq = 0;
}

void Event::Stop()
{
	isRunning = false;
}

