#include "Player.h"


Player::Player(glm::vec3 Initialposition, float Initialyaw, float startMoveSpeed, float startTurnSpeed)
{
	pos = Initialposition;
	yaw = Initialyaw;
	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;
}

Player::~Player()
{
}

void Player::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat desplazamiento = moveSpeed * deltaTime;

	glm::mat4 model(1.0);

	float despz = 0;
	float despx = 0;

	if (keys[GLFW_KEY_W])
	{
		despz += desplazamiento;
	}

	if (keys[GLFW_KEY_S])
	{
		despz -= desplazamiento;
	}

	if (keys[GLFW_KEY_A])
	{
		despx += desplazamiento;
	}

	if (keys[GLFW_KEY_D])
	{
		despx -=desplazamiento;
	}

	model = glm::translate(model, glm::vec3(pos.x, 0, pos.z));
	model = glm::rotate(model, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(despx, 0, despz));

	pos.x = model[3][0];
	pos.z = model[3][2];

}

void Player::mouseControl(float xChange)
{
	xChange *= turnSpeed;

	xChange = -xChange;

	yaw += xChange;

}