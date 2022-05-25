#include "ToroideP.h"

ToroideP::ToroideP(float rMayor, float rMenor, int pila, int cara) :
	rMayor(rMayor), rMenor(rMenor), pila(pila), cara(cara) {

}

ToroideP::ToroideP() {

}

ToroideP::~ToroideP() {

}

void ToroideP::init() {
	std::vector<GLfloat> verticeCara;
	std::vector<GLuint> indice;

	const float toRadians = 3.14159265f / 180.0f;

	for (int i = 0; i < pila; i++) {
		float V = 360.0f / (float)pila;
		float beta = i * V * toRadians;

		float equis = i * (1.0f / (pila - 1.0f));

		for (int j = 0; j < cara; j++) {

			float U = 360.0f / (float)cara;

			float ye = j * (1.0f / (cara - 1.0f));

			float alfa = j * U * toRadians;

			float X = (rMayor + rMenor * cos(alfa)) * cos(beta);
			float Y = rMenor * sin(alfa);
			float Z = (rMayor + rMenor * cos(alfa)) * sin(beta);

			verticeCara.push_back(X);
			verticeCara.push_back(Y);
			verticeCara.push_back(Z);

			float X2 = rMayor * cos(beta);
			float Z2 = rMenor * sin(beta);

			verticeCara.push_back(equis);
			verticeCara.push_back(ye);

			verticeCara.push_back(X2 - X);
			verticeCara.push_back(-Y);
			verticeCara.push_back(Z2 - Z);

		}
	}

	for (int L = 0; L < pila; L++) {
		for (int S = 0; S < cara; S++) {

			int t_izquierda_abajo = L * cara + S;
			indice.push_back(t_izquierda_abajo);

			int t_derecha_abajo = (t_izquierda_abajo + cara) % (pila * cara);
			indice.push_back(t_derecha_abajo);

			int t_izquierda_arriba = (t_izquierda_abajo + 1) % (pila * cara);
			indice.push_back(t_izquierda_arriba);


			indice.push_back(t_izquierda_arriba);
			indice.push_back(t_derecha_abajo);

			int t_derecha_arriba = (t_derecha_abajo + 1) % (pila * cara);
			indice.push_back(t_derecha_arriba);
		}
	}

	mesh = Mesh();
	mesh.CreateMesh(&verticeCara[0], &indice[0], verticeCara.size(), indice.size());
}

void ToroideP::render() {
	mesh.RenderMesh();
}