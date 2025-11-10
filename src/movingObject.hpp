#pragma once
#include "Model.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class MovingEntity
{
public:
	MovingEntity(std::function<glm::vec3(GLfloat)>);
	glm::vec3 getPos() { return pos; }
	void update(GLfloat dt);
	void updateAnimation() { return; };

	~MovingEntity();
private:
	glm::vec3 pos, oldpos, oldoldpos;
	GLfloat t, vel;
	std::function<glm::vec3(GLfloat)> curveCallBack;
}; 
