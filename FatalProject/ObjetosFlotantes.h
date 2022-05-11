#pragma once

#include "Model.h"
#include <random>
#include <math.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

class ObjetosFlotantes
{
public:
	ObjetosFlotantes(Model* model);
	void Move(float deltaTime);
	void Render(GLuint uniformModel, GLuint uniformColor);
	void GoTofloor(float deltaTime);
	void GoToObj(float deltaTime);

	~ObjetosFlotantes();

private:

	Model* modelo;
	float CurrTime = 0;
	int a, b, c = 0;
	float x, y, z, objy = 0;

	bool goingFloor, onTheFloor;
	bool goingObj, onTheObj;

};

