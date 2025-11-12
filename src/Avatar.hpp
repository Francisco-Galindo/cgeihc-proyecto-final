#pragma once

#include "AnimatingEntity.hpp"
#include "Model.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Avatar: public AnimatingEntity
{
public:
	Avatar(Model *cuerpoModel, Model *musloModel, Model
	       *piernaModel, Model *brazoModel, Model *antebrazoModel,
	       glm::vec3 orig) {

		cuerpo_M = cuerpoModel;
		muslo_M = musloModel;
		pierna_M = piernaModel;
		brazo_M = brazoModel;
                antebrazo_M = antebrazoModel;

		pos = orig;
		return;
	}
	glm::vec3 getPos() { return pos; }
	bool getMoving() { return moving; };
	void update(GLfloat dt);
	void startAnimation();
	void render(GLint uniformModel);
	void setDir(glm::vec3 newDir);
	void setMoving(bool newMoving);
	void moveToDir(GLfloat distance);
	// ~MovingEntity() = default;
protected:
	Model *cuerpo_M, *muslo_M, *pierna_M, *brazo_M, *antebrazo_M;
	GLfloat hombroAng, piernaAng, rodillaAng, rodillaAng2, anguloGiro;
	bool moving;
	glm::mat4 baseModel;
	glm::vec3 dir;
}; 
