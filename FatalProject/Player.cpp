#include "Player.h"


Player::Player(glm::vec3 Initialposition, float Initialyaw, float startMoveSpeed, float startTurnSpeed, Model KaishiPartss[])
{
	pos = Initialposition;
	yaw = Initialyaw;
	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;
	KaishiParts = KaishiPartss;
}

Player::~Player()
{
}


void Player::keyControl(bool* keys, GLfloat deltaTime)
{
	timer += 8*deltaTime;

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



	if (despx != 0 || despz != 0) {
		rotBrazos = 30 * sin(glm::radians(timer));
		rotAntebrazos = abs(30 * sin(glm::radians(timer)));
		rotPiernas = 30 * sin(glm::radians(timer));
		rotEspinillas = abs(30 * sin(glm::radians(timer)));
		rotTorso = 10 * sin(glm::radians(timer));
	}
	else {
		rotBrazos = 0;
		rotAntebrazos = 0;
		rotPiernas = 0;
		rotEspinillas = 0;
		rotTorso = 0;
		timer = 0;
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

void Player::RenderKaishi(GLuint uniformColor, GLuint uniformModel) {

	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::mat4 modelaux2(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	model = glm::mat4(1.0);
	model = glm::translate(model, pos);
	model = glm::rotate(model, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	modelaux = model;

	///// Torso
	model = modelaux;

	model = glm::translate(model, glm::vec3(0.0f, -0.321f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(KaishiYawn), glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, glm::radians(rotTorso), glm::vec3(0.0f, 1.0f, 0.0f));
	modelaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	KaishiParts[0].RenderModel();

	//Brazo derecho
	model = modelaux;

	model = glm::translate(model, glm::vec3(0.136f, 0.06f, 0.0f));
	model = glm::rotate(model, glm::radians(-70.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, glm::radians(rotBrazos), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	KaishiParts[1].RenderModel();

	model = glm::translate(model, glm::vec3(0.258f, 0.00f, 0.0f));
	model = glm::rotate(model, glm::radians(rotAntebrazos), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	KaishiParts[2].RenderModel();

	//Brazo izquierdo
	model = modelaux;

	model = glm::translate(model, glm::vec3(-0.136f, 0.06f, 0.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-70.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, glm::radians(rotBrazos), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	KaishiParts[1].RenderModel();

	model = glm::translate(model, glm::vec3(0.258f, 0.00f, 0.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotAntebrazos), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	KaishiParts[2].RenderModel();

	//Pierna derecha
	model = modelaux;

	model = glm::translate(model, glm::vec3(0.085f, -0.552f, -0.037f));
	model = glm::rotate(model, glm::radians(-rotPiernas), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	KaishiParts[3].RenderModel();

	model = glm::translate(model, glm::vec3(0.0f, -0.4f, 0.0f));
	model = glm::rotate(model, glm::radians(-rotEspinillas), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	KaishiParts[4].RenderModel();

	//Pierna Izquierda
	model = modelaux;

	model = glm::translate(model, glm::vec3(-0.085f, -0.552f, -0.037f));
	model = glm::rotate(model, glm::radians(rotPiernas), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	KaishiParts[3].RenderModel();

	model = glm::translate(model, glm::vec3(0.0f, -0.4f, 0.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-rotEspinillas), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	KaishiParts[4].RenderModel();

}

