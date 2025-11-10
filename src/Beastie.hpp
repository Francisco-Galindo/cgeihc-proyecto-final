#pragma once
#include "MovingEntity.hpp"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Beastie: public MovingEntity
{
public:
	Beastie(Model *cuerpoModel, Model *llantaTrasModel, Model *llantaDelModel, glm::vec3 orig, std::function<glm::vec3(GLfloat)> callback)
	: MovingEntity(orig, callback) {
		anguloGiro = 0;
		anguloVuelta = 0;
		anguloGiro = 0;
		cuerpo_M = cuerpoModel;
		llantaDel_M = llantaDelModel;
		llantaTras_M = llantaTrasModel;
	}
	void updateAnimation(GLfloat dt);
	void render(GLint uniformModel);
	// ~Beastie() = default;
private:
	GLfloat anguloLLanta, anguloVuelta, anguloGiro;
	Model *cuerpo_M, *llantaTras_M, *llantaDel_M;
}; 
