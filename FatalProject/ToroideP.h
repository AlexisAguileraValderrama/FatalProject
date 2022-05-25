#pragma once

#include "definition.h"
#include <vector>
#include "Mesh.h"

#include<math.h>
class ToroideP
{
public:
	ToroideP(float rMayor, float rMenor, int pila, int cara);
	ToroideP();
	void init();
	void render();
	virtual ~ToroideP();

private: 
	std::vector<GLfloat>verticeCara;
	std::vector<GLuint> indice;

	float rMayor, rMenor;
	int pila, cara;

	Mesh mesh;
};