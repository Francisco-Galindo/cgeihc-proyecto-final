#pragma once
#include "MovingEntity.hpp"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Delfin: public MovingEntity
{
public:
	Delfin(Model *cuerpoModel, glm::vec3 orig, std::function<glm::vec3(GLfloat)> callback)
	: MovingEntity(orig, callback) {
		anguloPitch = 0;
		anguloYaw = 0;
		cuerpo_M = cuerpoModel;
	}
	void updateAnimation(GLfloat dt);
        bool getAnimating() { return animating; };
        void restartAnim();
	void render(GLint uniformModel);
	// ~Beastie() = default;
private:
	GLfloat anguloPitch, anguloYaw;
	bool animating;
	Model *cuerpo_M, *llantaTras_M, *llantaDel_M;
}; 
