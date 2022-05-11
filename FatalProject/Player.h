#pragma once
#include <glm.hpp>
#include <glew.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <glfw3.h>

class Player
{
public:

	Player(glm::vec3 Initialposition, float Initialyaw, float startMoveSpeed, float startTurnSpeed);
	~Player();

	void keyControl(bool* keys, float deltaTime);
	void mouseControl(float xChange);

	glm::vec3 pos;
	float yaw;
	float moveSpeed;
	float startTurnSpeed;
	float turnSpeed;

private:

};
