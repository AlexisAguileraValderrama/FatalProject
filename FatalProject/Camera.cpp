#include "Camera.h"

Camera::Camera() {}

Camera::Camera(Player *PPlayer, glm::vec3 startUp, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	player = PPlayer;
	worldUp = startUp;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;

	yaw -= xChange;
	pitch = 0.5f;

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(player->pos+front, player->pos, up);
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}


glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

void Camera::update()
{
	front.x = -3.0f * cos(glm::radians(player->yaw - 90)) * cos(glm::radians(pitch));
	//front.y = 3.0f * sin(glm::radians(pitch));
	front.z = 3.0f * sin(glm::radians(player->yaw - 90)) * cos(glm::radians(pitch));
	//front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


Camera::~Camera()
{
}
