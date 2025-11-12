#include "Window.h"
#include "Camera.h"
#include <stdio.h>
#include <cmath>

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	rotax = 0.0f;
	rotay = 0.0f;
	rotaz = 0.0f;
	carPos = 0.0f;
	porticullisPos = 0.0f;
	prendeLuzAtras = false;
	prendeLuzEnfrente = false;
	prendeLuzLinterna = true;
prendeDiablo = false;
	prendePoste = true;
	animandoPuerta = false;
	abriendoPuerta = true;
	primerGiro = true;
	animandoDado = false;
	dadoEnAire = false;
	dadoAng = glm::radians(71.0f);
	dadoDir = glm::vec3(0.0f);
	dadoPos = glm::vec3(0.0f);
	dadoMat = glm::mat4(1.0f);
	oldDadoMat = glm::mat4(1.0f);
	deslizPos = glm::vec3(0.0f);
	carVel = 0.0f;
	blackHawkVel = 0.0f;
	porticullisVel = 0.0f;
	maxvel = 10.0f;
	articulacion1 = 0.0f;
	articulacion2 = 0.0f;
	articulacion3 = 0.0f;
	articulacion4 = 0.0f;
	articulacion5 = 0.0f;
	articulacion6 = 0.0f;
	angparam = 0.0f;

        beastie.t = 0.0f;
        beastie.anguloGiro = 0.0f;
        beastie.anguloLlanta = 0.0f;
        beastie.anguloVuelta = 0.0f;
        beastie.orig = glm::vec3(1.0f);
	beastie.pos = beastie.orig;
	
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Proyecto final", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);

        return 0;
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::UpdateBeastie(float dt) {
	beastie.t += dt;

	beastie.oldoldpos = beastie.oldpos;
	beastie.oldpos = beastie.pos;

        // beastie.pos = glm::vec3(10.0f * cos(beastie.t), 0.0f, 15.0f * sin(beastie.t));
        beastie.pos = glm::vec3(20.0f * cos(beastie.t), 0.0f, 50.0f * sin(0.666f * beastie.t));
	beastie.pos += beastie.orig;

	glm::vec3 diff = beastie.pos - beastie.oldpos;
	glm::vec3 khat = glm::vec3(0.0f, 0.0f, 1.0f);

        beastie.anguloGiro = atan2(diff.x, diff.z) + 3.1415;
}

void Window::UpdateAngles(float dt)
{
	angparam += dt;
	articulacion5 = 15 * sin(2*angparam) - 15;

	articulacion1 = 45 * sin(3*angparam);
	articulacion2 = 45 * sin(3*angparam + 90.0f * (3.141592f / 180.0f));
	articulacion4 = 45 * sin(3*angparam + 125.0f * (3.141592f / 180.0f));
	articulacion3 = 45 * sin(3*angparam + 30.0f * (3.141592f / 180.0f));
}

void Window::UpdatePos(float dt)
{
	carPos += carVel * dt;
	blackHawkPos += blackHawkVel * dt;
	float circunf = 2.0f * 3.141592 * 25.0f / 16.0f;
	articulacion1 = -2.0f * 3.141592 * carPos / circunf;

	if (animandoPuerta) {
		if (abriendoPuerta && articulacion6 >= 90.0f) {
			articulacion6 = 90.0f;
			animandoPuerta = false;
		} else if (!abriendoPuerta && articulacion6 <= 0.0f) {
			articulacion6 = 0.0f;
			deslizPos = glm::vec3(0.0f);
			animandoPuerta = false;
		} else if (abriendoPuerta) {
			articulacion6 += 90.0f * dt;
			if (glm::length(deslizPos) < 1.0f) {
				deslizPos.z -= maxvel * dt / 4.0f;
			} else {
				deslizPos.x += maxvel * dt / 4.0f;
			}
		} else if (!abriendoPuerta) {
			articulacion6 -= 90.0f * dt;
			if (glm::length(deslizPos) < 1.05f) {
				deslizPos -= glm::normalize(deslizPos) * ( maxvel * dt / 4.0f);
			} else {
				deslizPos.x -= maxvel * dt / 4.0f;
			}
		}
	}
}

void Window::UpdateDado(float dt) {
	if (!dadoEnAire) {
		dadoAng += dadoVel * dt;
		glm::mat4 rot = glm::rotate(glm::mat4(1.0f), dadoAng, dadoDir);

		dadoMat = rot * oldDadoMat;

		rot = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		dadoPos += glm::vec3(rot * glm::vec4(dadoDir.x, dadoDir.y, dadoDir.z, 1.0f)) * glm::cos(dadoAng) * dadoVel * dt;
        } else {
		dadoVel -= 30.0f * dt;
		dadoPos.y += dadoVel * dt;
                if (dadoPos.y <= 0.0f) {
			dadoPos.y = 0.0f;
			dadoEnAire = false;
			dadoVel = 15.0f;
		}
	}
}

void Window::UpdateDadoDir(glm::vec3 dir) {
	if (!primerGiro) {
		glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(70.52877f), dadoDir);
		oldDadoMat = rot * oldDadoMat;
        } else {
		primerGiro = false;
	}
	dadoAng = 0.0f;
        dadoDir = dir;
        dadoVel -= 1.0;
        if (dadoVel <= 0.0f) {
		animandoDado = false;
		dadoVel = 0.0;
	}
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	
	if (key == GLFW_KEY_E) {
		theWindow->rotax += 10.0;
	}
	if (key == GLFW_KEY_R) {
		theWindow->rotay += 10.0; //rotar sobre el eje y 10 grados
	}
	if (key == GLFW_KEY_T) {
		theWindow->rotaz += 10.0;
	}


	if (key == GLFW_KEY_H) {
		// recorrido
		theWindow->camera->startRig();
	}
	if (key == GLFW_KEY_J) {
		theWindow->camera->setEstado(THIRD_PERSON_CAMERA);
	}
	if (key == GLFW_KEY_K) {
		// Libre
		theWindow->camera->setEstado(FREE_CAMERA);
	}
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		theWindow->camera->goToNextLocation();
	}

	if (key == GLFW_KEY_I) {
		theWindow->prendeDiablo = true;
	}
	if (key == GLFW_KEY_O) {
		theWindow->prendeDiablo = false;
	}


        if (key == GLFW_KEY_Y) {
		theWindow->prendePoste = true;
        }
        if (key == GLFW_KEY_U) {
		theWindow->prendePoste = false;
	}

	// Puerta
        if (key == GLFW_KEY_N) {
		if (!theWindow->animandoPuerta && !theWindow->animandoPuerta) {
			theWindow->abriendoPuerta = !theWindow->abriendoPuerta;
			theWindow->animandoPuerta = true;
		}
	}

        if (key == GLFW_KEY_M) {
		if (!theWindow->animandoDado) {
			theWindow->animandoDado = true;
			theWindow->dadoVel = 40.0f;
			theWindow->dadoEnAire = true;
		}
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}

void Window::setCamera(Camera *cam) {
	camera = cam;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
