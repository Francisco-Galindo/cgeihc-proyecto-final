/*
 Proyecto final para Computación Gráfica e Interacción Humano - Computadora
*/

//para cargar imagen
#include "Avatar.hpp"
#include "MovingEntity.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <cerrno>
#include <math.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"
#include "Beastie.hpp"
#include "Xue.hpp"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//variables para animación
float movCoche;
float movOffset;
float rotllanta;
float rotllantaOffset;
bool avanza;
float toffsetflechau = 0.0f;
float toffsetflechav = 0.0f;
float toffsetnumerou = 0.0f;
float toffsetnumerov = 0.0f;
float toffsetnumerocambiau = 0.0;
float angulovaria = 0.0f;
float dragonavance = 0.0f;
float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame,
ciclo, ciclo2, ciclo3, ciclo4, ciclo5, ciclo6, ciclo7, ciclo8, ciclo9, ciclo0, contador = 0;
int i, a = 20;
bool manejoAni = false;


Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture dadoTexture;
Texture plainTexture;
Texture pisoTexture;

Texture Degradado;
Texture race;
Texture bottom_Trunk;
Texture coconut;
Texture roca;
Texture techo;
Texture wall;
Texture wood;
Texture plateado;
Texture metal;
Texture chest;
Texture cara;

Texture letreroTexture;

Texture padock1;
Texture padock2;
Texture padock3;
Texture padockLetter;

Texture ballcourt1;
Texture ballcourt2;
Texture ballcourt3;
Texture ballcourt4;
Texture ballcourt5;
Texture ballcourt6;



Model Kitt_M;
Model Llanta_M;
Model Lampara_M;
Model Blackhawk_M;

Model palmera_ruina_tronco_M;
Model palmera_ruina_hojas_M;
Model piedra_0_M;
Model tunel_ruina_M;

Model Diablo_M;

Model Arco_M;
Model Puerta_M;
Model Porticullis_M;

Model beastieCarro_M;
Model beastieCarroLlantaDel_M;
Model beastieCarroLlantaTras_M;

Model XueCarro_M;
Model XueTurbina_M;
Model XuePaleta_M;

Model cajaFrente_M;
Model casitaIzq_M;
Model castillo_M;
Model constFrente_M;
Model constMedioChiquito_M;
Model constMedio_M;
Model EsqIzqFrente_M;
Model esqIzq_M;
Model explanadaDer_M;
Model ruinasIzq_M;

Model avatarCuerpo_M;
Model avatarBrazo_M;
Model avatarAntebrazo_M;
Model avatarMuslo_M;
Model avatarPierna_M;

Model beach_M;
Model tux_M;
Model tuxAla_M;

Model delfin_M;
Model globo_M;

Model suzanne_cuerpo_M;
Model suzanne_pierna_M;
Model suzanne_antebrazo_M;
Model suzanne_brazo_M;

Model condor_cuerpo_M;
Model condor_muslo_M;
Model condor_pierna_M;
Model condor_antebrazo_M;
Model condor_brazo_M;

Model castillo;
Model constMedio;
Model constMedioChiquito;
Model esqIzq;
Model casitaIzq;
Model ruinasIzq;
Model esqIzqFrente;
Model cajaFrente;
Model constFrente;
Model explanadaDer;
Model esqDer;
Model racecourse;
Model palmera;
Model coco;
Model FrenteIzq;
Model casaTux;
Model smallCasaTux;
Model ring;
Model santo;
Model lampara;
Model chest_lid;
Model chest_body;
Model chest_key;
Model padock;

Model thunderbirdCuerpo_M;
Model thunderbirdAla_M;

Model ballcourt_M;


Avatar* avatar;
Tux* tux;
Delfin* delfin;
Suzanne* suzanne;
Condor* condor;

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;

//archivos
FILE* archivo;
int err;
char linea[100];

Sphere sp = Sphere(0.1, 20, 20);

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

SpotLight luzLinterna;
SpotLight faroDelantero;
SpotLight faroTrasero;
SpotLight luzCofre;

PointLight luzDiablo;
PointLight luzPoste;

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";

//función para teclado de keyframes 
void inputKeyframes(bool* keys);


//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//x      y      z	u	  v	nx	  ny    nz
		-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,	0.5f, 0.0f,	0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.6f,	1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,	0.5f, 1.0f,	0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	1.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,	1.0f, 1.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,	0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,	1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,	1.0f, 1.0f,	0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,	0.0f, 1.0f,	0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,	0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,	1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,	1.0f, 1.0f,	0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,	0.0f, 1.0f,	0.0f, 0.0f, 0.0f,


	};

	unsigned int letreroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat letreroVertices[] = {
		-0.5f, 1.0f, 0.0f,	0.0f, 1.0f,	0.0f, 0.0f, -1.0f,
		0.5f, 1.0f, 0.0f,	0.125f, 1.0f,	0.0f, 0.0f, -1.0f,
		0.5f, 0.0f, 0.0f,	0.125f, 0.875f,	0.0f, 0.0f, -1.0f,
		-0.5f, 0.0f, 0.0f,	0.0f, 0.875f,	0.0f, 0.0f, -1.0f,
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	Mesh* obj8 = new Mesh();
	obj8->CreateMesh(letreroVertices, letreroIndices, sizeof(letreroVertices) / sizeof(GLfloat), sizeof(letreroIndices) / sizeof(unsigned int));
	meshList.push_back(obj8); // solo un número

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);
}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void CrearDado()
{
	unsigned int dado_indices[] = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23
	};

	GLfloat sin60 = 0.866025f;
	GLfloat cos60 = 0.5f;

	GLfloat dado_vertices[] = {
		// x      y      z       u     v      nx     ny     nz
		// Cara 1
		 -1.0f,  0.0f,  1.0f,   0.6834f, 0.5037f,   0.0f,  -sin60,  -cos60,
		 1.0f,  0.0f,  1.0f,   0.294f, 0.5037f,   0.0f,  -sin60,  -cos60,
		 0.0f,  2.0f,  0.0f,   0.4887f, 0.26809f,   0.0f,  -sin60,  -cos60,

		 // Cara 7
		 1.0f,  0.0f, -1.0f,   0.10201f, 0.26809f,   -cos60, -sin60,  0.0f,
		 1.0f,  0.0f,  1.0f,   0.295f, 0.5037f,   -cos60, -sin60,  0.0f,
		 0.0f,  2.0f,  0.0f,   0.4887f, 0.26809f,   -cos60, -sin60,  0.0f,

		 // Cara 5
		 -1.0f,  0.0f,  -1.0f,  0.10201f, 0.26809f,   0.0f,  -sin60, cos60,
		 1.0f,  0.0f,  -1.0f,   0.4887f, 0.26809f,   0.0f,  -sin60, cos60,
		 // 0.0f,  2.0f, 0.0f,   0.4887f, 0.26809f,   0.0f,  -sin60, cos60,
		 0.0f,  2.0f, 0.0f,   0.294f, 0.035,   0.0f,  -sin60, cos60,

		 // Cara 3
		 -1.0f,  0.0f,  -1.0f,   0.878, 0.26809f,  cos60, -sin60, 0.0f,
		 -1.0f,  0.0f,  1.0f,   0.683f, 0.5037f,  cos60, -sin60, 0.0f,
		 0.0f,  2.0f,  0.0f,   0.4887f, 0.26809f,  cos60, -sin60, 0.0f,

		 // Cara 4
		  -1.0f,  0.0f,  1.0f,   0.6834f, 0.5037f,   0.0f, sin60,  -cos60,
		  1.0f,  0.0f,  1.0f,   0.2959f, 0.5037f,   0.0f,  sin60,  -cos60,
		  0.0f,  -2.0f,  0.0f,   0.4887f, 0.7387f,   0.0f,  sin60,  -cos60,

		  // Cara 6
		  1.0f,  0.0f, -1.0f,   0.10201f, 0.73988f,   -cos60, sin60,  0.0f,
		  1.0f,  0.0f,  1.0f,   0.2959f, 0.5037f,   -cos60, sin60,  0.0f,
		  0.0f,  -2.0f,  0.0f,   0.4887f, 0.7387f,   -cos60, sin60,  0.0f,

		  // Cara 8
		  -1.0f,  0.0f,  -1.0f,  0.2959f, 0.9735f,   0.0f,  sin60, cos60,
		  1.0f,  0.0f,  -1.0f,   0.10201f, 0.73988f,   0.0f,  sin60, cos60,
		  0.0f,  -2.0f, 0.0f,   0.4887f, 0.7387f,   0.0f,  sin60, cos60,

		  // Cara 2
		  -1.0f,  0.0f,  -1.0f,   0.875f, 0.73789f,  cos60, sin60, 0.0f,
		  -1.0f,  0.0f,  1.0f,   0.6834f, 0.5037f,  cos60, sin60, 0.0f,
		  0.0f,  -2.0f,  0.0f,   0.4887f, 0.7387f,  cos60, sin60, 0.0f,
	};


	Mesh* dado = new Mesh();
	dado->CreateMesh(dado_vertices, dado_indices, sizeof(dado_vertices), sizeof(dado_indices));
	meshList.push_back(dado);
}

///////////////////////////////KEYFRAMES/////////////////////

bool animacion = false;


//NEW// Keyframes
float posXLlave = 0.0, posYLlave = -0.0, posZLlave = 0.0;
float	movLlave_x = 0.0f, movLlave_y = 0.0f, giroLlave = 0.0f, giroCofre;

#define MAX_FRAMES 100 //N�mero de cuadros m�ximos
int i_max_steps = 20; //N�mero de pasos entre cuadros para interpolaci�n, a mayor n�mero , m�s lento ser� el movimiento
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movLlave_x;		//Variable para PosicionX
	float movLlave_y;		//Variable para PosicionY
	float movLlave_xInc;		//Variable para IncrementoX
	float movLlave_yInc;		//Variable para IncrementoY
	float giroLlave;
	float giroLlaveInc;
	float giroCofre;
	float giroCofreInc;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 6;			//El n�mero de cuadros guardados actualmente desde 0 para no sobreescribir
bool play = false;
int playIndex = 0;

void saveFrame(void) //tecla L
{

	printf("frameindex %d\n", FrameIndex);


	KeyFrame[FrameIndex].movLlave_x = movLlave_x;
	KeyFrame[FrameIndex].movLlave_y = movLlave_y;
	KeyFrame[FrameIndex].giroLlave = giroLlave;
	KeyFrame[FrameIndex].giroCofre = giroCofre;
	//Se agregan nuevas l�neas para guardar m�s variables si es necesario

	//no volatil,se requiere agregar una forma de escribir a un archivo para guardar los frames
	FrameIndex++;

	archivo = fopen("datos.txt", "a");
	if (err != 0 || archivo == NULL) {
		printf("Error al abrir el archivo.\n");
		exit(EXIT_FAILURE);
	}
	fprintf(archivo, "%f\n", movLlave_x);
	fprintf(archivo, "%f\n", movLlave_y);
	fprintf(archivo, "%f\n", giroLlave);
	fprintf(archivo, "%f\n", giroCofre);
	fclose(archivo);

}

void readFile(void) {
	archivo = fopen("datos.txt", "r");
	if (err != 0 || archivo == NULL) {
		printf("Error al abrir el archivo.\n");
		return;
	}

	// Reiniciamos FrameIndex para cargar la animación desde cero
	FrameIndex = 0;
	float x, y, g, g2;

	while (fscanf(archivo, "%f %f %f %f", &x, &y, &g, &g2) == 4) {
		if (FrameIndex >= MAX_FRAMES) {
			printf("Se alcanzó el máximo de frames (%d).\n", MAX_FRAMES);
			break; // Evitar que se desborde el arreglo
		}

		// Guardamos los valores en el ARREGLO, no en las variables globales
		KeyFrame[FrameIndex].movLlave_x = x;
		KeyFrame[FrameIndex].movLlave_y = y;
		KeyFrame[FrameIndex].giroLlave = g;
		KeyFrame[FrameIndex].giroCofre = g2;

		printf("Leído Frame %d: x=%.1f, y=%.1f, g=%.1f, g2=%.1f\n", FrameIndex, x, y, g, g2);
		FrameIndex++; // Incrementamos el índice de frames leídos
	}

	fclose(archivo);
	printf("Lectura de archivo completa. Total de frames cargados: %d\n", FrameIndex);

}

void resetElements(void) //Tecla 0
{

	movLlave_x = KeyFrame[0].movLlave_x;
	movLlave_y = KeyFrame[0].movLlave_y;
	giroLlave = KeyFrame[0].giroLlave;
	giroCofre = KeyFrame[0].giroCofre;
}


void interpolation(void)
{
	KeyFrame[playIndex].movLlave_xInc = (KeyFrame[playIndex + 1].movLlave_x - KeyFrame[playIndex].movLlave_x) / i_max_steps;
	KeyFrame[playIndex].movLlave_yInc = (KeyFrame[playIndex + 1].movLlave_y - KeyFrame[playIndex].movLlave_y) / i_max_steps;
	KeyFrame[playIndex].giroLlaveInc = (KeyFrame[playIndex + 1].giroLlave - KeyFrame[playIndex].giroLlave) / i_max_steps;
	KeyFrame[playIndex].giroCofreInc = (KeyFrame[playIndex + 1].giroCofre - KeyFrame[playIndex].giroCofre) / i_max_steps;
}


void animate(void)
{
	//Movimiento del objeto con barra espaciadora
	if (play) {
		// fin de animaci�n entre frames?
		if (i_curr_steps >= i_max_steps) {
			playIndex++;
			printf("playindex : %d\n", playIndex);

			//Fin de toda la animaci�n con �ltimo frame?
			if (playIndex > FrameIndex - 2) {
				printf("Frame index= %d\n", FrameIndex);
				printf("termino la animacion\n");
				playIndex = 0;
				play = false;
			}
			else if (playIndex > FrameIndex - 3) {
				// Fin de toda la animaci�n con �ltimo frame?
				if (manejoAni == false) {
					manejoAni = true;
				}

			}
			else {
				//Interpolaci�n del pr�ximo cuadro
				i_curr_steps = 0; //Resetea contador
				//Interpolar
				interpolation();
			}
		}
		else {
			//Dibujar Animaci�n
			if (manejoAni == false) {
				movLlave_x += KeyFrame[playIndex].movLlave_xInc;
				movLlave_y += KeyFrame[playIndex].movLlave_yInc;
				giroLlave += KeyFrame[playIndex].giroLlaveInc;
				giroCofre += KeyFrame[playIndex].giroCofreInc;
				i_curr_steps++;
			}
		}
	}
}


///////////////* FIN KEYFRAMES*////////////////////////////

int main()
{


	if (!alutInit(NULL, NULL)) {
		ALenum error = alutGetError();
		fprintf(stderr, "%s\n", alutGetErrorString(error));
		exit(EXIT_FAILURE);
	}


	ALCcontext* context;
	ALCdevice* device;

	device = alcOpenDevice(NULL);
	if (device == nullptr) {
		fprintf(stderr, "No se pudo abrir el dispositivo de audio: %d...\n", alGetError());
	}


	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);

	alGetError();

	ALenum error;
	ALuint     alBuffer;             //data for the buffer
	unsigned int alSource;      //source
	ALuint     alBuffer2;             //data for the buffer
	unsigned int alSource2;      //source

	alBuffer = alutCreateBufferFromFile("./audio/hacienda.wav");
	if (alBuffer == AL_NONE) {
		error = alutGetError();
		fprintf(stderr, "Error loading file: '%s'\n",
			alutGetErrorString(error));
		alutExit();
		exit(EXIT_FAILURE);
	}
	alGenSources(1, &alSource);
	alSourcei(alSource, AL_BUFFER, alBuffer);


	alBuffer2 = alutCreateBufferFromFile("./audio/golpe.wav");
	if (alBuffer2 == AL_NONE) {
		error = alutGetError();
		fprintf(stderr, "Error loading file: '%s'\n",
			alutGetErrorString(error));
		alutExit();
		exit(EXIT_FAILURE);
	}
	alGenSources(1, &alSource2);
	alSourcei(alSource2, AL_BUFFER, alBuffer2);


	// mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow = Window(1920, 1080); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearDado();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);
	mainWindow.setCamera(&camera);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.png");
	pisoTexture.LoadTextureA();

	letreroTexture = Texture("Textures/fuente-limpio.png");
	letreroTexture.LoadTextureA();

	Degradado = Texture("Textures/degradado.png");
	Degradado.LoadTextureA();
	race = Texture("Textures/tokyo.png");
	race.LoadTextureA();
	bottom_Trunk = Texture("Textures/Bottom_Trunk.bmp");
	bottom_Trunk.LoadTextureA();
	coconut = Texture("Textures/Coconut_01.png");
	coconut.LoadTextureA();
	roca = Texture("Textures/roca.png");
	roca.LoadTextureA();
	techo = Texture("Textures/roof.png");
	techo.LoadTextureA();
	wood = Texture("Textures/oldWood.png");
	wood.LoadTextureA();
	wall = Texture("Textures/wall.png");
	wall.LoadTextureA();
	plateado = Texture("Textures/plateado.png");
	plateado.LoadTextureA();
	metal = Texture("Textures/metal028.png");
	metal.LoadTextureA();
	chest = Texture("Textures/chest.png");
	chest.LoadTextureA();

	padock1 = Texture("Textures/texture1.png");
	padock1.LoadTextureA();
	padock2 = Texture("Textures/texture2.png");
	padock2.LoadTextureA();
	padock3 = Texture("Textures/texture3.png");
	padock3.LoadTextureA();
	padockLetter = Texture("Textures/1.png");
	padockLetter.LoadTextureA();

	ballcourt1 = Texture("Textures/7macaw_Material.003_BaseColor.png");
	ballcourt1.LoadTextureA();
	ballcourt2 = Texture("Textures/7macaw_Material.003_Normal.png");
	ballcourt2.LoadTextureA();
	ballcourt3 = Texture("Textures/7macaw_Material.003_Roughness.png");
	ballcourt3.LoadTextureA();
	ballcourt4 = Texture("Textures/ballourt_Material_BaseColor.png");
	ballcourt4.LoadTextureA();
	ballcourt5 = Texture("Textures/ballourt_Material_Normal.png");
	ballcourt5.LoadTextureA();
	ballcourt6 = Texture("Textures/ballourt_Material_Roughness.png");
	ballcourt6.LoadTextureA();

	cara = Texture("Textures/cara.png");
	cara.LoadTextureA();


	Lampara_M = Model();
	Lampara_M.LoadModel("Models/posteluz.fbx");
	Diablo_M = Model();
	Diablo_M.LoadModel("Models/diablo.fbx");
	Arco_M = Model();
	Arco_M.LoadModel("Models/puerta-arco.obj");
	Puerta_M = Model();
	Puerta_M.LoadModel("Models/puerta.obj");
	Porticullis_M = Model();
	Porticullis_M.LoadModel("Models/porticullis.obj");

	dadoTexture = Texture("Textures/dado-8-caras.png");
	dadoTexture.LoadTextureA();

	beastieCarro_M = Model();
	beastieCarroLlantaDel_M = Model();
	beastieCarroLlantaTras_M = Model();
	beastieCarro_M.LoadModel("./Models/beastie-carro.obj");
	beastieCarroLlantaDel_M.LoadModel("./Models/beastie-carro-llanta-delantera.obj");
	beastieCarroLlantaTras_M.LoadModel("./Models/beastie-carro-llanta-trasera.obj");

	XueCarro_M = Model();
	XueTurbina_M = Model();
	XuePaleta_M = Model();
	XueCarro_M.LoadModel("./Models/xue-cuerpo.obj");
	XueTurbina_M.LoadModel("./Models/xue-turbina.obj");
	XuePaleta_M.LoadModel("./Models/xue-paleta.obj");

	avatarCuerpo_M = Model();
	avatarCuerpo_M.LoadModel("./Models/avatar-cuerpo.obj");
	avatarMuslo_M = Model();
	avatarMuslo_M.LoadModel("./Models/avatar-muslo.obj");
	avatarPierna_M = Model();
	avatarPierna_M.LoadModel("./Models/avatar-pierna.obj");
	avatarBrazo_M = Model();
	avatarBrazo_M.LoadModel("./Models/avatar-brazo.obj");
	avatarAntebrazo_M = Model();
	avatarAntebrazo_M.LoadModel("./Models/avatar-antebrazo.obj");

	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");

	palmera_ruina_tronco_M = Model();
	palmera_ruina_tronco_M.LoadModel("Models/palmera-ruina-tronco.obj");
	palmera_ruina_hojas_M = Model();
	palmera_ruina_hojas_M.LoadModel("Models/palmera-ruina-hojas.obj");
	piedra_0_M = Model();
	piedra_0_M.LoadModel("Models/piedra-0.obj");
	tunel_ruina_M = Model();
	tunel_ruina_M.LoadModel("Models/tunel-ruina.obj");

	cajaFrente_M = Model();
	cajaFrente_M.LoadModel("Models/tulum/cajaFrente.obj");
	casitaIzq_M = Model();
	casitaIzq_M.LoadModel("Models/tulum/casitaIzq.obj");
	castillo_M = Model();
	castillo_M.LoadModel("Models/tulum/castillo.obj");
	constFrente_M = Model();
	constFrente_M.LoadModel("Models/tulum/constFrente.obj");
	constMedioChiquito_M = Model();
	constMedioChiquito_M.LoadModel("Models/tulum/constFrente.obj");
	constMedio_M = Model();
	constMedio_M.LoadModel("Models/tulum/constMedio.obj");
	EsqIzqFrente_M = Model();
	EsqIzqFrente_M.LoadModel("Models/tulum/EsqIzqFrente.obj");
	esqIzq_M = Model();
	esqIzq_M.LoadModel("Models/tulum/esqIzq.obj");
	explanadaDer_M = Model();
	explanadaDer_M.LoadModel("Models/tulum/explanadaDer.obj");
	ruinasIzq_M = Model();
	ruinasIzq_M.LoadModel("Models/tulum/ruinasIzq.obj");


	castillo = Model();
	castillo.LoadModel("Models/tulum/castillo.obj");
	constMedio = Model();
	constMedio.LoadModel("Models/tulum/constCentro.obj");
	constMedioChiquito = Model();
	constMedioChiquito.LoadModel("Models/tulum/constCentroTecho.obj");
	esqIzq = Model();
	esqIzq.LoadModel("Models/tulum/esqIzq.obj");
	casitaIzq = Model();
	casitaIzq.LoadModel("Models/tulum/casaDer.obj");
	ruinasIzq = Model();
	ruinasIzq.LoadModel("Models/tulum/muroDer.obj");
	esqIzqFrente = Model();
	esqIzqFrente.LoadModel("Models/tulum/muroDerFrente.obj");
	cajaFrente = Model();
	cajaFrente.LoadModel("Models/tulum/cajaFrente.obj");
	constFrente = Model();
	constFrente.LoadModel("Models/tulum/constFrente.obj");
	explanadaDer = Model();
	explanadaDer.LoadModel("Models/tulum/planoIzq.obj");
	FrenteIzq = Model();
	FrenteIzq.LoadModel("Models/tulum/frenteIzq.obj");
	esqDer = Model();
	esqDer.LoadModel("Models/tulum/esqDer.obj");
	racecourse = Model();
	racecourse.LoadModel("Models/racecourse.obj");
	palmera = Model();
	palmera.LoadModel("Models/tulum/palmera.obj");
	coco = Model();
	coco.LoadModel("Models/coco.obj");
	casaTux = Model();
	casaTux.LoadModel("Models/casaTux.obj");
	ring = Model();
	ring.LoadModel("Models/ring_lucha_libre.obj");
	santo = Model();
	santo.LoadModel("Models/santo.obj");
	lampara = Model();
	lampara.LoadModel("Models/lampara.obj");
	smallCasaTux = Model();
	smallCasaTux.LoadModel("Models/smallCasaTux.obj");
	chest_lid = Model();
	chest_lid.LoadModel("Models/chest_lid.obj");
	chest_body = Model();
	chest_body.LoadModel("Models/chest_body.obj");
	chest_key = Model();
	chest_key.LoadModel("Models/chest_key.obj");

	beach_M = Model();
	beach_M.LoadModel("Models/beach.obj");
	tux_M = Model();
	tux_M.LoadModel("Models/tux-cuerpo.obj");
	tuxAla_M = Model();
	tuxAla_M.LoadModel("Models/tux-ala.obj");

	delfin_M = Model();
	delfin_M.LoadModel("Models/delfin.obj");

	globo_M = Model();
	globo_M.LoadModel("Models/globo.obj");

	suzanne_cuerpo_M = Model();
	suzanne_cuerpo_M.LoadModel("Models/suzanne-cuerpo.obj");
	suzanne_pierna_M = Model();
	suzanne_pierna_M.LoadModel("Models/suzanne-pierna.obj");
	suzanne_antebrazo_M = Model();
	suzanne_antebrazo_M.LoadModel("Models/suzanne-antebrazo.obj");
	suzanne_brazo_M = Model();
	suzanne_brazo_M.LoadModel("Models/suzanne-brazo.obj");

	condor_cuerpo_M = Model();
	condor_cuerpo_M.LoadModel("Models/condor-cuerpo.obj");
	condor_muslo_M = Model();
	condor_muslo_M.LoadModel("Models/condor-muslo.obj");
	condor_pierna_M = Model();
	condor_pierna_M.LoadModel("Models/condor-pierna.obj");
	condor_antebrazo_M = Model();
	condor_antebrazo_M.LoadModel("Models/condor-antebrazo.obj");
	condor_brazo_M = Model();
	condor_brazo_M.LoadModel("Models/condor-brazo.obj");

	thunderbirdCuerpo_M = Model();
	thunderbirdCuerpo_M.LoadModel("Models/thunderbird-cuerpo.obj");
	thunderbirdAla_M = Model();
	thunderbirdAla_M.LoadModel("Models/thunderbird-ala.obj");

	ballcourt_M = Model();
	ballcourt_M.LoadModel("Models/court.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/heather_rt.jpg");
	skyboxFaces.push_back("Textures/Skybox/heather_lf.jpg");
	skyboxFaces.push_back("Textures/Skybox/heather_dn.jpg");
	skyboxFaces.push_back("Textures/Skybox/heather_up.jpg");
	skyboxFaces.push_back("Textures/Skybox/heather_bk.jpg");
	skyboxFaces.push_back("Textures/Skybox/heather_ft.jpg");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	glm::vec3 luces[20] = { glm::vec3(-120.0f, -1.0f, -10.0f), glm::vec3(30.0f, 0.0f, 0.0f), glm::vec3(30.0f, 0.0f, 0.0f), glm::vec3(30.0f, 0.0f, 0.0f),
				   glm::vec3(30.0f, 0.0f, 0.0f) ,glm::vec3(0.0f, 0 - 0.0f, 30.0f) , glm::vec3(0.0f, 0.0f, 30.0f), glm::vec3(0.0f, 0.0f, 30.0f), glm::vec3(0.0f, 0.0f, 30.0f),
				   glm::vec3(-30.0f, 0.0f, 0.0f),glm::vec3(-30.0f, 0.0f, 0.0f),glm::vec3(-30.0f, 0.0f, 0.0f), glm::vec3(-10.0f, 0.0f, -30.0f), glm::vec3(-10.0f, 0.0f, -30.0f),
				   glm::vec3(-10.0f, 0.0f, -30.0f) };



	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual

	int luz = 12;

	for (int i = 0; i < luz; i++) {
		pointLights[i] = PointLight(1.0f, 1.0f, 1.0f,
			2.0f, 2.0f,
			0.0f, 2.5f, 1.5f,
			0.3f, 0.2f, 0.1f);
	}


	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	// //luz fija
	// spotLights[1] = SpotLight(0.0f, 0.0f, 1.0f,
	// 			  1.0f, 2.0f,
	// 			  5.0f, 10.0f, 0.0f,
	// 			  0.0f, -5.0f, 0.0f,
	// 			  1.0f, 0.0f, 0.0f,
	// 			  15.0f);
	// spotLightCount++;





	// //luz direccional, sólo 1 y siempre debe de existir
	// mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
	// 	0.4f, 0.4f,
	// 	0.0f, -1.0f, 0.0f);
	// //contador de luces puntuales
	// pointLightCount = 0;
	// spotLightCount = 0;

	// //linterna
	// luzLinterna = SpotLight(1.0f, 1.0f, 1.0f,
	// 	0.0f, 2.0f,
	// 	0.0f, 0.0f, 0.0f,
	// 	0.0f, -1.0f, 0.0f,
	// 	1.0f, 0.0f, 0.0f,
	// 	5.0f);

	// faroDelantero = SpotLight(1.0f, 1.0f, 0.0f,
	// 	1.0f, 0.2f,
	// 	5.0f, 10.0f, 0.0f,
	// 	-2.0f, 0.0f, 0.0f,
	// 	1.0f, 0.001f, 0.001f,
	// 	20.0f);

	SpotLight faro1 = SpotLight(0.75f, 1.0f, 0.7f,
		0.3f, 0.3f,
		5.0f, 10.0f, 0.0f,
		2.0f, 0.0f, 0.0f,
		1.0f, 0.001f, 0.001f,
		20.0f);
	SpotLight faro2 = SpotLight(0.5f, 1.0f, 0.5f,
		0.2f, 0.2f,
		5.0f, 10.0f, 0.0f,
		2.0f, 0.0f, 0.0f,
		1.0f, 0.001f, 0.001f,
		20.0f);

	// luzCofre = SpotLight(0.25f, 1.0f, 0.0f,
	// 	1.0f, 2.0f,
	// 	5.0f, 10.0f, 0.0f,
	// 	-2.0f, 0.0f, 0.0f,
	// 	1.0f, 0.001f, 0.001f,
	// 	15.0f);

	// luzDiablo = PointLight(1.0f, 0.125f, 0.0f,
	// 	0.8f, 0.8f,
	// 	6.0f, 2.5f, 1.5f,
	// 	0.3f, 0.2f, 0.1f);

	// luzPoste = PointLight(1.0f, 1.0f, 1.0f,
	// 	1.0f, 2.0f,
	// 	0.0f, 12.0f, -19.25f,
	// 	1.0f, 0.01f, 0.01f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	glm::vec3 posblackhawk = glm::vec3(2.0f, 0.0f, 0.0f);

	glm::vec3 poscoco = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 arbol[20] = { glm::vec3(-2.0f, 0.0f, -5.0f), glm::vec3(1.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, -5.0f),
				glm::vec3(-1.0f, 0.0f, -5.0f), glm::vec3(-4.0f, 0.0f, -5.0f), glm::vec3(4.0f, 0.0f, -5.0f), glm::vec3(-3.0f, 0.0f, -5.0f),
				glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(3.0f, 0.0f, -5.0f), glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec3(-1.0f, 0.0f, -5.0f),
				glm::vec3(5.0f, 0.0f, -5.0f), glm::vec3(2.0f, 0.0f, -5.0f), glm::vec3(-3.0f, 0.0f, -5.0f), glm::vec3(1.0f, 0.0f, -5.0f),
				glm::vec3(-1.0f, 0.0f, -5.0f), glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(-3.0f, 0.0f, -5.0f) };

	glm::vec3 posLlave = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 luz_position = glm::vec3(0.0f, 0.0f, 0.0f);

	sp.init(); //inicializar esfera
	sp.load();


	std::vector<MovingEntity*> movingEntities;

	// Pos: 153.167160 41.381664 -228.169876
	// Dir: -21.500000 71.000000

	movingEntities.push_back(new Beastie(&beastieCarro_M, &beastieCarroLlantaTras_M, &beastieCarroLlantaDel_M, glm::vec3(150.0f, 0.0f, -230.0f), [](GLfloat t) {
		return glm::vec3(20.0f * cos(t), 0.0f, 50.0f * sin(0.666f * t));
		}));

	movingEntities.push_back(new Xue(&XueCarro_M, &XuePaleta_M, &XueTurbina_M, glm::vec3(160.0f, 0.0f, -240.0f), [](GLfloat t) {
		return glm::vec3(40.0f * cos(t), 0.0f, 40.0f * sin(0.666f * t));
		}));

	movingEntities.push_back(new Thunderbird(&thunderbirdCuerpo_M, &thunderbirdAla_M, glm::vec3(0.0f), [](GLfloat t) {
		return glm::vec3(40.0f * cos(t), 75.0f + 20.0f * sin(t), 100.0f * sin(0.666f * t));
		}));

	movingEntities.push_back(new Thunderbird(&thunderbirdCuerpo_M, &thunderbirdAla_M, glm::vec3(200.0f, 0.0f, 200.0f), [](GLfloat t) {
		return glm::vec3(40.0f * cos(t), 75.0f + 20.0f * sin(t), 100.0f * sin(0.666f * t));
		}));


	delfin = new Delfin(&delfin_M, glm::vec3(-400.0f, 0.0f, 100.0f), [](GLfloat t) {
		return glm::vec3(0.0f, 20 * sin(t) - 5.0f, 20.0f * cos(t));
		});

	movingEntities.push_back(new Globo(
		&globo_M, glm::vec3(0.0f, 0.0f, 0.0f), [](GLfloat t) {
			while (t > 120.0f) {
				t -= 120.0f;
			}

			if (t <= 5.0f) {
				return glm::vec3(300.0f, 30 * t, 0.0f);
			}
			else if (t <= 55.0f) {
				t -= 5.0f;
				return glm::vec3(300.0f * cos(0.12566 * t), 160.0f + 15 * sin(t * 1.256), 300.0f * sin(0.12566 * t));
			}
			else if (t <= 60.0f) {
				return glm::vec3(300.0f, 30 * (60 - t), 0.0f);
			}

			return glm::vec3(300.0f, 0.0f, 0.0f);
		}));

	movingEntities.push_back(delfin);

	avatar = new Avatar(&avatarCuerpo_M, &avatarMuslo_M, &avatarPierna_M, &avatarBrazo_M, &avatarAntebrazo_M, glm::vec3(0.0f, 0.0f, 2.0f));
	avatar->startAnimation();




	camera.setAvatar(avatar);

	camera.addLocation(glm::vec3(5.0f, 30.0f, 140.0f), glm::vec2(-20.0f, 0.0f));
	camera.addLocation(glm::vec3(-225.0f, 20.0f, 125.0f), glm::vec2(-20.0f, -135.0f));
	camera.addLocation(glm::vec3(-17.0f, 110.0f, -320.0f), glm::vec2(-27.0f, 30.0f));

	// Lee los keyframes del archivo
	// readKeyframes("keyframes-palmera.txt");


	printf("\nTeclas para uso de Keyframes:\n1.-Presionar barra espaciadora para reproducir animacion.\n2.-Presionar 0 para volver a habilitar reproduccion de la animacion\n");
	printf("3.-Presiona L para guardar frame\n4.-Presiona P para habilitar guardar nuevo frame\n5.-Presiona 1 para mover en X\n6.-Presiona 2 para habilitar mover en X\n");



	glm::mat4 model(1.0);
	glm::mat4 modelcuerpo(1.0);
	glm::mat4 modelaux(1.0);
	glm::mat4 modeltrans(1.0);
	glm::mat4 modelrot(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec4 lightpos = glm::vec4(0.0f);
	glm::vec4 lightdir = glm::vec4(0.0f);
	glm::vec2 toffset = glm::vec2(0.0f, 0.0f);
	GLfloat lastLetrero = glfwGetTime();

	int indiceLetrero = 0;
	char letreroTexto[] = " PROYECTO CGEIHC ";
	glm::vec4 dir = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 rotDado = glm::mat4(1.0f);
	int contadorGiros = 0;
	GLfloat timeSinceStatic = glfwGetTime();
	int ultimoRandom = 0;
	int r = 0;
	int k;

	model = glm::translate(model, glm::vec3(-230.0f, 0.0f, 100.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	tux = new Tux(&tux_M, &tuxAla_M, model);

	suzanne = new Suzanne(&suzanne_cuerpo_M, &suzanne_pierna_M, &suzanne_antebrazo_M, &suzanne_brazo_M, glm::mat4(1.0f));
	condor = new Condor(&condor_cuerpo_M, &condor_muslo_M, &condor_pierna_M, &condor_antebrazo_M, &condor_brazo_M, glm::mat4(1.0f));

	bool firstFrame = true;
	GLfloat hora = 60.0f;

	float gain = 0.25f;
	alSourcef(alSource, AL_GAIN, gain);
	alSourcei(alSource, AL_LOOPING, AL_TRUE);

	alSourcePlay(alSource);


	// Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		GLfloat dt = now - lastTime;
		deltaTime = dt;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		if (!firstFrame) {
			hora += dt;
		}
		if (hora >= 120.0f) {
			hora -= 120.0f;
		}

		mainWindow.UpdatePos(dt);

		pointLightCount = 0;
		spotLightCount = 0;

		// Recibir eventos del usuario
		glfwPollEvents();
		if (camera.getEstado() == RIGGING_CAMERA) {
			camera.updateRig(dt);
		}
		else {
			camera.keyControl(mainWindow.getsKeys(), deltaTime);
			camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		}

		//-------Para Keyframes
		inputKeyframes(mainWindow.getsKeys());
		animate();

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection, hora);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation(); // para la textura con movimiento

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
		// glm::vec3 lowerLight = camera.getCameraPosition();
		// lowerLight.y -= 0.3f;
		// spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		toffset = glm::vec2(0.0f, 0.0f);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(60.0f, 1.0f, 60.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		// Diablo
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.5f, 0.0f, -25.0));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Diablo_M.RenderModel();

		// if (mainWindow.getPrendeDiablo()) {
// 	model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
// 	lightpos = model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
// 	luzDiablo.SetPos(lightpos);
// 	pointLights[pointLightCount++] = luzDiablo;
// }

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::translate(model, glm::vec3(-170.0f, -5.0f, 0.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaTux.RenderModel();

		model = glm::translate(model, glm::vec3(-40.0, -4.0f, 60.0f));;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		smallCasaTux.RenderModel();

		model = glm::translate(model, glm::vec3(-60.0, 0.0f, 0.0f));;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		smallCasaTux.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::translate(model, glm::vec3(152.0f, -2.0f, 100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		palmera.RenderModel();


		for (i = 0; i < 20; i++) {
			model = glm::translate(model, arbol[i]);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			bottom_Trunk.UseTexture();
			palmera.RenderModel();

		}

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-182.0f, -2.0f, 100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		palmera.RenderModel();




		for (i = 0; i < 20; i++) {
			model = glm::translate(model, arbol[i]);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			bottom_Trunk.UseTexture();
			palmera.RenderModel();


		}



		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, -2.0f, -170.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		palmera.RenderModel();





		for (i = 0; i < 20; i++) {
			model = glm::translate(model, arbol[i]);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			bottom_Trunk.UseTexture();

			palmera.RenderModel();


		}


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, -2.0f, -190.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		palmera.RenderModel();


		for (i = 0; i < 20; i++) {

			model = glm::translate(model, arbol[i]);

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			bottom_Trunk.UseTexture();
			palmera.RenderModel();





		}




		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-60.0f, -2.0f, 220.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		palmera.RenderModel();


		for (i = 0; i < 20; i++) {

			model = glm::translate(model, arbol[i]);

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

			bottom_Trunk.UseTexture();

			palmera.RenderModel();


		}


		//fin palmeras


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::translate(model, luces[0]);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara.RenderModel();
		luz_position = glm::vec3(model[3][0], model[3][1] + 5, model[3][2]);
		pointLights[0].SetPos(luz_position);


		int t = glfwGetTime();
		for (k = 1; k < luz; k++) {
			model = glm::translate(model, luces[k]);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			lampara.RenderModel();
			if (hora < 60.0f) {
				luz_position = glm::vec3(model[3][0], model[3][1] + 5, model[3][2]);
				pointLights[k].SetPos(luz_position);
				pointLights[pointLightCount++] = pointLights[k];
			}
		}

		if (hora < 60.0f) {
			faro1.SetFlash(movingEntities[0]->getPos(), movingEntities[0]->getDiff());
			faro2.SetFlash(movingEntities[1]->getPos(), movingEntities[1]->getDiff());
			spotLights[spotLightCount++] = faro1;
			spotLights[spotLightCount++] = faro2;
		}

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		castillo.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		constMedio.RenderModel();
		model = modelaux;
		model = glm::translate(model, glm::vec3(-90.0f, 15.0f, 25.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ring.RenderModel();

		suzanne->setModel(model);
		suzanne->update(dt);
		suzanne->render(uniformModel);
		condor->setModel(model);
		condor->update(dt);
		condor->render(uniformModel);

		model = glm::translate(model, glm::vec3(35.0f, 2.0f, -8.0f));
		model = glm::rotate(model, 60 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		santo.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esqIzq.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casitaIzq.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ruinasIzq.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esqIzqFrente.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cajaFrente.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		constFrente.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		explanadaDer.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		modelaux = model;
		// model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esqDer.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		modelaux = model;
		// model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		constMedioChiquito.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		modelaux = model;
		// model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrenteIzq.RenderModel();



		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 0.0f, -200.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		racecourse.RenderModel();


		//cofre con keyframe
		model = glm::mat4(1.0);

		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 140.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		chest_body.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 1.1f, -0.7f));

		modelaux = model;

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		sp.render();

		model = modelaux;
		modelaux = model;
		model = glm::rotate(model, giroCofre * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		chest_lid.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, 2.0f));
		posLlave = glm::vec3(posXLlave + movLlave_x, posYLlave, posZLlave + movLlave_y);
		model = glm::translate(model, posLlave);
		model = glm::rotate(model, giroLlave * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		sp.render();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		chest_key.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 0.0f, 300.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ballcourt_M.RenderModel();

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		for (auto entity : movingEntities) {
			if (!firstFrame) {
				entity->update(dt);
			}
			entity->render(uniformModel);
		}

		avatar->update(dt);
		avatar->render(uniformModel);

		if (!tux->getAnimating() && mainWindow.getReiniciaTux()) {
			tux->startAnimation();
		}

		if (!delfin->getAnimating() && mainWindow.getReiniciaDelfin()) {
			delfin->restartAnim();
		}

		if (!condor->getAnimating() && mainWindow.getReiniciaCondor()) {
			condor->startAnimation();
			alSourcei(alSource2, AL_LINEAR_DISTANCE, AL_TRUE);

			alSourcePlay(alSource2);
		}

		if (!suzanne->getAnimating() && mainWindow.getReiniciaSuzanne()) {
			suzanne->startAnimation();

			alSourcei(alSource2, AL_LINEAR_DISTANCE, AL_TRUE);

			alSourcePlay(alSource2);
		}


		tux->update(dt);
		tux->render(uniformModel);

		model = glm::mat4(1.0);
		model = model * tux->getModel();
		model = glm::translate(model, glm::vec3(3.0f, -1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		beach_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, -50.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Arco_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.39f, 0.0f, 0.0));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion6()), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puerta_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, mainWindow.getDeslizPos());
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Porticullis_M.RenderModel();

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-150.0f, -2.0f, -10.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);

		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Arco_M.RenderModel();


		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.3f, 0.0f, 0.0));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion6()), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puerta_M.RenderModel();



		model = modelaux;
		model = glm::translate(model, mainWindow.getDeslizPos());
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Porticullis_M.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -150.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		padock.RenderModel();

		int numpapus = 9;
		GLfloat angdif = 15.0f;
		for (int i = 0; i < numpapus; i++) {

			model = modelaux;
			model = glm::translate(model, glm::vec3(0.0f, 6.2f, 0.5025f));
			GLfloat angulo = (angdif * (numpapus / 2)) - angdif * i;
			angulo += angdif * (glfwGetTime() - lastLetrero) / 0.25 - angdif;
			model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(0.0f, 1.875f, 0.0f));
			model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

			int ind = (indiceLetrero + i) % strlen(letreroTexto);
			toffsetnumerou = 0.125f * ((letreroTexto[ind] - 'A') % 8);
			toffsetnumerov = 1 - 0.125f * ((letreroTexto[ind] - 'A') / 8);
			toffset = glm::vec2(toffsetnumerou, toffsetnumerov);
			// toffset = glm::vec2(0.125f, 0.125f);

			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			letreroTexture.UseTexture();
			meshList[4]->RenderMesh();
		}
		if (glfwGetTime() - lastLetrero > 0.25f) {
			indiceLetrero = (indiceLetrero + 1) % strlen(letreroTexto);
			lastLetrero = glfwGetTime();
		}

		toffset = glm::vec2(0.0f, 0.0f);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));


		// shaderList[0].SetPointLights(pointLights, pointLightCount);

		if (mainWindow.getPrendeLuzLinterna()) {
			glm::vec3 lowerLight = camera.getCameraPosition();
			lowerLight.y -= 0.3f;
			luzLinterna.SetFlash(lowerLight, camera.getCameraDirection());
			spotLights[spotLightCount++] = luzLinterna;
		}

		glm::vec4 dir = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		float ang = (6.28 / 120.0) * hora;
		glm::mat4 papu = glm::rotate(glm::mat4(1.0f), ang, glm::vec3(0.0f, 0.0f, 1.0f));
		dir = papu * dir;
		mainLight.SetDir(dir);
		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);


		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		// meshList[3]->RenderMesh();
		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();

		firstFrame = false;
	}


	alDeleteSources(1, &alSource);

	//delete our buffer
	//alDeleteBuffers(1, &alSampleSet);

	context = alcGetCurrentContext();

	//Get device for active context
	device = alcGetContextsDevice(context);

	//Disable context
	alcMakeContextCurrent(NULL);

	//Release context(s)
	alcDestroyContext(context);

	//Close device
	alcCloseDevice(device);

	return 0;
}

void inputKeyframes(bool* keys)
{
	if (keys[GLFW_KEY_SPACE]) {
		if (reproduciranimacion < 1) {
			if (play == false && (FrameIndex > 1)) {
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("\n presiona 0 para habilitar reproducir de nuevo la animaci�n'\n");
				habilitaranimacion = 0;

			}
			else {
				play = false;

			}
		}
	}

	if (keys[GLFW_KEY_L]) {
		if (guardoFrame < 1) {
			saveFrame();
			printf("movLlave_x es: %f\n", movLlave_x);
			printf("movLlave_y es: %f\n", movLlave_y);
			printf("presiona P para habilitar guardar otro frame'\n");
			guardoFrame++;
			reinicioFrame = 0;
		}
	}
	if (keys[GLFW_KEY_P]) {
		if (reinicioFrame < 1) {
			guardoFrame = 0;
			printf("Ya puedes guardar otro frame presionando la tecla L'\n");
		}
	}


	if (keys[GLFW_KEY_1]) {
		if (ciclo < 1) {
			//printf("movLlave_x es: %f\n", movLlave_x);
			movLlave_x += 1.0f;
			printf("\n movLlave_x es: %f\n", movLlave_x);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_2]) {
		if (ciclo2 < 1) {
			ciclo = 0;
			ciclo2++;
			printf("\n Ya puedes modificar tu variable presionando la tecla 1\n");
		}
	}
	if (keys[GLFW_KEY_3]) {
		if (ciclo3 < 1) {
			//printf("movLlave_x es: %f\n", movLlave_x);
			movLlave_x -= 1.0f;
			printf("\n movLlave_x es: %f\n", movLlave_x);
			ciclo3++;
			ciclo4 = 0;
			printf("\n Presiona la tecla 4 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_4]) {
		if (ciclo4 < 1) {
			ciclo3 = 0;
			ciclo4++;
			printf("\n Ya puedes modificar tu variable presionando la tecla 3\n");
		}
	}

	//movimiento en Y
	if (keys[GLFW_KEY_5]) {
		if (ciclo5 < 1) {
			//printf("movLlave_x es: %f\n", movLlave_x);
			movLlave_y += 1.0f;
			printf("\n movllave_y es: %f\n", movLlave_y);
			ciclo5++;
			ciclo6 = 0;
			printf("\n Presiona la tecla 6 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_6]) {
		if (ciclo6 < 1) {
			ciclo5 = 0;
			ciclo6++;
			printf("\n Ya puedes modificar tu variable presionando la tecla 5\n");
		}
	}

	if (keys[GLFW_KEY_7]) {
		if (ciclo7 < 1) {
			//printf("movLlave_x es: %f\n", movLlave_x);
			movLlave_y -= 1.0f;
			printf("\n movllave_y es: %f\n", movLlave_y);
			ciclo7++;
			ciclo8 = 0;
			printf("\n Presiona la tecla 8 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_8]) {
		if (ciclo8 < 1) {
			ciclo7 = 0;
			ciclo8++;
			printf("\n Ya puedes modificar tu variable presionando la tecla 7\n");
		}
	}

	if (keys[GLFW_KEY_9]) {
		if (ciclo9 < 1) {
			//printf("movAvion_x es: %f\n", movAvion_x);
			giroLlave += 22.5f;
			printf("\n giroAvion es: %f\n", giroLlave);
			ciclo9++;
			ciclo0 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_0]) {
		if (ciclo0 < 1) {
			ciclo9 = 0;
			ciclo0++;
			printf("\n Ya puedes modificar tu variable presionando la tecla 1\n");
		}
	}


	if (keys[GLFW_KEY_R]) {
		resetElements();
		printf("--- Leyendo archivo y reiniciando animación ---\n");

		play = false;
		i_curr_steps = 0;
		manejoAni = false;

		readFile();

		if (FrameIndex > 1) {
			interpolation();
			play = true;
			playIndex = 0;
		}
		else {
			printf("Archivo leído, pero no hay suficientes frames para animar.\n");
		}
	}

}
