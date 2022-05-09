#pragma once
#include <glm.hpp>

class Event
{
public:

	Event(int x, int z, int (*evento)(int));
	void Start();
	void Stop();
	void Iterate();

	int currentSeq = 0;

	bool isRunning = false;

	glm::vec3 pos;
	int (*evento)(int);

private:


};
