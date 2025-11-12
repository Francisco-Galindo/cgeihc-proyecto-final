#include "Beastie.hpp"

void Beastie::updateAnimation(GLfloat dt) {
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

void Beastie::render(GLint uniformModel) {
	// Carro
	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 modelaux = glm::mat4(1.0);

	model = glm::translate(model, pos);
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
	model = glm::rotate(model, anguloGiro, glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
	modelaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	cuerpo_M->RenderModel();

	model = modelaux;
	model = glm::translate(model, glm::vec3(-0.25f, 0.147f, -0.57f));
	model = glm::rotate(model, anguloVuelta, glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, anguloLLanta, glm::vec3(1.0f, 0.0f, 0.0));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	llantaDel_M->RenderModel();

	model = modelaux;
	model = glm::translate(model, glm::vec3(0.25f, 0.147f, -0.57f));
	model = glm::rotate(model, anguloVuelta, glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, anguloLLanta, glm::vec3(1.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	llantaDel_M->RenderModel();

	model = modelaux;
	model = glm::translate(model, glm::vec3(-0.267f, 0.215f, 0.459f));
	model = glm::rotate(model, anguloLLanta, glm::vec3(1.0f, 0.0f, 0.0));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	llantaTras_M->RenderModel();

	model = modelaux;
	model = glm::translate(model, glm::vec3(0.267f, 0.215f, 0.459f));
	model = glm::rotate(model, anguloLLanta, glm::vec3(1.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	llantaTras_M->RenderModel();

}
