#include "Condor.hpp"

void Condor::update(GLfloat dt) {
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

void Condor::startAnimation() {
	animT = 0.0f;
	anguloHombro1 = 0.0f;
	anguloCodo = 0.0f;
	anguloHombro2 = 0.0f;
	animating = true;
	golpeando = true;
}

void Condor::render(GLint uniformModel) {
	// Condor
	glm::mat4 model = baseModel;
	glm::mat4 modelaux = model;
	glm::mat4 modelauxaux = model;

	model = glm::translate(model, pos);
	model = glm::translate(model, glm::vec3(0.0f, 4.25f, -3.0f));
	model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
	modelaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	cuerpo_M->RenderModel();


        model = modelaux;
	model = glm::translate(model, glm::vec3(0.085f, 0.0f, 0.0f));
	modelauxaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	muslo_M->RenderModel();

        model = modelauxaux;
	model = glm::translate(model, glm::vec3(0.0f, -0.3f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pierna_M->RenderModel();


        model = modelaux;
	model = glm::translate(model, glm::vec3(-0.085f, 0.0f, 0.0f));
	modelauxaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	muslo_M->RenderModel();

        model = modelauxaux;
	model = glm::translate(model, glm::vec3(0.0f, -0.3f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pierna_M->RenderModel();


        model = modelaux;
	// model = glm::translate(model, glm::vec3(-0.09f, 0.6384f, 0.0f));
	model = glm::translate(model, glm::vec3(0.11f, 0.4f, 0.0f));
	model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	modelauxaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	antebrazo_M->RenderModel();

        model = modelauxaux;
	// model = glm::translate(model, glm::vec3(-0.09f, 0.6384f, 0.0f));
	model = glm::translate(model, glm::vec3(-0.13f, 0.016f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	// model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	brazo_M->RenderModel();


        model = modelaux;
	// model = glm::translate(model, glm::vec3(-0.09f, 0.6384f, 0.0f));
	model = glm::translate(model, glm::vec3(-0.11f, 0.4f, 0.0f));
	model = glm::rotate(model, glm::radians(-30.0f - anguloHombro1), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-60.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	modelauxaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	antebrazo_M->RenderModel();

        model = modelauxaux;
	// model = glm::translate(model, glm::vec3(-0.09f, 0.6384f, 0.0f));
	model = glm::translate(model, glm::vec3(-0.13f, 0.016f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f - anguloCodo), glm::vec3(0.0f, 1.0f, 0.0f));
	// model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	brazo_M->RenderModel();
}

void Condor::setModel(glm::mat4 model) {
	baseModel = model;
}
