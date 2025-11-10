#include "MovingEntity.hpp"

MovingEntity::MovingEntity(glm::vec3 theorig, std::function<glm::vec3(GLfloat)> callback) {
	t = 0.0f;
	vel = 1.0f;
	pos = glm::vec3(0.0f);
	oldpos = glm::vec3(0.0f);
	oldoldpos = glm::vec3(0.0f);
	curveCallBack = callback;
	orig = theorig;
}

void MovingEntity::update(GLfloat dt) {
	t += vel * dt;
	oldoldpos = oldpos;
	oldpos = pos;


        pos = orig + curveCallBack(t);

	oldDiff = diff;
	diff = (pos - oldpos) / dt;
	diff2 = (diff - oldDiff) / dt;
	this->updateAnimation(dt);
}
