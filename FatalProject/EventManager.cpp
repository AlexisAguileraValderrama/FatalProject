#include "Event.h"
#include "EventManager.h"
#include "Window.h"
#include "Camera.h"

#include <vector>

EventManager::EventManager()
{
	lastActionState = false;
}

EventManager::~EventManager()
{
}

void EventManager::AddEvent(int x, int z, int (*evento)(int))
{

	Event* eve = new Event(x, z, evento);

	eventos.push_back(*eve);

}

void EventManager::AddAction(int x, int z, int numActions, int (*evento)(int))
{

	Event* eve = new Event(x,z,numActions,evento);

	actions.push_back(*eve);

}

void  EventManager::Update(bool actionSate, glm::vec3 playerPos) {

	float dist = 0;

	if (actionSate != lastActionState) {
		for (Event& e : eventos) {

			dist = glm::distance(playerPos, e.pos);

			if (dist < 5.0f && !e.isRunning) {
				e.Start();
			}
		}

		for (Event& e : actions) {

			dist = glm::distance(playerPos, e.pos);

			if (dist < 5.0f && !e.isRunning) {
				e.NextAction();
			}
		}

	}

	for (Event& e : eventos) {

		if (e.isRunning) {
			e.Iterate();
		}
	}

	for (Event& e : actions) {
			e.Iterate();
	}

	lastActionState = actionSate;


}



