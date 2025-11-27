#pragma once
#include "Model.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class MovingEntity
{
public:
	MovingEntity() {
		pos = glm::vec3(0.0f);
		t = 0.0f;
		vel = 1.0f;
		pos = glm::vec3(0.0f);
		oldpos = glm::vec3(0.0f);
		oldoldpos = glm::vec3(0.0f);
		baseModel = glm::mat4(1.0f);
		angle = 0;
	}
	MovingEntity(glm::vec3 orig, std::function<glm::vec3(GLfloat)> callback);
	glm::vec3 getPos() { return pos; }
	glm::vec3 getDiff() { return diff; }
	void update(GLfloat dt);
	void setBaseModel(glm::mat4 mat);
	void setAngle(GLfloat ang);
	virtual void updateAnimation(GLfloat dt) { return; };
	virtual void render(GLint uniformModel) = 0;

	// ~MovingEntity() = default;
protected:
	glm::vec3 pos, oldpos, oldoldpos, diff, oldDiff, diff2, orig;
	glm::mat4 baseModel;
	GLfloat t, vel, angle;
	std::function<glm::vec3(GLfloat)> curveCallBack;
}; 
