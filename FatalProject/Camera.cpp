#include "Camera.h"

Camera::Camera() {}

Camera::Camera(Player *PPlayer, glm::vec3 startUp, GLfloat startPitch)
{
	player = PPlayer;
	worldUp = startUp;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	update(false);
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(player->pos + front, player->pos, up);

}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}


glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

void Camera::update(bool isometric)
{

	isIsometric = isometric;

	front = glm::vec3(0,0,0);

	if (isIsometric) {
		pitch = 90.0f;
		front.y = 50.0f * sin(glm::radians(pitch));
		front.x = -50.0f * cos(glm::radians(player->yaw + 90 )) * cos(glm::radians(pitch));
		front.z = 50.0f * sin(glm::radians(player->yaw + 90)) * cos(glm::radians(pitch));
	}
	else {
		pitch = 0.5f;
		front.x = -3.0f * cos(glm::radians(player->yaw - 90)) * cos(glm::radians(pitch));
		front.z = 3.0f * sin(glm::radians(player->yaw - 90)) * cos(glm::radians(pitch));
		front.y = 0;
	}

	//front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


Camera::~Camera()
{
}
