/*
 Proyecto final para Computación Gráfica e Interacción Humano - Computadora
*/

//para cargar imagen
#include "Avatar.hpp"
#include "MovingEntity.hpp"
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

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
float toffsetflechau = 0.0f;
float toffsetflechav = 0.0f;
float toffsetnumerou = 0.0f;
float toffsetnumerov = 0.0f;
float toffsetnumerocambiau = 0.0;
float dragonavance = 0.0f;
float movCoche;
float movOffset;
float rotllanta;
float rotllantaOffset;
bool avanza;
float angulovaria = 0.0f;

// variables para keyframes
float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, ciclo3, ciclo4, ciclo5, ciclo6, ciclo7, ciclo8, ciclo9, ciclo10, contador = 0;


Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture dadoTexture;
Texture plainTexture;
Texture pisoTexture;

Texture letreroTexture;

Model Dado_M;

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

Avatar *avatar;

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


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
	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
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
	Shader *shader1 = new Shader();
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
float posXavion = 2.0, posYavion = 5.0, posZavion = -3.0;
float	movAvion_x = 0.0f, movAvion_y = 0.0f;
float giroAvion = 0;
float ang_tronco = 0.0f, ang_hojas = 0.0f;

#define MAX_FRAMES 100 //Número de cuadros máximos
int i_max_steps = 100; //Número de pasos entre cuadros para interpolación, a mayor número , más lento será el movimiento
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float ang_tronco;		//Variable para PosicionX
	float ang_hojas;		//Variable para PosicionY
	float ang_tronco_inc;		//Variable para IncrementoX
	float ang_hojas_inc;		//Variable para IncrementoY
	float giroAvion;		//Variable para GiroAvion
	float giroAvionInc;		//Variable para IncrementoGiroAvion
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//El número de cuadros guardados actualmente desde 0 para no sobreescribir
bool play = false;
int playIndex = 0;


void readKeyframes(std::string path) {
	std::fstream archivo(path, std::ios_base::in);

	float x, y, a;
        while (archivo >> x >> y >> a) {
		KeyFrame[FrameIndex].ang_tronco = x;
		KeyFrame[FrameIndex].ang_hojas = y;
		KeyFrame[FrameIndex].giroAvion = a;
		std::cout << "Leyendo keyframe\t x: " << x << ", \ty: " << y << ", \trot: " << a << "\n";

		FrameIndex++;
	}          
}

void writeKeyframe(std::string path, float x, float y, float a) {
	std::ofstream archivo(path, std::ios::app);

        if (!archivo) {
		std::cout << "Error: No se pudo abrir archivo '" << path << "'";
		return;
	}

        archivo << x << " " << y << " " << a << "\n";
        std::cout << "Escribiendo a txt: " << x << " " << y << " " << a << "\n";
	archivo.close();
}

void saveFrame(void) //tecla L
{

	printf("frameindex %d\n", FrameIndex);


	KeyFrame[FrameIndex].ang_tronco = ang_tronco;
	KeyFrame[FrameIndex].ang_hojas = ang_hojas;
	KeyFrame[FrameIndex].giroAvion = giroAvion;
	//Se agregan nuevas líneas para guardar más variables si es necesario
	
	//no volatil,se requiere agregar una forma de escribir a un archivo para guardar los frames
	FrameIndex++;

	writeKeyframe("keyframes-palmera.txt", ang_tronco, ang_hojas, giroAvion);
}

void resetElements(void) //Tecla 0
{

	ang_tronco = KeyFrame[0].ang_tronco;
	ang_hojas = KeyFrame[0].ang_hojas;
	giroAvion = KeyFrame[0].giroAvion;
}

void interpolation(void)
{
	KeyFrame[playIndex].ang_tronco_inc = (KeyFrame[playIndex + 1].ang_tronco - KeyFrame[playIndex].ang_tronco) / i_max_steps;
	KeyFrame[playIndex].ang_hojas_inc = (KeyFrame[playIndex + 1].ang_hojas - KeyFrame[playIndex].ang_hojas) / i_max_steps;
	KeyFrame[playIndex].giroAvionInc = (KeyFrame[playIndex + 1].giroAvion - KeyFrame[playIndex].giroAvion) / i_max_steps;

}


void animate(void)
{
	//Movimiento del objeto con barra espaciadora
	if (play) {
		//fin de animación entre frames?
		if (i_curr_steps >= i_max_steps) {
			playIndex++;
			printf("playindex : %d\n", playIndex);
			//Fin de toda la animación con último frame?
			if (playIndex > FrameIndex - 2) {
				printf("Frame index= %d\n", FrameIndex);
				printf("termino la animacion\n");
				playIndex = 0;
				play = false;
			} else {
				//Interpolación del próximo cuadro
				
				i_curr_steps = 0; //Resetea contador
				//Interpolar
				interpolation();
			}
		} else {
			//Dibujar Animación
			ang_tronco += KeyFrame[playIndex].ang_tronco_inc ;
			ang_hojas += KeyFrame[playIndex].ang_hojas_inc ;
			giroAvion += KeyFrame[playIndex].giroAvionInc;
			i_curr_steps++;
		}

	}
}

///////////////* FIN KEYFRAMES*////////////////////////////

int main()
{
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


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.4f, 0.4f,
		0.0f, -1.0f, 0.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	unsigned int spotLightCount = 0;

	//linterna
	luzLinterna = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);

	faroDelantero = SpotLight(1.0f, 1.0f, 0.0f,
		1.0f, 0.2f,
		5.0f, 10.0f, 0.0f,
		-2.0f, 0.0f, 0.0f,
		1.0f, 0.001f, 0.001f,
		20.0f);

	faroTrasero = SpotLight(0.0f, 1.0f, 1.0f,
		1.0f, 0.2f,
		5.0f, 10.0f, 0.0f,
		2.0f, 0.0f, 0.0f,
		1.0f, 0.001f, 0.001f,
		20.0f);

	luzCofre = SpotLight(0.25f, 1.0f, 0.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		-2.0f, 0.0f, 0.0f,
		1.0f, 0.001f, 0.001f,
		15.0f);

	luzDiablo = PointLight(1.0f, 0.125f, 0.0f,
		0.8f, 0.8f,
		6.0f, 2.5f, 1.5f,
		0.3f, 0.2f, 0.1f);

	luzPoste = PointLight(1.0f, 1.0f, 1.0f,
		1.0f, 2.0f,
		0.0f, 12.0f, -19.25f,
		1.0f, 0.01f, 0.01f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset=0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	glm::vec3 posblackhawk = glm::vec3(2.0f, 0.0f, 0.0f);

	std::vector<MovingEntity*> movingEntities;


        movingEntities.push_back(new Beastie(&beastieCarro_M, &beastieCarroLlantaTras_M, &beastieCarroLlantaDel_M, glm::vec3(0.0f), [](GLfloat t) {
		return glm::vec3(20.0f * cos(t), 0.0f, 50.0f * sin(0.666f * t));
	}));

        movingEntities.push_back(new Beastie(&beastieCarro_M, &beastieCarroLlantaTras_M, &beastieCarroLlantaDel_M, glm::vec3(0.0f), [](GLfloat t) {
		return glm::vec3(40.0f * cos(t), 75.0f + 20.0f * sin(t), 100.0f * sin(0.666f * t));
	}));

        movingEntities.push_back(new Xue(&XueCarro_M, &XuePaleta_M, &XueTurbina_M, glm::vec3(0.0f), [](GLfloat t) {
		return glm::vec3(40.0f * cos(t), 0.0f, 40.0f * sin(0.666f * t));
	}));

        avatar = new Avatar(&avatarCuerpo_M, &avatarMuslo_M, &avatarPierna_M, &avatarBrazo_M, &avatarAntebrazo_M, glm::vec3(0.0f, 0.0f, 2.0f));
	avatar->startAnimation();

        camera.setAvatar(avatar);

        camera.addLocation(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
        camera.addLocation(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec2(45.0f, 0.0f));
        camera.addLocation(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 45.0f));
        camera.addLocation(glm::vec3(2.0f, 0.0f, 0.0f), glm::vec2(0.0f, 90.0f));

	// Lee los keyframes del archivo
	readKeyframes("keyframes-palmera.txt");


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

	// Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		GLfloat dt = now - lastTime;
		deltaTime = dt;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		mainWindow.UpdatePos(dt);

                pointLightCount = 0;
                spotLightCount = 0;

		// Recibir eventos del usuario
		glfwPollEvents();
		if (camera.getEstado() == RIGGING_CAMERA) {
			camera.updateRig(dt);
		} else {
			camera.keyControl(mainWindow.getsKeys(), deltaTime);
			camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		}

		//-------Para Keyframes
		inputKeyframes(mainWindow.getsKeys());
		animate();

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
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

		// // Dado de Opengl
		// // Ejercicio 1: Texturizar su cubo con la imagen dado_animales ya optimizada por ustedes
		// model = glm::mat4(1.0);
		// model = glm::translate(model, glm::vec3(-10.5f, 5.0f, -10.0f));
		// glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		// dadoTexture.UseTexture();
		// meshList[5]->RenderMesh();

		// Diablo
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.5f, 0.0f, -25.0));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Diablo_M.RenderModel();

                if (mainWindow.getPrendeDiablo()) {
			model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
			lightpos = model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
			luzDiablo.SetPos(lightpos);
			pointLights[pointLightCount++] = luzDiablo;
		}

		model = glm::mat4(1.0);
		posblackhawk=glm::vec3(posXavion + movAvion_x, posYavion + movAvion_y, posZavion);
		model = glm::translate(model, posblackhawk);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, giroAvion * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//color = glm::vec3(0.0f, 1.0f, 0.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();

		// Tronco
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.5f, 0.0f, 5.0));
		model = glm::scale(model, glm::vec3(2.0f));
		modelcuerpo = model;

		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piedra_0_M.RenderModel();

		model = glm::rotate(model, glm::radians(ang_tronco), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		palmera_ruina_tronco_M.RenderModel();

		model = glm::translate(model, glm::vec3(0.125f, 6.0f, 0.5));
		model = glm::rotate(model, glm::radians(ang_hojas), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		palmera_ruina_hojas_M.RenderModel();

                model = modelcuerpo;
		model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 0.0));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tunel_ruina_M.RenderModel();



		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 0.0f, 10.0));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cajaFrente_M.RenderModel();
		casitaIzq_M.RenderModel();
		castillo_M.RenderModel();
		constFrente_M.RenderModel();
		constMedioChiquito_M.RenderModel();
		constMedio_M.RenderModel();
		EsqIzqFrente_M.RenderModel();
		esqIzq_M.RenderModel();
		explanadaDer_M.RenderModel();
		ruinasIzq_M.RenderModel();


		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

                for (auto entity : movingEntities) {
			entity->update(dt);
			entity->render(uniformModel);
		}

		avatar->update(dt);
		avatar->render(uniformModel);

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

		int numpapus = 9;
		GLfloat angdif = 15.0f;
                for (int i = 0; i < numpapus; i++) {

			model = modelaux;
			model = glm::translate(model, glm::vec3(0.0f, 6.2f, 0.5025f));
			GLfloat angulo = (angdif * (numpapus/2)) - angdif * i;
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
		glm::mat4 papu = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
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
	}

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
				printf("\n presiona 0 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimacion = 0;

			} else {
				play = false;

			}
		}
	}
	if (keys[GLFW_KEY_0]) {
		if (habilitaranimacion < 1 && reproduciranimacion>0) {
			printf("Ya puedes reproducir de nuevo la animación con la tecla de barra espaciadora'\n");
			reproduciranimacion = 0;
		}
	}

	if (keys[GLFW_KEY_L]) {
		if (guardoFrame < 1) {
			saveFrame();
			printf("ang_tronco es: %f\n", ang_tronco);
			printf("ang_hojas es: %f\n", ang_hojas);
			printf("presiona P para habilitar guardar otro frame'\n");
			guardoFrame++;
			reinicioFrame = 0;
		}
	}
	if (keys[GLFW_KEY_P]) {
		if (reinicioFrame < 1) {
			guardoFrame = 0;
			reinicioFrame++;
			printf("Ya puedes guardar otro frame presionando la tecla L'\n");
		}
	}


	if (keys[GLFW_KEY_1]) {
		if (ciclo < 1) {
			//printf("movAvion_x es: %f\n", movAvion_x);
			ang_tronco += 5.0f;
			printf("\n ang_tronco es: %f\n", ang_tronco);
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
			//printf("movAvion_x es: %f\n", movAvion_x);
			ang_tronco -= 5.0f;
			printf("\n ang_tronco es: %f\n", ang_tronco);
			ciclo3++;
			ciclo4 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_4]) {
		if (ciclo4 < 1) {
			ciclo3 = 0;
			ciclo4++;
			printf("\n Ya puedes modificar tu variable presionando la tecla 1\n");
		}
	}


	if (keys[GLFW_KEY_5]) {
		if (ciclo5 < 1) {
			//printf("movAvion_x es: %f\n", movAvion_x);
			ang_hojas += 5.0f;
			printf("\n ang_hojas es: %f\n", ang_hojas);
			ciclo5++;
			ciclo6 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_6]) {
		if (ciclo6 < 1) {
			ciclo5 = 0;
			ciclo6++;
			printf("\n Ya puedes modificar tu variable presionando la tecla 1\n");
		}
	}


	if (keys[GLFW_KEY_7]) {
		if (ciclo7 < 1) {
			//printf("movAvion_x es: %f\n", movAvion_x);
			ang_hojas -= 5.0f;
			printf("\n ang_hojas es: %f\n", ang_hojas);
			ciclo7++;
			ciclo8 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_8]) {
		if (ciclo8 < 1) {
			ciclo7 = 0;
			ciclo8++;
			printf("\n Ya puedes modificar tu variable presionando la tecla 1\n");
		}
	}

	if (keys[GLFW_KEY_9]) {
		if (ciclo9 < 1) {
			//printf("movAvion_x es: %f\n", movAvion_x);
			giroAvion += 180.0f;
			printf("\n asdf es: %f\n", giroAvion);
			ciclo9++;
			ciclo10 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_O]) {
		if (ciclo10 < 1) {
			ciclo9 = 0;
			ciclo10++;
			printf("\n Ya puedes modificar tu variable presionando la tecla 1\n");
		}
	}
}
