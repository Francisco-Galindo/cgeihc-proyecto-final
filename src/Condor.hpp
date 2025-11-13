
#pragma once

#include "AnimatingEntity.hpp"
#include "Model.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Condor: public AnimatingEntity
{
public:
	Condor(Model *cuerpoModel, Model *musloModel, Model *piernaModel, Model *antebrazoModel, Model *brazoModel, glm::mat4 model) {
		cuerpo_M = cuerpoModel;
		muslo_M = musloModel;
		pierna_M = piernaModel;
		antebrazo_M = antebrazoModel;
		brazo_M = brazoModel;
		baseModel = model;
		anguloCodo = 0.0f;
		anguloHombro1 = 0.0f;
		anguloHombro2 = 0.0f;
		animating = false;
		return;
	}
	glm::vec3 getPos() { return pos; }
	glm::mat4 getModel() { return baseModel; }
	bool getAnimating() { return animating; }
	bool getGolpeando() { return golpeando; }
	void setModel(glm::mat4 model);
	void update(GLfloat dt);
	void startAnimation();
	void render(GLint uniformModel);
	// ~MovingEntity() = default;
protected:
	Model *cuerpo_M, *muslo_M, *pierna_M, *antebrazo_M, *brazo_M;
	GLfloat animT, tWhenWaving, anguloHombro1, anguloCodo, anguloHombro2;
	bool golpeando, animating;
	glm::mat4 baseModel;
	glm::vec3 dir;
}; 
