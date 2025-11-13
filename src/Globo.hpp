#pragma once
#include "MovingEntity.hpp"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Globo: public MovingEntity
{
public:
	Globo(Model *cuerpoModel, glm::vec3 orig, std::function<glm::vec3(GLfloat)> callback)
	: MovingEntity(orig, callback) {
		t = 0.0f;
		anguloGiro = 0;
		anguloVuelta = 0;
		anguloGiro = 0;
		cuerpo_M = cuerpoModel;
	}
	void updateAnimation(GLfloat dt);
	void render(GLint uniformModel);
	// ~Beastie() = default;
private:
	GLfloat anguloLLanta, anguloVuelta, anguloGiro;
	Model *cuerpo_M, *llantaTras_M, *llantaDel_M;
}; 
