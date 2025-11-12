#pragma once
#include "Camera.h"
#include<stdio.h>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
        void setCamera(Camera *cam);
	GLfloat getrotay() { return rotay; }
	GLfloat getrotax() { return rotax; }
	GLfloat getrotaz() { return rotaz; }
	GLfloat getarticulacion1() { return articulacion1; }
	GLfloat getarticulacion2() { return articulacion2; }
	GLfloat getarticulacion3() { return articulacion3; }
	GLfloat getarticulacion4() { return articulacion4; }
	GLfloat getarticulacion5() { return articulacion5; }
	GLfloat getarticulacion6() { return articulacion6; }
	GLfloat getCarPos() { return carPos; }
	GLfloat getBlackHawkPos() { return blackHawkPos; }
	glm::vec3 getDeslizPos() { return deslizPos; }
	glm::vec3 getDadoPos() { return dadoPos; }
	glm::vec3 getBeastiePos() { return beastie.pos; }
	GLfloat getBeastieAnguloGiro() { return beastie.anguloGiro; }
	void UpdateAngles(float dt);
	void UpdatePos(float dt);
	void UpdateDado(float dt);
	void UpdateBeastie(float dt);
	void UpdateDadoDir(glm::vec3 dir);
	void UpdateBeastie(glm::vec3 dir);
	bool getPrendeLuzLinterna() { return prendeLuzLinterna; }
	bool getPrendeLuzEnfrente() { return prendeLuzEnfrente; }
	bool getPrendeLuzAtras() { return prendeLuzAtras; }
	bool getPrendeDiablo() { return prendeDiablo; }
	bool getPrendePoste() { return prendePoste; }
	bool getPrendeLuzCofre() { return articulacion5 != 0.0f; }
	bool getAnimandoDado() { return animandoDado; }
	GLfloat getDadoAng() { return dadoAng; }
	GLfloat getDadoVel() { return dadoVel; }
	glm::mat4 getDadoMat() { return dadoMat; }

	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	GLfloat carPos, blackHawkPos, porticullisPos, carVel, blackHawkVel, porticullisVel, maxvel;
	GLfloat rotax,rotay,rotaz, articulacion1, articulacion2, articulacion3, articulacion4, articulacion5, articulacion6;
	GLfloat dadoVel;
	struct {
		glm::vec3 pos;
		glm::vec3 oldpos;
		glm::vec3 oldoldpos;
		glm::vec3 orig;
		GLfloat anguloLlanta;
		GLfloat anguloVuelta;
		GLfloat anguloGiro;
		GLfloat t;

	} beastie;
        // struct {

	// } pajaro;
	GLfloat angparam;
	bool keys[1024];
	bool prendeLuzLinterna, prendeLuzEnfrente, prendeLuzAtras, prendeLuz, prendeDiablo, prendePoste;
	bool animandoPuerta, abriendoPuerta, animandoDado;
	GLint bufferWidth, bufferHeight;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat dadoAng;
	Camera *camera;
	glm::vec3 deslizPos, dadoDir, dadoPos;
	glm::mat4 dadoMat, oldDadoMat;
	bool primerGiro, dadoEnAire;
	bool mouseFirstMoved;
	void createCallbacks();
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
}; 
