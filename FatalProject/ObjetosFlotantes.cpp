#include "ObjetosFlotantes.h"

ObjetosFlotantes::ObjetosFlotantes(Model* model)
{
	modelo = model;
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> rand(-4, 4);
	std::uniform_int_distribution<int> randc(-3, 3);
	do {
		a = rand(rng);
	} while (a == 0);

	do {
		b = rand(rng);
	} while (a == b || b==0);

	do
	{
		c = randc(rng);
	} while (b == c || a == c || c == 0);

	std::uniform_int_distribution<int> randT(0, 1000);

	CurrTime = randT(rng);

	int timevel = CurrTime / 50.0f;

	x = (a - b) * cos(timevel) + c * cos(((a / b) - 1) * timevel) + 25.575;
	objy = cos(timevel) * sin(timevel) + 2;
	z = (a - b) * sin(timevel) - c * sin(((a / b) - 1) * timevel) + 66.751;

	y = 1.2f;

	goingFloor = false;
	onTheFloor = true;

	onTheObj = false;
	goingObj = false;


}

void ObjetosFlotantes::GoTofloor(float deltaTime)
{
	if (!onTheFloor) {
		onTheObj = false;
		goingObj = false;
		goingFloor = true;
	}

	if (goingFloor) {
		if (1.2f < y) {
			y -= 0.005f * deltaTime;
			if (1.2f > y) {
				y = 1.2f;
				goingFloor = false;
				onTheFloor = true;
			}
		}
		else {
			y += 0.005f * deltaTime;
			if (1.2f < y) {
				y = 1.2f;
				goingFloor = false;
				onTheFloor = true;
			}
		}
	}


}

void ObjetosFlotantes::GoToObj(float deltaTime)
{

	if (goingObj) {
		if (objy < y) {
			y -= 0.005f * deltaTime;
			if (objy > y) {
				y = objy;
				goingObj = false;
				onTheObj = true;
			}
		}
		else {
			y += 0.005f * deltaTime;
			if (objy < y) {
				y = objy;
				goingObj = false;
				onTheObj = true;
			}
		}
	}

}

void ObjetosFlotantes::Move(float deltaTime)
{

	if (!onTheObj) {
		onTheFloor = false;
		goingFloor = false;
		goingObj = true;
		GoToObj(deltaTime);
	}
	else {

		if (abs(CurrTime) > 1000) {
			std::random_device rd;     // only used once to initialise (seed) engine
			std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
			std::uniform_int_distribution<int> randT(0, 1000);
			CurrTime = randT(rng);
		}

		CurrTime += deltaTime;

		float timevel = CurrTime / 50.0f;

		x = (a - b) * cos(timevel) + c * cos(((a / b) - 1) * timevel) + 25.575;
		y = cos(timevel) * sin(timevel) + 2;
		z = (a - b) * sin(timevel) - c * sin(((a / b) - 1) * timevel) + 66.751;
		objy = y;
	}

}

void ObjetosFlotantes::Render(GLuint uniformModel, GLuint uniformColor)
{

	glm::mat4 model(1.0);
	model = glm::mat4(1.0);

	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
	modelo->RenderModel();

}


ObjetosFlotantes::~ObjetosFlotantes()
{
}