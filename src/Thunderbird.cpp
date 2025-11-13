#include "Thunderbird.hpp"

void Thunderbird::updateAnimation(GLfloat dt) {
        anguloGiro = atan2(diff.x, diff.z) + 3.1415;
	GLfloat anguloDiff2 = atan2(diff2.x, diff2.z) + 3.1415;

	anguloVuelta = (anguloDiff2 - anguloGiro);
        if (anguloVuelta > 3.141592) {
		anguloVuelta -= 6.29;
        } else if (anguloVuelta < -3.141592) {
		anguloVuelta += 6.29;
	}

        anguloVuelta /= 5.0f;

        anguloAlas = 30 * sin(t * 3);
}

void Thunderbird::render(GLint uniformModel) {
	// Thunderbird
	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 modelaux = glm::mat4(1.0);

	model = glm::translate(model, pos);
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
	model = glm::rotate(model, anguloGiro, glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, anguloVuelta, glm::vec3(0.0f, 0.0f, 1.0));
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
	modelaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	cuerpo_M->RenderModel();

	model = modelaux;
	model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.25f));
	model = glm::rotate(model, glm::radians(anguloAlas), glm::vec3(0.0f, 0.0f, 1.0));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	ala_M->RenderModel();

	model = modelaux;
	model = glm::translate(model, glm::vec3(0.0f, 0.3f, -0.25f));
	model = glm::rotate(model, glm::radians(-anguloAlas), glm::vec3(0.0f, 0.0f, 1.0));
	model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	ala_M->RenderModel();

}
