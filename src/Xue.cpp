#include "Xue.hpp"

void Xue::updateAnimation(GLfloat dt) {
        anguloGiro = atan2(diff.x, diff.z) + 3.1415;
	GLfloat anguloDiff2 = atan2(diff2.x, diff2.z) + 3.1415;

	anguloVuelta = (anguloDiff2 - anguloGiro);
        if (anguloVuelta > 3.141592) {
		anguloVuelta -= 6.29;
        } else if (anguloVuelta < -3.141592) {
		anguloVuelta += 6.29;
	}

        anguloVuelta /= 5.0f;

        anguloLLanta -= glm::length(diff) * dt;
}

void Xue::render(GLint uniformModel) {
	// Carro
	glm::mat4 model = baseModel;
	glm::mat4 modelaux = baseModel;

	model = glm::translate(model, pos);
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
	model = glm::rotate(model, anguloGiro, glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, anguloVuelta, glm::vec3(0.0f, 0.0f, 1.0));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	modelaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	cuerpo_M->RenderModel();

	model = modelaux;
	model = glm::translate(model, glm::vec3(0.0f, 0.6f, 0.54f));
	model = glm::rotate(model, anguloLLanta, glm::vec3(0.0f, 0.0f, 1.0));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	turbina_M->RenderModel();

	model = modelaux;
	model = glm::translate(model, glm::vec3(0.0f, 0.36f, 0.579f));
	model = glm::rotate(model, -2.0f * anguloVuelta, glm::vec3(0.0f, 1.0f, 0.0));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	paleta_M->RenderModel();
}
