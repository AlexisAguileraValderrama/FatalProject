#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();

	bool getAction() { return actionState; }

	GLfloat getmuevex() { return muevex; }
	GLfloat getmuevey() { return muevey; }
	GLfloat getmuevez() { return muevez; }

	bool IsLightOneTurnOn() { return isLightOneTurnOn; }
	bool IsLightTwoTurnOn() { return isLightTwoTurnOn; }
	bool IsLightOn() { return isLightOn; }

	bool IsFarward() { return isFarward; }
	bool IsBackward() { return isBackward; }

	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }

	bool getIsometric() { return isIsometric; }
	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	GLfloat muevey;
	GLfloat muevez;

	bool isLightOneTurnOn = true;
	bool isLightTwoTurnOn = true;
	bool isLightOn = true;

	bool isFarward = false;
	bool isBackward = false;

	bool actionState = false;

	bool isIsometric = false;

	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

