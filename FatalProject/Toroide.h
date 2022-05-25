#pragma once
#include <vector>

#include <math.h>
#include "Mesh.h"

#include "definition.h"

class Toroide
{
public:
	Toroide(float radioMayor, float radioMenor, int stacks, int segments);
	Toroide();
	void init();
	void render();
	virtual ~Toroide();
private:

	std::vector<GLfloat> vertexC;
	std::vector<GLuint> index;

	float radioMayor;
	float radioMenor;
	int stacks;
	int segments;

	Mesh mesh;
};

