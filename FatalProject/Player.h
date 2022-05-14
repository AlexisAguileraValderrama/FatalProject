#pragma once
#include <glm.hpp>
#include <glew.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include <glfw3.h>
#include "model.h"
#include "Material.h"

class Player
{
public:

	Player(glm::vec3 Initialposition, float Initialyaw, float startMoveSpeed, float startTurnSpeed,Model KaishiParts[]);
	~Player();

	void keyControl(bool* keys, float deltaTime);
	void mouseControl(float xChange);
	void RenderKaishi(GLuint uniformColor, GLuint uniformModel);

	glm::vec3 pos;
	float yaw;
	float KaishiYawn = 0;

	float moveSpeed;
	float startTurnSpeed;
	float turnSpeed;

	Model *KaishiParts;

	//Animacion
	float rotBrazos = 0;
	float rotAntebrazos = 0;
	float rotPiernas = 0;
	float rotEspinillas = 0;
	float rotTorso = 0;

	float timer=0;

private:

};
