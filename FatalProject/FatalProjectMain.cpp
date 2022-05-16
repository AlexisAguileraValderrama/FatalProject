/*
Semestre 2022-2
Práctica 5: Carga de Modelos
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include <random>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include"Model.h"
#include "Skybox.h"

#include "EventManager.h"
#include "ObjetosFlotantes.h"
#include "Player.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

const float toRadians = 3.14159265f / 180.0f;
const float PI = 3.14159265f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

EventManager eventManager;

Model Terreno;
Model Casa;
Model Lampara;
Model LamparaTori;
Model Valla;
Model Tori;
Model Tumba;
Model Mausoleo;


Model Doll;
Model Oni;
Model LamparaPapel;

Model Zombie;
Model Rope;
Model Poste;

Model Desktop;
Model Vodoo;
Model Walls;
Model Door;
Model Ghost;
Model Chest;
Model ChestTape;

Model objetos[6];

Model KaishiParts[5];

Model Chaser;
Model WallsPasillo;


std::vector<ObjetosFlotantes> flotantes;


Texture ArbolTexture[3];
Texture KanjiTexture;

Skybox skybox;
Skybox skybox2;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

//Daytime

float daytime = 0;
float daytimevel = 0.05f;

float daytimeLightpointLights = 0.2f;
float daytimeLightspointLights = 10.0f;

bool day = false;

//Variables de avatar

glm::vec3 PlayerPos = glm::vec3(0.0f, 2.836f, 0.0);

Player player = Player(PlayerPos, 0, 0.2f, 1.0f, KaishiParts);

////////Evento 1/////////////

float timeAC = 0, posz = 0, posx = 0, poszA = 0, posxA = 0, posy = 0, vel = 0, ang = 0;

float intensityFloor = 0.2f;
float intensityOni = 0.0f;
float intensityThree = 0.0f;

float colorLight1 = 0;
float colorLight2 = 0;
float colorLight3 = 0;

float Light1posx, Light1posz = 0;
float Light2posx, Light2posz = 0;
float Light3posx, Light3posz = 0;

float Light1angx, Light1angz = 0;
float Light2angx, Light2angz = 0;
float Light3angx, Light3angz = 0;

float colorang, lightangpos = 0;

///////Variables evento 2///////////////

float angCuerdas = 0;
glm::vec3 posZombie = glm::vec3(-20.604f, 5.3777f, 77.374f);
float angZombie = 0;

float LightIntensity_E2 = 0.2f;

float angTamboleoCuerdas = 0.0f;
float timeTamboleo = 0.0f;

GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
uniformSpecularIntensity = 0, uniformShininess = 0;
GLuint uniformColor = 0;

/////////Variables 3////////////////

float LightIntensity_E3 = 0.2f;
float LightIntensitySpotLight_E3 = 0.0f;

/////////Variables evento 4/////////////

glm::vec3 posVodoo = glm::vec3(22.996f, 2.3037f, 25.164f);
float scaleVodoo = 1.0f;

glm::vec3 posDoor1 = glm::vec3(27.498f, 2.4226f, 24.381f);
glm::vec3 posDoor2 = glm::vec3(27.498f, 2.4226f, 25.973f);

float angTape = 0;

glm::vec3 posGhost = glm::vec3(32.834f, 1.3739f, 25.145f);
float angGhost = 0;
float scaleGhost = 0.0f;

float tempo4 = 0;

float LightIntensity_E4 = 0.2f;
float DemonLightIntensity_E4 = 0.0f;

////////Variables para evento 5/////


float chaseTimer = 0;
float desplazamientoChaser = 0;
glm::vec3 posChaser = glm::vec3(-35.003,0.7011f,46.613f);
float angChaser = 0;

float LightIntensity_E5 = 0.2f;
float chaserScale = 0.0f;

////////////////

glm::mat4 model(1.0);
glm::mat4 modelaux(1.0);
glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";



//En create objects: 
unsigned int vegetacionIndices[] = {
		0, 1, 2,
		0, 2, 3,
		4,5,6,
		4,6,7
};

GLfloat vegetacionVertices[] = {
	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

	0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
	0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
	0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
	0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,
};





//llamar en main función CrearDado
//Renderizar el Dado


void CreateObjects()
{

	//En create objects: 
	unsigned int vegetacionIndices[] = {
			0, 1, 2,
			0, 2, 3,
			4,5,6,
			4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.25f, -0.5f, 0.0f,		0.223f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.25f, -0.5f, 0.0f,		0.777f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.25f, 0.5f, 0.0f,		0.777f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.25f, 0.5f, 0.0f,		0.223f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.25f,		0.233f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.25f,		0.777f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.25f,		0.777f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.25f,		0.233f, 1.0f,		0.0f, 0.0f, 0.0f,
	};

	//En create objects: 
	unsigned int kanjiIndices[] = {
			0, 1, 2,
			0, 2, 3,
	};

	GLfloat KanjiVertices[] = {
		-0.5f, -0.5f, 0.0f,   	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj1);


	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(KanjiVertices, kanjiIndices, 32, 6);
	meshList.push_back(obj2);
	// fin create objects


}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

float* Fourier(std::vector<float> coefzCN, std::vector<float> coefzSN, std::vector<float> coefxCN, std::vector<float> coefxSN, float t, float vel) {

	float posz = 0;

	float posx = 0;

	int N = coefzCN.size() * 2;

	for (int i = 0; i < N / 2; i++) {
		posz += coefzCN[i] * cos((2 * PI * t * i) / (N * vel)) + coefzSN[i] * sin((2 * PI * t * i) / (N * vel));
		posx += coefxCN[i] * cos((2 * PI * t * i) / (N * vel)) + coefxSN[i] * sin((2 * PI * t * i) / (N * vel));
	}

	float pos[2] = { posz, posx };

	return pos;

}

float AngleOf2(glm::vec2 p1, glm::vec2 p2) {


	glm::vec2 C = p2 - p1;
	float Cmag = sqrt(C.x * C.x + C.y * C.y);

	float ang = acos(glm::dot(C, glm::vec2(0, 1)) / (Cmag));

	if (C.x < 0) {
		ang = -ang;
	}

	return ang;

}


std::vector<float> coefxCn = { -9.7574295f,
							9.9744506f,
							-0.75981228f,
							0.65529038f,
							0.11264482f,
							-1.8801795f,
							1.6172443f,
							-0.36016341f,
							0.18781106f,
							0.039508188f,
							0.42643272f,
							-0.064029927f,
							0.072172092f,
							0.017299245f,
							-0.10818795f,
							-0.058225783f,
							0.088916457f,
							-0.035052926f,
							-0.029790758f,
							-0.062926560f,
							-0.063883618f,
							-0.080321346f,
							0.013411364f,
							-0.039042570f,
							-0.012722972f,
							0.013668673f,
							0.0036968969f,
							-0.024843677f,
							0.0089399774f,
							-0.033193852f,
							-0.014700471f,
							-0.029752333f,
							0.010623411f,
							0.0031162904f,
							0.0022506304f,
							-0.032968178f,
							-0.0019289525f,
							0.049940239f,
							0.0054488619f,
							0.051109780f,
							0.038564086f,
							-0.013133813f,
							0.019331697f,
							0.060150511f,
};


std::vector<float> coefxSn = { 7.4082155e-15f,
-8.5846874f,
-1.6641705f,
3.2687172f,
-0.45914151f,
-0.75502974f,
-0.56225151f,
0.85239838f,
-0.61918513f,
0.26302899f,
0.016532803f,
0.064985503f,
0.25227090f,
-0.11656318f,
-0.089458149f,
-0.046498294f,
-0.053889773f,
-0.054065390f,
0.052920448f,
0.021953794f,
0.14715944f,
-0.012223489f,
-0.018084091f,
0.033386869f,
-0.020169158f,
0.021292405f,
0.0072443237f,
0.029082127f,
-0.030258202f,
-0.0069025663f,
-0.036505264f,
-0.076742030f,
-0.022900306f,
-0.0051417701f,
-0.012927358f,
-0.020928687f,
-0.0010034451f,
-0.061084737f,
0.011353092f,
0.0090788778f,
-0.00096322302f,
0.015860058f,
0.014054408f,
-0.024300625f,
};
std::vector<float> coefzCn = { 60.327991f,
25.762195f,
8.8904121f,
3.6829075f,
2.1965472f,
2.7129365f,
0.68848265f,
0.43055146f,
0.49778393f,
-0.097882778f,
0.83342351f,
0.44668574f,
0.67104851f,
0.78738057f,
0.39328699f,
0.21018313f,
0.29757793f,
0.13082497f,
0.23816032f,
0.16043430f,
0.23059296f,
0.14180677f,
0.11383864f,
0.11916434f,
0.11500041f,
0.10329584f,
0.032539931f,
0.048825494f,
-0.013386986f,
0.0078668315f,
-0.021330743f,
-0.013843999f,
0.0035328512f,
-0.013817555f,
-0.090462657f,
-0.10923293f,
-0.097959602f,
-0.070237453f,
-0.072001380f,
-0.069351490f,
-0.11594853f,
-0.099691545f,
-0.10769932f,
-0.089151161f,
};


std::vector<float> coefzSn = { -4.7800148e-14f,
		-5.7169481f,
		-6.0872255f,
		-5.9213816f,
		2.0820633f,
		0.87353464f,
		1.6359553f,
		0.49726843f,
		-0.72985356f,
		-0.67934254f,
		-0.49225796f,
		-0.12211313f,
		-0.19807210f,
		0.083066445f,
		0.12517432f,
		0.024393007f,
		0.080315997f,
		-0.058118058f,
		0.019954953f,
		0.0041843694f,
		0.066591290f,
		0.073075048f,
		0.13409318f,
		0.19749245f,
		0.21222716f,
		0.19674110f,
		0.18234367f,
		0.23941984f,
		0.19242980f,
		0.18550196f,
		0.20223872f,
		0.20139520f,
		0.16949263f,
		0.14215960f,
		0.095457251f,
		0.13314241f,
		0.12905584f,
		0.15864058f,
		0.084022283f,
		0.032475856f,
		0.042330571f,
		0.039135828f,
		0.012736363f,
		0.034919635f,
};




int evento1(int seq) {

	colorLight1 = sin(colorang);
	colorLight2 = cos(colorang);
	colorLight3 = cos(colorang);

	Light1posx = 4.0f * cos(lightangpos);
	Light1posz = 4.0f * sin(lightangpos) + 109.0f;

	Light2posx = 4.0f * cos(lightangpos + 90* toRadians);
	Light2posz = 4.0f * sin(lightangpos + 90 * toRadians) + 109.0f;

	Light3posx = 4.0f * cos(lightangpos + 180 * toRadians);;
	Light3posz = 4.0f * sin(lightangpos + 180 * toRadians) + 109.0f;

	Light1angx = -0.5 * cos(lightangpos);
	Light1angz = -0.5 * sin(lightangpos);

	Light2angx = 0.5 * sin(lightangpos);
	Light2angz = -0.5 * cos(lightangpos);

	Light3angx = 0.5 * cos(lightangpos);
	Light3angz = 0.5 * sin(lightangpos);


	colorang += 0.05f * deltaTime;
	lightangpos += 0.05f * deltaTime;

	switch (seq) {
		case 0:
			intensityFloor = 0.0f;
			intensityOni = 0.5;
			intensityThree = 3.0;
			posx = 0;
			posz = 109.15f;
			posy = -1.3f;
			vel = 20.0f;

			colorang = 0.0f;
			lightangpos = 0.0f;
			
			return 1;
		case 1:

			color = glm::vec3(1.0f, 1.0f, 1.0f);

			modelaux = glm::mat4(1.0);

			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-posx,
				posy,
				posz));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			Doll.RenderModel();

			posy += 0.005f * deltaTime;

			if (posy >= 1.5f) {
				timeAC = 0;
				return 2;
			}
			else {
				return 1;
			}

		case 2:

			timeAC += deltaTime;

			model = glm::mat4(1.0);

			float* p;	

			p = Fourier(coefzCn, coefzSn, coefxCn, coefxSn, timeAC, vel);

			posz = *p;
			posx = *(p + 1);

			ang = AngleOf2(glm::vec2(posxA, poszA), glm::vec2(posx, posz));

			///Para vuelta////
			///Jerarquización de carro descargado///////////////////////

			color = glm::vec3(1.0f, 1.0f, 1.0f);

			modelaux = glm::mat4(1.0);

			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-posx,
				posy,
				posz));

			model = glm::rotate(model, -ang, glm::vec3(0.0f, 1.0f, 0.0f));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			Doll.RenderModel();

			posxA = posx;
			poszA = posz;

			if (timeAC > coefzCn.size()*2*vel) {
				posx = 0;
				posz = 109.15f;
				posy = 1.5f;
				return 3;
			}
			else {
				return 2;
			}
		case 3:
			color = glm::vec3(1.0f, 1.0f, 1.0f);

			modelaux = glm::mat4(1.0);

			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-posx,
				posy,
				posz));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			Doll.RenderModel();

			posy -= 0.005f * deltaTime;

			if (posy <= -1.3f) {
				timeAC = 0;
				intensityOni = 0.0;
				intensityThree = 0.0;
				intensityFloor = 0.2f;
				return -1;
			}
			else {
				return 3;
			}
	}
}

int evento2(int seq) {
	switch (seq)
	{

	case 0:

		angCuerdas = 0;
		angZombie = 0;
		posZombie = glm::vec3(-20.604f, 5.3777f, 77.374f);
		LightIntensity_E2 = 0.0f;
		timeTamboleo = 0;

		return 1;

	case 1:

		if (angCuerdas > -70.0f) {
			angCuerdas -= 1.5f * deltaTime;
		}

		timeTamboleo += 1.3f * deltaTime;

		if (timeTamboleo > 360) {
			timeTamboleo = 0;
		}

		angTamboleoCuerdas = 7.0f * cos(timeTamboleo * toRadians);


		if (posZombie.y > -40.0f) {
			posZombie -= glm::vec3(0.0, 0.3 * deltaTime, 0.0f);

			angZombie += 1.7f * deltaTime;
		}

		return 1;

	}
}

int evento3(int seq) {
	switch (seq)
	{
		case 0:

			LightIntensity_E3 = 0.2f;
			LightIntensitySpotLight_E3 = 0.0f;

			for (ObjetosFlotantes& f : flotantes) {
				f.GoTofloor(deltaTime);
			}


			break;

		case 1:

			LightIntensity_E3 = 0.0f;
			LightIntensitySpotLight_E3 = 3.0f;

			for (ObjetosFlotantes& f : flotantes) {
				f.Move(deltaTime);
			}
			break;
	}

	return seq;
}

int evento4(int seq) {


	switch (seq)
	{

	case 0:

		posVodoo = glm::vec3(22.996f, 2.3037f, 25.164f);
		scaleVodoo = 0.0f;

		posDoor1 = glm::vec3(27.498f, 2.4226f, 24.381f);
		posDoor2 = glm::vec3(27.498f, 2.4226f, 25.973f);

		angTape = 0;
		angGhost = 0;

		posGhost = glm::vec3(32.834f, 1.3739f, 25.145f);
		scaleGhost = 0.0f;

		tempo4 = 0;

		LightIntensity_E4 = 0;


		return 1;

		break;

	case 1:

		posDoor1.z -= 0.25f * deltaTime;
		posDoor2.z += 0.25f * deltaTime;

		if (posDoor1.z < 23.0f) {
			posDoor1.z = 23.0f;
			posDoor2.z = 27.5f;
			return 2;
		}

		return 1;

	case 2:

		angTape += 0.2f * deltaTime;

		if (angTape > 100.0f) {
			angTape = 100.0f;
			return 3;
		}

		return 2;

	case 3:

		scaleGhost += 0.05f * deltaTime;

		posGhost.x -= 0.06f * deltaTime;
		posGhost.y += 0.02f * deltaTime;

		if (scaleGhost > 1.0f) {
			scaleGhost = 1.0f;
			DemonLightIntensity_E4 = 2.0f;
			return 4;
		}

		return 3;

	case 4:

		tempo4 += deltaTime;

		if (tempo4 > 100.0f) {
			return 5;
		}

		return 4;

	case 5:

		angGhost += 0.6f * deltaTime;

		if (angGhost > 90.0f) {
			return 6;
		}

		return 5;
		
	case 6:

		posGhost.z += 0.08f * deltaTime;

		if (posGhost.z > 32.0f) {
			return 7;
		}

		return 6;

	case 7:

		posDoor1.z += 0.06f * deltaTime;
		posDoor2.z -= 0.06f * deltaTime;

		if (posDoor1.z > 24.381f) {
			posDoor1.z = 24.381f;
			posDoor2.z = 25.973f;
		}

		angTape -= 2.0f * deltaTime;

		if (ang < 0) {
			angTape = 0;
		}

		scaleVodoo += 0.02*deltaTime;

		if (scaleVodoo > 1.0f)
		{
			scaleVodoo = 1.0f;
			DemonLightIntensity_E4 = 0.0f;
			LightIntensity_E4 = 0.2f;
			return -1;
		}

		return 7;

	}

}

int evento5(int seq) {

	switch (seq)
	{

	case 0:

		posChaser = glm::vec3(-35.003, 2.162f, 46.548f);
		chaseTimer = 0.0f;
		LightIntensity_E5 = 0.0f;
		chaserScale = 1.0f;

		return 1;


	case 1:
		chaseTimer += 0.1 * deltaTime;

		desplazamientoChaser = 0;
		angChaser = AngleOf2(glm::vec2(posChaser.x, posChaser.z), glm::vec2(player.pos.x, player.pos.z));


		if (glm::distance(posChaser, player.pos) > 2.0f) {
			desplazamientoChaser += 0.05 * deltaTime;
		}

		if (chaseTimer > 100) {
			return 2;
		}

		return 1;

	case 2:
		chaseTimer += 0.5 * deltaTime;

		desplazamientoChaser = 0;
		angChaser = AngleOf2(glm::vec2(posChaser.x, posChaser.z), glm::vec2(-35.003, 46.548f));


		if (glm::distance(posChaser, glm::vec3(-35.003, 2.162f, 46.548f)) > 0.2f) {
			desplazamientoChaser += 0.05 * deltaTime;
		}
		else {
			LightIntensity_E5 = 0.2f;
			chaserScale = 0.0f;
			return -1;
		}

		return 2;
	

	default:
		break;
	}

}



int main()
{

	srand(time(0));

	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	eventManager = EventManager();

	eventManager.AddEvent(0, 110, &evento1);     //Animación de invocacion demoniaca
	eventManager.AddEvent(-14, 68, &evento2);    //Animación de sacrficio semi humano
	eventManager.AddAction(15, 66, 2, &evento3); //Animación de cosas flotantes
	eventManager.AddEvent(22, 24, &evento4);     //Animación de cofre demoniaco
	eventManager.AddEvent(-29, 46, &evento5);    //Animación de 

	CreateObjects();
	CreateShaders();

	Terreno = Model();
	Terreno.LoadModel("Models/Terreno.obj");

	Casa = Model();
	Casa.LoadModel("Models/House.obj");

	Tori = Model();
	Tori.LoadModel("Models/Tori.obj");

	Lampara = Model();
	Lampara.LoadModel("Models/Lamp.obj");

	Valla = Model();
	Valla.LoadModel("Models/fence.obj");

	Tumba = Model();
	Tumba.LoadModel("Models/Grave.obj");

	Mausoleo = Model();
	Mausoleo.LoadModel("Models/Mausoleo.obj");


	Doll = Model();
	Doll.LoadModel("Models/Doll.obj");

	LamparaPapel = Model();
	LamparaPapel.LoadModel("Models/FlorLamp.obj");

	Oni = Model();
	Oni.LoadModel("Models/Oni.obj");


	Zombie = Model();
	Zombie.LoadModel("Models/ZombieRope.obj");

	Rope = Model();
	Rope.LoadModel("Models/Rope.obj");

	Poste = Model();
	Poste.LoadModel("Models/WoodenPost.obj");

	LamparaTori = Model();
	LamparaTori.LoadModel("Models/LampRojo.obj");

	Desktop = Model();
	Desktop.LoadModel("Models/Desktop.obj");

	Vodoo = Model();
	Vodoo.LoadModel("Models/Vodoo.obj");

	Walls = Model();
	Walls.LoadModel("Models/Walls.obj");

	Door = Model();
	Door.LoadModel("Models/Door.obj");

	Ghost = Model();
	Ghost.LoadModel("Models/Ghost.obj");

	Chest = Model();
	Chest.LoadModel("Models/Chest.obj");

	ChestTape = Model();
	ChestTape.LoadModel("Models/ChestTape.obj");

	KaishiParts[0] = Model();
	KaishiParts[0].LoadModel("Models/KaishiTorso.obj");

	KaishiParts[1] = Model();
	KaishiParts[1].LoadModel("Models/KaishiBrazo.obj");

	KaishiParts[2] = Model();
	KaishiParts[2].LoadModel("Models/KaishiAntebrazo.obj");

	KaishiParts[3] = Model();
	KaishiParts[3].LoadModel("Models/KaishiPierna.obj");

	KaishiParts[4] = Model();
	KaishiParts[4].LoadModel("Models/KaishiEspinilla.obj");

	Chaser = Model();
	Chaser.LoadModel("Models/Chaser.obj");

	WallsPasillo = Model();
	WallsPasillo.LoadModel("Models/WallsPasillo.obj");


	camera = Camera(&player, glm::vec3(0.0f, 0.5f, 0.0f), 0.5f);

	objetos[0] = Model();
	objetos[0].LoadModel("Models/Katana.obj");

	objetos[1] = Model();
	objetos[1].LoadModel("Models/Silla.obj");

	objetos[2] = Model();
	objetos[2].LoadModel("Models/Teapod.obj");

	objetos[3] = Model();
	objetos[3].LoadModel("Models/Candle.obj");

	objetos[4] = Model();
	objetos[4].LoadModel("Models/Estatua.obj");

	objetos[5] = Model();
	objetos[5].LoadModel("Models/Plateset.obj");


	for (int i = 0; i < 60; i++) {
		flotantes.push_back(ObjetosFlotantes(&objetos[i%6]));
	}


	ArbolTexture[0] = Texture("Textures/ArbolTexture.png");
	ArbolTexture[0].LoadTextureA();

	ArbolTexture[1] = Texture("Textures/ArbolTexture1.png");
	ArbolTexture[1].LoadTextureA();

	ArbolTexture[2] = Texture("Textures/ArbolTexture2.png");
	ArbolTexture[2].LoadTextureA();

	KanjiTexture = Texture("Textures/OniKanjiTexture.png");
	KanjiTexture.LoadTextureA();


	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/left.jpg");
	skyboxFaces.push_back("Textures/Skybox/right.jpg");
	skyboxFaces.push_back("Textures/Skybox/bottom.jpg");
	skyboxFaces.push_back("Textures/Skybox/top.jpg");
	skyboxFaces.push_back("Textures/Skybox/back.jpg");
	skyboxFaces.push_back("Textures/Skybox/front.jpg");

	skybox = Skybox(skyboxFaces);

	std::vector<std::string> skyboxFaces2;
	skyboxFaces2.push_back("Textures/Skybox/left_n.jpg");
	skyboxFaces2.push_back("Textures/Skybox/right_n.jpg");
	skyboxFaces2.push_back("Textures/Skybox/bottom_n.jpg");
	skyboxFaces2.push_back("Textures/Skybox/top_n.jpg");
	skyboxFaces2.push_back("Textures/Skybox/back_n.jpg");
	skyboxFaces2.push_back("Textures/Skybox/front_n.jpg");

	skybox2 = Skybox(skyboxFaces2);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);



	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.6, 0.6f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;

	//Luces de lamparas
	
	pointLights[0] = PointLight(1.0f, 0.7f, 0.0f,
		0.2f, 0.2f,
		2.0f, 1.5f, 1.5f,
		0.1f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[1] = PointLight(1.0f, 0.7f, 0.0f,
		0.2f, 0.2f,
		2.0f, 1.5f, 1.5f,
		0.1f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[2] = PointLight(1.0f, 0.7f, 0.0f,
		0.2f, 0.2f,
		2.0f, 1.5f, 1.5f,
		0.1f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[3] = PointLight(1.0f, 0.7f, 0.0f,
		0.2f, 0.2f,
		2.0f, 1.5f, 1.5f,
		0.1f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[4] = PointLight(1.0f, 0.7f, 0.0f,
		0.2f, 0.2f,
		2.0f, 1.5f, 1.5f,
		0.1f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[5] = PointLight(1.0f, 0.7f, 0.0f,
		0.2f, 0.2f,
		2.0f, 1.5f, 1.5f,
		0.1f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[6] = PointLight(1.0f, 0.7f, 0.0f,
		0.2f, 0.2f,
		2.0f, 1.5f, 1.5f,
		0.1f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[7] = PointLight(1.0f, 0.7f, 0.0f,
		0.2f, 0.2f,
		2.0f, 1.5f, 1.5f,
		0.1f, 0.2f, 0.1f);
	pointLightCount++;

	//Lamparas de piso
	pointLights[8] = PointLight(0.7f, 0.7f, 0.0f,
		0.2f, 0.2f,
		2.0f, 1.5f, 1.5f,
		0.1f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[9] = PointLight(0.7f, 0.7f, 0.0f,
		0.2f, 0.2f,
		2.0f, 1.5f, 1.5f,
		0.1f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[10] = PointLight(1.0f, 0.0f, 0.1f,
		0.5f, 0.5f,
		2.0f, 1.5f, 1.5f,
		0.1f, 0.2f, 0.1f);
	pointLightCount++;

	/////Casa de cofre
	pointLights[11] = PointLight(0.7f, 0.7f, 0.0f,
		0.2f, 0.2f,
		2.0f, 1.5f, 1.5f,
		0.1f, 0.2f, 0.1f);
	pointLightCount++;

	/////Casa de objetos flotantes
	pointLights[12] = PointLight(0.7f, 0.7f, 0.0f,
		0.2f, 0.2f,
		2.0f, 1.5f, 1.5f,
		0.1f, 0.2f, 0.1f);
	pointLightCount++;

	/////Sacrificios
	pointLights[13] = PointLight(0.7f, 0.7f, 0.0f,
		0.2f, 0.2f,
		2.0f, 1.5f, 1.5f,
		0.1f, 0.2f, 0.1f);
	pointLightCount++;

	/////Pasillo
	pointLights[14] = PointLight(0.7f, 0.7f, 0.0f,
		0.2f, 0.2f,
		2.0f, 1.5f, 1.5f,
		0.1f, 0.2f, 0.1f);
	pointLightCount++;


	unsigned int spotLightCount = 0;


	//linterna global
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		2.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//Lampara tori

	spotLights[1] = SpotLight(1.0f, 0.3f, 0.0f,
		10.0f, 10.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -0.5f, -0.0f,
		0.1f, 0.2f, 0.1f,
		70.0f);
	spotLightCount++;

	spotLights[2] = SpotLight(1.0f, 0.3f, 0.0f,
		10.0f, 10.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -0.5f, -0.0f,
		0.1f, 0.2f, 0.1f,
		70.0f);
	spotLightCount++;

	spotLights[3] = SpotLight(1.0f, 0.3f, 0.0f,
		10.0f, 10.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -0.5f, -0.0f,
		0.1f, 0.2f, 0.1f,
		70.0f);
	spotLightCount++;

	spotLights[4] = SpotLight(1.0f, 0.3f, 0.0f,
		10.0f, 10.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -0.5f, -0.0f,
		0.1f, 0.2f, 0.1f,
		70.0f);
	spotLightCount++;

	spotLights[5] = SpotLight(1.0f, 0.3f, 0.0f,
		10.0f, 10.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -0.5f, -0.0f,
		0.1f, 0.2f, 0.1f,
		70.0f);
	spotLightCount++;

	spotLights[6] = SpotLight(1.0f, 0.3f, 0.0f,
		10.0f, 10.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -0.5f, -0.0f,
		0.1f, 0.2f, 0.1f,
		70.0f);
	spotLightCount++;

	//Luces de invocacion
	spotLights[7] = SpotLight(1.0f, 0.3f, 0.0f,
		3.0f, 3.0f,
		1.781f, 4.0f, 109.0f,
		-0.5f, -0.5f, 0.0f,
		0.1f, 0.2f, 0.1f,
		70.0f);
	spotLightCount++;

	spotLights[8] = SpotLight(1.0f, 0.3f, 0.0f,
		3.0f, 3.0f,
		-1.781f, 4.0f, 109.0f,
		0.5f, -0.5f, 0.0f,
		0.1f, 0.2f, 0.1f,
		70.0f);
	spotLightCount++;

	spotLights[9] = SpotLight(0.4f, 0.3f, 0.6f,
		3.0f, 3.0f,
		0.0f, 4.0f, 111.0f,
		0.0f, -0.5f, -0.5f,
		0.1f, 0.2f, 0.1f,
		70.0f);
	spotLightCount++;

	spotLights[10] = SpotLight(1.0f, 0.0f, 1.0f,
		3.0f, 3.0f,
		28.082f, 3.6624f, 23.996f,
		0.5f, -0.5f, 0.3f,
		0.1f, 0.2f, 0.1f,
		70.0f);
	spotLightCount++;

	spotLights[11] = SpotLight(1.0f, 0.0f, 1.0f,
		3.0f, 3.0f,
		28.082f, 3.6624f, 26.251f,
		0.5f, -0.5f, -0.3f,
		0.1f, 0.2f, 0.1f,
		70.0f);
	spotLightCount++;

	///Casa de cosas flotantes

	spotLights[12] = SpotLight(0.6f, 0.5f, 1.0f,
		3.0f, 3.0f,
		17.584f, 3.8812f, 73.47f,
		0.5f, -0.5f, -0.3f,
		0.04f, 0.08f, 0.04f,
		70.0f);
	spotLightCount++;

	spotLights[13] = SpotLight(0.6f, 0.5f, 1.0f,
		3.0f, 3.0f,
		17.584f, 3.8812f, 60.517f,
		0.5f, -0.5f, 0.3f,
		0.04f, 0.08f, 0.04f,
		70.0f);
	spotLightCount++;

	//Arboles
	std::vector<glm::vec3> posicionArboles;
	std::vector<int> tipoArboles;
	std::vector<std::vector<int>> limitesArboles = { { 36,48,13,63 },
													 {35,41,63,98},
													 {9,42,102,111},
													{-42,-9,102,111},
													{-45,-34,51,92}
	};

	int Ax, Az = 0;

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)

	for (std::vector<int> limite : limitesArboles) {
		std::uniform_int_distribution<int> randx(limite[0], limite[1]);
		std::uniform_int_distribution<int> randz(limite[2], limite[3]);
		std::uniform_int_distribution<int> randi(0, 2);
		for (int i = 0; i < 30; i++) {

			Ax = randx(rng);
			Az = randz(rng);
			posicionArboles.push_back(glm::vec3(Ax, 4.0f, Az));
			tipoArboles.push_back(randi(rng));
		}
	}


	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		//camera.keyControl(mainWindow.getsKeys(), deltaTime);
		player.mouseControl(mainWindow.getXChange());
		player.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.update(mainWindow.getIsometric());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		if (day) {
			skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		else {
			skybox2.DrawSkybox(camera.calculateViewMatrix(), projection);
		}

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		eventManager.Update(mainWindow.getAction(), player.pos);

		// luz ligada a la cámara de tipo flash
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		daytime += deltaTime * 0.1f;

		if (daytime > 360) {
			daytime = 0;
		}

		if (daytime > 10 && daytime < 210) {
			daytimeLightpointLights = 0.0f;
			daytimeLightspointLights = 0.0f;
			day = true;
		}
		else {
			daytimeLightpointLights = 0.2f;
			daytimeLightspointLights = 10.0f;
			day = false;
		}

		//Main Light
		mainLight.Use(1.0f, 0.1f*sin(daytime*toRadians) + 0.8f, 0.3*sin(daytime*toRadians) + 0.5f,
			0.25 * sin(daytime*toRadians) + 0.5, 0.25 * sin(daytime*toRadians) + 0.5,
			0.5*cos(daytime*toRadians), -abs(0.5*sin(daytime*toRadians)), 0);
		

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		//Definicion de avatar

		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		player.RenderKaishi(uniformColor,uniformModel);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		////////////Terreno///////

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Terreno.RenderModel();

		//////////////Casa Muñeca y niña////////////////


		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(25.617f, 4.0f, 25.26f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casa.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(23.226f, 0.9742f, 25.115f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Desktop.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, posVodoo);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(scaleVodoo, scaleVodoo, scaleVodoo));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Vodoo.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(27.758f, 2.2576f, 30.313f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Walls.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model,posDoor1);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Door.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, posDoor2);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Door.RenderModel();


		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(32.903f, 0.9577f, 25.115f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Chest.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(33.661f, 2.1387f, 25.115f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, angTape * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		ChestTape.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model,posGhost);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, angGhost * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(scaleGhost, scaleGhost, scaleGhost));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Ghost.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(22.0f, 1.0f, 24.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LamparaPapel.RenderModel();

		pointLights[11].SetPos(glm::vec3(modelaux[3][0], modelaux[3][1] + 0.5f, modelaux[3][2]));
		pointLights[11].SetIntensity(LightIntensity_E4);

		spotLights[10].SetIntensity(DemonLightIntensity_E4, DemonLightIntensity_E4);

		spotLights[11].SetIntensity(DemonLightIntensity_E4, DemonLightIntensity_E4);

		//////////////Casa se pasillo////////////////

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-23.752f, 4.0f, 46.81f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casa.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-23.122f, 2.31f, 46.838f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		WallsPasillo.RenderModel();


		model = glm::mat4(1.0);

		model = glm::translate(model,posChaser);
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, angChaser - (90*toRadians) , glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-desplazamientoChaser, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(chaserScale, chaserScale, chaserScale));

		posChaser.x = model[3][0];
		posChaser.y = model[3][1];
		posChaser.z = model[3][2];

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Chaser.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-29.234f, 1.0f, 46.613f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LamparaPapel.RenderModel();

		pointLights[14].SetPos(glm::vec3(modelaux[3][0], modelaux[3][1] + 0.5f, modelaux[3][2]));
		pointLights[14].SetIntensity(LightIntensity_E5);

		///////////////Casa de cosas flotantes///////////////

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(25.617f, 4.0f, 66.751f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casa.RenderModel();

		for (ObjetosFlotantes &f : flotantes) {
			f.Render(uniformModel, uniformColor);
		}

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(15.0f, 1.0f, 68.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LamparaPapel.RenderModel();

		pointLights[12].SetPos(glm::vec3(modelaux[3][0], modelaux[3][1] + 0.5f, modelaux[3][2]));
		pointLights[12].SetIntensity(LightIntensity_E3);

		spotLights[12].SetIntensity(LightIntensitySpotLight_E3, LightIntensitySpotLight_E3);
		spotLights[13].SetIntensity(LightIntensitySpotLight_E3, LightIntensitySpotLight_E3);


		//////////////Casa invocacion///////////////////

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(0.0f, 4.29f, 106.51f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casa.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(2.2477f, 1.2448f, 112.11f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LamparaPapel.RenderModel();

		pointLights[8].SetPos(glm::vec3(modelaux[3][0], modelaux[3][1] + 0.5f, modelaux[3][2]));
		pointLights[8].SetIntensity(intensityFloor);


		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-2.2477f, 1.2448f, 112.11f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LamparaPapel.RenderModel();

		pointLights[9].SetPos(glm::vec3(modelaux[3][0], modelaux[3][1] + 0.5f, modelaux[3][2]));
		pointLights[9].SetIntensity(intensityFloor);

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(0.0f, 1.6328f, 113.87f));
		modelaux = model;
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Oni.RenderModel();

		pointLights[10].SetPos(glm::vec3(modelaux[3][0], modelaux[3][1], modelaux[3][2] + 0.5f));
		pointLights[10].SetIntensity(intensityOni);

		spotLights[7].SetIntensity(intensityThree, intensityThree);
		spotLights[7].SetFlash(glm::vec3(Light1posx, 4.0f, Light1posz), glm::vec3(Light1angx, -0.5f, Light1angz));
		spotLights[7].SetColor(glm::vec3(1.0,1.0,colorLight1));

		spotLights[8].SetIntensity(intensityThree, intensityThree);
		spotLights[8].SetFlash(glm::vec3(Light2posx, 4.0f, Light2posz), glm::vec3(Light2angx, -0.5f, Light2angz));
		spotLights[8].SetColor(glm::vec3(1.0, colorLight2, 1.0));

		spotLights[9].SetIntensity(intensityThree, intensityThree);
		spotLights[9].SetFlash(glm::vec3(Light3posx, 4.0f, Light3posz), glm::vec3(Light3angx, -0.5f, Light3angz));
		spotLights[9].SetColor(glm::vec3(colorLight3, 1.0, 1.0));

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0,1.4f,110.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		KanjiTexture.UseTexture();
		meshList[1]->RenderMesh();
		glDisable(GL_BLEND);


		//////////////Lamparas///////////////////

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(14.766f, 0.9745f, 16.455f));

		modelaux = model;

		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Lampara.RenderModel();

		pointLights[0].SetPos(glm::vec3(modelaux[3][0], modelaux[3][1] + 2.3f, modelaux[3][2]));
		pointLights[0].SetIntensity(daytimeLightpointLights);

		/////1

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(14.766f, 0.9745f, 33.642f));
		modelaux = model;

		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Lampara.RenderModel();

		pointLights[1].SetPos(glm::vec3(modelaux[3][0], modelaux[3][1] + 2.3f, modelaux[3][2]));
		pointLights[1].SetIntensity(daytimeLightpointLights);
		
		/////2

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(14.766f, 0.9745f, 58.161f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Lampara.RenderModel();

		pointLights[2].SetPos(glm::vec3(modelaux[3][0], modelaux[3][1] + 2.3f, modelaux[3][2]));
		pointLights[2].SetIntensity(daytimeLightpointLights);

		/////3

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(14.766f, 0.9745f, 75.65f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Lampara.RenderModel();

		pointLights[3].SetPos(glm::vec3(modelaux[3][0], modelaux[3][1] + 2.3f, modelaux[3][2]));
		pointLights[3].SetIntensity(daytimeLightpointLights);


		/////4

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(9.158f, 0.9745f, 95.79f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Lampara.RenderModel();

		pointLights[4].SetPos(glm::vec3(modelaux[3][0], modelaux[3][1] + 2.3f, modelaux[3][2]));
		pointLights[4].SetIntensity(daytimeLightpointLights);

		/////5

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-9.158f, 0.9745f, 95.79f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Lampara.RenderModel();

		pointLights[5].SetPos(glm::vec3(modelaux[3][0], modelaux[3][1] + 2.3f, modelaux[3][2]));
		pointLights[5].SetIntensity(daytimeLightpointLights);

		/////6

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-13.749f, 0.9745f, 55.046f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Lampara.RenderModel();

		pointLights[6].SetPos(glm::vec3(modelaux[3][0], modelaux[3][1] + 2.3f, modelaux[3][2]));
		pointLights[6].SetIntensity(daytimeLightpointLights);

		/////7

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-13.749f, 0.9745f, 37.911f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Lampara.RenderModel();

		pointLights[7].SetPos(glm::vec3(modelaux[3][0], modelaux[3][1] + 2.3f, modelaux[3][2]));
		pointLights[7].SetIntensity(daytimeLightpointLights);

		////////////////////Tori////////////////

		//0
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(0.0f, 10.975f, 34.004f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Tori.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(3.7151f, 5.0371f, 34.442f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LamparaTori.RenderModel();

		spotLights[1].SetFlash(glm::vec3(modelaux[3][0], modelaux[3][1] + 1.5, modelaux[3][2]),
								glm::vec3(0.0, -1.0f, 0.0f));
		spotLights[1].SetIntensity(daytimeLightspointLights, daytimeLightspointLights);

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-3.7151f, 5.0371f, 34.442f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LamparaTori.RenderModel();

		spotLights[2].SetFlash(glm::vec3(modelaux[3][0], modelaux[3][1] + 1.5, modelaux[3][2]),
			glm::vec3(0.0, -1.0f, 0.0f));
		spotLights[2].SetIntensity(daytimeLightspointLights, daytimeLightspointLights);



		//1
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(0.0f, 10.975f, 56.476f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Tori.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(3.7151f, 5.0371f, 56.838f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LamparaTori.RenderModel();

		spotLights[3].SetFlash(glm::vec3(modelaux[3][0], modelaux[3][1] + 1.5, modelaux[3][2]),
			glm::vec3(0.0, -1.0f, 0.0f));
		spotLights[3].SetIntensity(daytimeLightspointLights, daytimeLightspointLights);

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-3.7151f, 5.0371f, 56.838f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LamparaTori.RenderModel();

		spotLights[4].SetFlash(glm::vec3(modelaux[3][0], modelaux[3][1] + 1.5, modelaux[3][2]),
			glm::vec3(0.0, -1.0f, 0.0f));

		spotLights[4].SetIntensity(daytimeLightspointLights, daytimeLightspointLights);



		//2
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(0.0f, 10.975f, 75.672f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Tori.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(3.7151f, 5.0371f, 76.158f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LamparaTori.RenderModel();

		spotLights[5].SetFlash(glm::vec3(modelaux[3][0], modelaux[3][1] + 1.5, modelaux[3][2]),
			glm::vec3(0.0, -1.0f, 0.0f));
		spotLights[5].SetIntensity(daytimeLightspointLights, daytimeLightspointLights);

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-3.7151f, 5.0371f, 76.158f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LamparaTori.RenderModel();

		spotLights[6].SetFlash(glm::vec3(modelaux[3][0], modelaux[3][1] + 1.5, modelaux[3][2]),
			glm::vec3(0.0, -1.0f, 0.0f));

		spotLights[6].SetIntensity(daytimeLightspointLights, daytimeLightspointLights);

		////////////////////Valla////////////////


		//0
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(34.402f, 0.650f, 46.201f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Valla.RenderModel();

		//1
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(33.727f, 0.650f, 87.291f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Valla.RenderModel();

		//2
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(21.203f, 0.650f, 100.19f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Valla.RenderModel();

		//3
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-20.815f, 0.650f, 100.19f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Valla.RenderModel();

		//4
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-33.361f, 0.650f, 87.291f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Valla.RenderModel();

		//5
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-33.361f, 0.650f, 62.556f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Valla.RenderModel();

		//6
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-33.361f, 0.650f, 27.112f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Valla.RenderModel();


		///////////Tumbas////////////
		
		//0
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(19.812f, 1.0516f, 38.974f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Tumba.RenderModel();

		//1
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(19.812f, 1.0516f, 46.286f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Tumba.RenderModel();

		//2
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(19.812f, 1.0516f, 53.38f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Tumba.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(30.0f, 0.71988f, 46.941f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Mausoleo.RenderModel();

		/////////Arboles/////////

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		for (int i = 0; i < posicionArboles.size(); i++) {

			model = glm::mat4(1.0);
			model = glm::translate(model,posicionArboles[i]);
			model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			//blending: transparencia o traslucidez
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			ArbolTexture[tipoArboles[i]].UseTexture();
			//Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[0]->RenderMesh();
			glDisable(GL_BLEND);
		}

		/////////////Sacrificio////////////


		//Postes
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-10.849f, 0.8745f, 77.491f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Poste.RenderModel();


		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-26.568f, 0.8745f, 69.666f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Poste.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-26.751f, 0.8745f, 84.622f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Poste.RenderModel();

		//Cuerdas
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-11.281f, 10.493f, 77.479f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		model = glm::rotate(model, angCuerdas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, angTamboleoCuerdas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Rope.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-26.554f, 10.493f, 84.115f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 50 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		model = glm::rotate(model, angCuerdas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, angTamboleoCuerdas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));


		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Rope.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-26.277f, 10.493f, 70.051f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, -52 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		model = glm::rotate(model, angCuerdas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, angTamboleoCuerdas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Rope.RenderModel();

		//Zombie
		model = glm::mat4(1.0);

		model = glm::translate(model, posZombie);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		model = glm::rotate(model, angZombie * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Zombie.RenderModel();
		
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-14.0f, 1.0f, 68.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LamparaPapel.RenderModel();

		pointLights[13].SetPos(glm::vec3(modelaux[3][0], modelaux[3][1] + 0.5f, modelaux[3][2]));
		pointLights[13].SetIntensity(LightIntensity_E2);



		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}