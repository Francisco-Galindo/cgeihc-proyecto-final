#include "Globo.hpp"

void Globo::updateAnimation(GLfloat dt) {
}

void Globo::render(GLint uniformModel) {
	// Globo
	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 modelaux = glm::mat4(1.0);

	model = glm::translate(model, pos);
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
	// model = glm::rotate(model, anguloGiro, glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
	modelaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	cuerpo_M->RenderModel();
}
