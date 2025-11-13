#include "Suzanne.hpp"

void Suzanne::update(GLfloat dt) {
	if (!animating) {
		return;
	}

	dt *= 120;

        if (golpeando && anguloCodo <= 90.0f) {
		anguloCodo += dt;
		anguloHombro1 += dt * 0.66;
        } else if (golpeando && anguloCodo > 90.f) {
		anguloCodo = 90.0f;
		anguloHombro1 = 60.0f;
		golpeando = false;
	} else if (!golpeando && anguloCodo > 0.0f) {
		anguloCodo -= dt;
		anguloHombro1 -= dt * 0.66;
        } else if (!golpeando && anguloCodo <= 0.0f) {
		anguloCodo = 0.0f;
		anguloHombro1 = 0.0f;
		animating = false;
	}

}

void Suzanne::startAnimation() {
	animT = 0.0f;
	anguloHombro1 = 0.0f;
	anguloCodo = 0.0f;
	anguloHombro2 = 0.0f;
	animating = true;
	golpeando = true;
}

void Suzanne::render(GLint uniformModel) {
	// Suzanne
	glm::mat4 model = baseModel;
	glm::mat4 modelaux = model;
	glm::mat4 modelauxaux = model;

	model = glm::translate(model, pos);
	model = glm::translate(model, glm::vec3(0.0f, 3.75f, 0.0f));
	model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
	modelaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	cuerpo_M->RenderModel();


        model = modelaux;
	model = glm::translate(model, glm::vec3(0.0375f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pierna_M->RenderModel();

        model = modelaux;
	model = glm::translate(model, glm::vec3(-0.0375f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pierna_M->RenderModel();

        model = modelaux;
	// model = glm::translate(model, glm::vec3(-0.09f, 0.6384f, 0.0f));
	model = glm::translate(model, glm::vec3(0.085f, 0.255f, 0.0f));
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(80.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	modelauxaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	antebrazo_M->RenderModel();

        model = modelauxaux;
	// model = glm::translate(model, glm::vec3(-0.09f, 0.6384f, 0.0f));
	// model = glm::translate(model, glm::vec3(0.015f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.14f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	brazo_M->RenderModel();


        model = modelaux;
	// model = glm::translate(model, glm::vec3(-0.09f, 0.6384f, 0.0f));
	model = glm::translate(model, glm::vec3(-0.085f, 0.255f, 0.0f));
	// model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(30.0f + anguloHombro1), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-80.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	modelauxaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	antebrazo_M->RenderModel();

        model = modelauxaux;
	// model = glm::translate(model, glm::vec3(-0.09f, 0.6384f, 0.0f));
	model = glm::translate(model, glm::vec3(0.14f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f - anguloCodo), glm::vec3(0.0f, 1.0f, 0.0f));
	// model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	brazo_M->RenderModel();
}

void Suzanne::setModel(glm::mat4 model) {
	baseModel = model;
}
