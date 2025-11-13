#include "Delfin.hpp"

void Delfin::updateAnimation(GLfloat dt) {
        anguloYaw = atan2(diff.x, diff.z) + 3.1415;
        anguloPitch = asin(-glm::normalize(diff).y) + 1.57;

        if (t > 3.15) {
		t = 3.15;
		animating = false;
	}
}

void Delfin::render(GLint uniformModel) {
	// Carro
	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 modelaux = glm::mat4(1.0);

	model = glm::translate(model, pos);
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
	model = glm::rotate(model, anguloYaw, glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, anguloPitch, glm::vec3(-1.0f, 0.0f, 0.0));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
	modelaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	cuerpo_M->RenderModel();

}

void Delfin::restartAnim() {
	t = 0;
}
