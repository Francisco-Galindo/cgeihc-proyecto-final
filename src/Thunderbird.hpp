#pragma once
#include "MovingEntity.hpp"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Thunderbird: public MovingEntity
{
public:
	Thunderbird(Model *cuerpoModel, Model *alaModel, glm::vec3 orig, std::function<glm::vec3(GLfloat)> callback)
	: MovingEntity(orig, callback) {
		anguloGiro = 0;
		anguloVuelta = 0;
		anguloGiro = 0;
		cuerpo_M = cuerpoModel;
		ala_M = alaModel;
	}
	void updateAnimation(GLfloat dt);
	void render(GLint uniformModel);
private:
	GLfloat anguloAlas, anguloVuelta, anguloGiro;
	Model *cuerpo_M, *ala_M;
}; 
