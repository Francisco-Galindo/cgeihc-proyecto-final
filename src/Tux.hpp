#pragma once

#include "AnimatingEntity.hpp"
#include "Model.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Tux: public AnimatingEntity
{
public:
	Tux(Model *cuerpoModel, Model *alaModel, glm::mat4 model) {
		cuerpo_M = cuerpoModel;
		ala_M = alaModel;
		baseModel = model;
		goingUp = false;
		animating = false;
		return;
	}
	glm::vec3 getPos() { return pos; }
	glm::mat4 getModel() { return baseModel; }
	bool getAnimating() { return animating; }
	// bool getMoving() { return moving; };
	void update(GLfloat dt);
	void startAnimation();
	void render(GLint uniformModel);
	// ~MovingEntity() = default;
protected:
	Model *cuerpo_M, *ala_M;
	GLfloat hombroAng, piernaAng, rodillaAng, rodillaAng2, anguloGiro;
	GLfloat animT, tWhenWaving, anguloAla1, anguloAla2;
	bool goingUp, animating;
	glm::mat4 baseModel;
	glm::vec3 dir;
}; 
