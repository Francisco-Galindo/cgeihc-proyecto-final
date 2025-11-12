#include "Avatar.hpp"
#include "AnimatingEntity.hpp"


void Avatar::update(GLfloat dt) {
	if (!moving) {
		return;
	}

        anguloGiro = atan2(dir.x, dir.z);
	animT += animVel * dt;
	hombroAng = 30 * sin(animT);
	piernaAng = 30 * sin(animT);
	rodillaAng = 45 * sin(animT) + 45;
	rodillaAng2 = 45 * cos(animT) + 45;
}

void Avatar::startAnimation() {
	animVel = 5.0f;
	hombroAng = 0;
	piernaAng = 0;
	rodillaAng = 0;
}

void Avatar::render(GLint uniformModel) {
	// Carro
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 modelaux = model;
	glm::mat4 modelauxaux = model;

	model = glm::translate(model, pos);
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
	model = glm::rotate(model, anguloGiro, glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.645f, 0.0));
	modelaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	cuerpo_M->RenderModel();


        model = modelaux;
	model = glm::translate(model, glm::vec3(0.06615f, 0.125f, 0.0f));
	model = glm::rotate(model, glm::radians(piernaAng), glm::vec3(1.0f, 0.0f, 0.0));
	modelauxaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	muslo_M->RenderModel();

        model = modelauxaux;
	model = glm::translate(model, glm::vec3(0.0f, -0.29f, -0.05f));
	model = glm::rotate(model, glm::radians(rodillaAng), glm::vec3(1.0f, 0.0f, 0.0));
	modelauxaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pierna_M->RenderModel();


        model = modelaux;
	model = glm::translate(model, glm::vec3(-0.06615f, 0.125f, 0.0f));
	model = glm::rotate(model, glm::radians(-piernaAng), glm::vec3(1.0f, 0.0f, 0.0));
	modelauxaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	muslo_M->RenderModel();

        model = modelauxaux;
	model = glm::translate(model, glm::vec3(0.0f, -0.29f, -0.05f));
	model = glm::rotate(model, glm::radians(rodillaAng2), glm::vec3(1.0f, 0.0f, 0.0));
	modelauxaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pierna_M->RenderModel();


        model = modelaux;
	model = glm::translate(model, glm::vec3(-0.09711f, 0.5f, -0.05f));
	model = glm::rotate(model, glm::radians(hombroAng), glm::vec3(1.0f, 0.0f, 0.0));
	model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0));
	model = glm::translate(model, glm::vec3(0.02f, 0.0f, 0.0f));
	modelauxaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	brazo_M->RenderModel();

        model = modelauxaux;
	model = glm::translate(model, glm::vec3(-0.15f, 0.0f, 0.05f));
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelauxaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	antebrazo_M->RenderModel();


        model = modelaux;
	model = glm::translate(model, glm::vec3(0.09711f, 0.5f, -0.05f));
	model = glm::rotate(model, glm::radians(-hombroAng), glm::vec3(1.0f, 0.0f, 0.0));
	model = glm::rotate(model, glm::radians(-60.0f), glm::vec3(0.0f, 0.0f, 1.0));
	model = glm::translate(model, glm::vec3(-0.02f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	modelauxaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	brazo_M->RenderModel();

        model = modelauxaux;
	model = glm::translate(model, glm::vec3(-0.15f, 0.0f, 0.05f));
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelauxaux = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	antebrazo_M->RenderModel();
}

void Avatar::setDir(glm::vec3 newDir) {
	dir = glm::normalize(newDir);
}

void Avatar::setMoving(bool newMoving) {
	moving = newMoving;
}

void Avatar::moveToDir(GLfloat distance) {
	pos += distance * dir;
}
