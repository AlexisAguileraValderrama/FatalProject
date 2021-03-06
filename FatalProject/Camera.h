#pragma once

#include <glew.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <glfw3.h>

#include "Player.h"

class Camera
{
public:
	Camera();
	Camera(Player *player, glm::vec3 startUp, GLfloat startPitch);

	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();
	glm::mat4 calculateViewMatrix();

	~Camera();

	Player *player;

	void update(bool isometric);

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat pitch;

	bool isIsometric = false;
};

