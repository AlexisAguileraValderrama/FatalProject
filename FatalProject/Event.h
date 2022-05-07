#pragma once
#include <glm.hpp>

class Event
{
public:

	Event(int x, int z, void (*evento)());
	void Start();
	void Iterate();

	int currentSeq;

	bool isRunning;

	glm::vec3 pos;
	void (*evento)();

private:


};
