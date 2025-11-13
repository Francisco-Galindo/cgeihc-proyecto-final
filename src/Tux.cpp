#include "Tux.hpp"

void Tux::update(GLfloat dt) {
	if (!animating) {
		return;
	}

	animT += dt;

	if (goingUp && animT < 1.0f) {
		anguloAla1 = animT * 1.57;
		return;
	} else if (goingUp){
		tWhenWaving = animT;
		goingUp = false;
		printf("YA NO\n");
	}                  

	if (!goingUp && animT - tWhenWaving < 3.1416 * 3) {
		anguloAla2 = 20 * sin(3.0f * (animT - tWhenWaving));
        } else if (!goingUp && anguloAla1 > 0.0f) {
		anguloAla1 -= dt;
        } else if (!goingUp && anguloAla1 <= 0.0f) {
		animating = false;
	}
}

void Tux::startAnimation() {
	animT = 0.0f;
	anguloAla1 = 0.0f;
	anguloAla2 = 0.0f;
	goingUp = true;
	animating = true;
}

void Tux::render(GLint uniformModel) {
	// Carro
	glm::mat4 model = baseModel;
	glm::mat4 modelaux = model;

	model = glm::translate(model, pos);
	// model = glm::rotate(model, anguloGiro, glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0));
	model = glm::translate(model, glm::vec3(0.0f, -0.75f, -1.125f));
	model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
	modelaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	cuerpo_M->RenderModel();

        model = modelaux;
	model = glm::translate(model, glm::vec3(-0.12f, 0.25f, 0.0f));
	model = glm::rotate(model, glm::radians(anguloAla2), glm::vec3(0.0f, 0.0f, 1.0));
	model = glm::rotate(model, anguloAla1, glm::vec3(1.0f, 0.0f, 0.0));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	ala_M->RenderModel();

        model = modelaux;
	model = glm::translate(model, glm::vec3(0.12f, 0.25f, 0.0f));
	model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	ala_M->RenderModel();
}
