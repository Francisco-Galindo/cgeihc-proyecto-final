#pragma once

#include "AnimatingEntity.hpp"
#include "Model.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Suzanne: public AnimatingEntity
{
public:
	Suzanne(Model *cuerpoModel, Model *piernaModel, Model *antebrazoModel, Model *brazoModel, glm::mat4 model) {
		cuerpo_M = cuerpoModel;
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
	bool getGolpeando() { return golpeando; }
	bool getAnimating() { return animating; }
	void setModel(glm::mat4 model);
	void update(GLfloat dt);
	void startAnimation();
	void render(GLint uniformModel);
	// ~MovingEntity() = default;
protected:
	Model *cuerpo_M, *pierna_M, *antebrazo_M, *brazo_M;
	GLfloat animT, tWhenWaving, anguloHombro1, anguloCodo, anguloHombro2;
	bool goingUp, animating, golpeando;
	glm::mat4 baseModel;
	glm::vec3 dir;
}; 
