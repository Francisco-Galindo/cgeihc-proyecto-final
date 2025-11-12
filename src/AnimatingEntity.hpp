#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class AnimatingEntity
{
public:
	AnimatingEntity() {
		pos = glm::vec3(0.0f);
	}
        AnimatingEntity(glm::vec3 orig);
	glm::vec3 getPos() { return pos; }
	virtual void update(GLfloat dt) = 0;
	virtual void startAnimation() = 0;
	virtual void render(GLint uniformModel) = 0;
	// ~MovingEntity() = default;
protected:
	glm::vec3 pos;
	GLfloat animT, animVel;
	bool animating;
}; 
