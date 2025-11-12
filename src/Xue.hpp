#pragma once
#include "MovingEntity.hpp"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Xue: public MovingEntity
{
public:
	Xue(Model *cuerpoModel, Model *paletaModel, Model *turbinaModel, glm::vec3 orig, std::function<glm::vec3(GLfloat)> callback)
	: MovingEntity(orig, callback) {
		anguloGiro = 0;
		anguloVuelta = 0;
		anguloGiro = 0;
		cuerpo_M = cuerpoModel;
		paleta_M = paletaModel;
		turbina_M = turbinaModel;
	}
	void updateAnimation(GLfloat dt);
	void render(GLint uniformModel);
private:
	GLfloat anguloLLanta, anguloVuelta, anguloGiro;
	Model *cuerpo_M, *paleta_M, *turbina_M;
}; 
