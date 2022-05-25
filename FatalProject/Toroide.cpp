#include "Toroide.h"


Toroide::Toroide(float radioMayor, float radioMenor, int stacks, int segments) :
	radioMayor(radioMayor), radioMenor(radioMenor), stacks(stacks), segments(segments) {

}
Toroide::Toroide() {

}

Toroide::~Toroide() {


}



void Toroide::init() {

	const float toRadians = 3.14159265f / 180.0f;

	for (int i = 0; i < stacks; i++) {
		float V = 360.0f / (float)stacks;
		float beta = i * V * toRadians;

		float equis = i * (1.0f / (stacks - 1.0f));

		for (int j = 0; j < segments; j++) {

			float U = 360.0f / (float)segments;

			float ye = j * (1.0f / (segments - 1.0f));

			//Punto izquierda abajo
			float alfa = j * U * toRadians;
			beta = i * V * toRadians;
			equis = i * (1.0f / (stacks - 1.0f));

			float X = (radioMayor + radioMenor * cos(alfa)) * cos(beta);
			float Y = radioMenor * sin(alfa);
			float Z = (radioMayor + radioMenor * cos(alfa)) * sin(beta);

			float X2 = radioMayor * cos(beta);
			float Z2 = radioMayor * sin(beta);

			vertexC.push_back(X);
			vertexC.push_back(Y);
			vertexC.push_back(Z);

			vertexC.push_back(equis*2);
			vertexC.push_back(ye/4);

			vertexC.push_back(X2 - X);
			vertexC.push_back(-Y);
			vertexC.push_back(Z2 - Z);

			///Punto derecha abajo
			alfa = j * U * toRadians;
			beta = (i + 1) * V * toRadians;
			equis = (i + 1) * (1.0f / (stacks - 1.0f));
			ye = j * (1.0f / (segments - 1.0f));

			X = (radioMayor + radioMenor * cos(alfa)) * cos(beta);
			Y = radioMenor * sin(alfa);
			Z = (radioMayor + radioMenor * cos(alfa)) * sin(beta);

			X2 = radioMayor * cos(beta);
			Z2 = radioMayor * sin(beta);

			vertexC.push_back(X);
			vertexC.push_back(Y);
			vertexC.push_back(Z);

			vertexC.push_back(equis*2);
			vertexC.push_back(ye/4);

			vertexC.push_back(X2 - X);
			vertexC.push_back(-Y);
			vertexC.push_back(Z2 - Z);

			///Punto izquierda arriba
			alfa = (j + 1) * U * toRadians;
			beta = i * V * toRadians;
			equis = i * (1.0f / (stacks - 1.0f));
			ye = (j + 1) * (1.0f / (segments - 1.0f));

			X = (radioMayor + radioMenor * cos(alfa)) * cos(beta);
			Y = radioMenor * sin(alfa);
			Z = (radioMayor + radioMenor * cos(alfa)) * sin(beta);

			X2 = radioMayor * cos(beta);
			Z2 = radioMayor * sin(beta);

			vertexC.push_back(X);
			vertexC.push_back(Y);
			vertexC.push_back(Z);

			vertexC.push_back(equis*2);
			vertexC.push_back(ye/4);

			vertexC.push_back(X2 - X);
			vertexC.push_back(-Y);
			vertexC.push_back(Z2 - Z);

			///Segunda cara

			//Punto izquierda abajo
			alfa = (j + 1) * U * toRadians;
			beta = i * V * toRadians;
			equis = i * (1.0f / (stacks - 1.0f));
			ye = (j + 1) * (1.0f / (segments - 1.0f));

			X = (radioMayor + radioMenor * cos(alfa)) * cos(beta);
			Y = radioMenor * sin(alfa);
			Z = (radioMayor + radioMenor * cos(alfa)) * sin(beta);

			X2 = radioMayor * cos(beta);
			Z2 = radioMayor * sin(beta);

			vertexC.push_back(X);
			vertexC.push_back(Y);
			vertexC.push_back(Z);

			vertexC.push_back(equis*2);
			vertexC.push_back(ye/4);

			vertexC.push_back(X2 - X);
			vertexC.push_back(-Y);
			vertexC.push_back(Z2 - Z);

			///Punto derecha abajo
			alfa = j * U * toRadians;
			beta = (i + 1) * V * toRadians;
			equis = (i + 1) * (1.0f / (stacks - 1.0f));
			ye = j * (1.0f / (segments - 1.0f));

			X = (radioMayor + radioMenor * cos(alfa)) * cos(beta);
			Y = radioMenor * sin(alfa);
			Z = (radioMayor + radioMenor * cos(alfa)) * sin(beta);

			X2 = radioMayor * cos(beta);
			Z2 = radioMayor * sin(beta);

			vertexC.push_back(X);
			vertexC.push_back(Y);
			vertexC.push_back(Z);

			vertexC.push_back(equis*2);
			vertexC.push_back(ye/4);

			vertexC.push_back(X2 - X);
			vertexC.push_back(-Y);
			vertexC.push_back(Z2 - Z);


			///Punto derecha arriba
			alfa = (j + 1) * U * toRadians;
			beta = (i + 1) * V * toRadians;
			equis = (i + 1) * (1.0f / (stacks - 1.0f));
			ye = (j + 1) * (1.0f / (segments - 1.0f));

			X = (radioMayor + radioMenor * cos(alfa)) * cos(beta);
			Y = radioMenor * sin(alfa);
			Z = (radioMayor + radioMenor * cos(alfa)) * sin(beta);

			X2 = radioMayor * cos(beta);
			Z2 = radioMayor * sin(beta);

			vertexC.push_back(X);
			vertexC.push_back(Y);
			vertexC.push_back(Z);

			vertexC.push_back(equis*2);
			vertexC.push_back(ye/4);

			vertexC.push_back(X2 - X);
			vertexC.push_back(-Y);
			vertexC.push_back(Z2 - Z);

		}
	}

	for (int L = 0; L < vertexC.size() / 8; L++) {
		index.push_back(L);
	}


	mesh.CreateMesh(&vertexC[0], &index[0], vertexC.size(), index.size());
}

void Toroide::render() {

	mesh.RenderMesh();
}