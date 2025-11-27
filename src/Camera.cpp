#include "Camera.h"
#include "Avatar.hpp"
#include "Mesh.h"


Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

        estado = FREE_CAMERA;

        cameraRig = CameraRig(position, [](GLfloat t) {
		return glm::vec3(150.0f * cos(t / 10.0f), 75.0f + 10.0f * sin(t / 3.0f), 150.0f * sin(t / 10.0f));
	});

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

        distanceToAvatar = 4.0f;

        locationIndex = -1;


	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (estado == THIRD_PERSON_CAMERA) {
		if (keys[GLFW_KEY_Q]) {
			distanceToAvatar -= 3.0f * velocity;
                        if (distanceToAvatar < 1.0f) {
				distanceToAvatar = 1.0f;
			}
		}

		if (keys[GLFW_KEY_E]) {
			distanceToAvatar += 3.0f * velocity;
		}


		avatar->setMoving(false);
		if (keys[GLFW_KEY_A] && keys[GLFW_KEY_W]) {
			glm::vec4 newDir = glm::vec4(front.x, 0.0f, front.z, 0.0f);
			glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			newDir = rot * newDir;
			avatar->setDir(newDir);
			avatar->moveToDir(velocity * 0.707); // Cuidado con la velocidad en diagonal
			avatar->setMoving(true);
		} else if (keys[GLFW_KEY_D] && keys[GLFW_KEY_W]) {
			glm::vec4 newDir = glm::vec4(front.x, 0.0f, front.z, 0.0f);
			glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			newDir = rot * newDir;
			avatar->setDir(newDir);
			avatar->moveToDir(velocity * 0.707); // Cuidado con la velocidad en diagonal
			avatar->setMoving(true);
		} else if (keys[GLFW_KEY_A] && keys[GLFW_KEY_S]) {
			glm::vec4 newDir = glm::vec4(front.x, 0.0f, front.z, 0.0f);
			glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			newDir = rot * newDir;
			avatar->setDir(newDir);
			avatar->moveToDir(velocity * 0.707); // Cuidado con la velocidad en diagonal
			avatar->setMoving(true);
		} else if (keys[GLFW_KEY_D] && keys[GLFW_KEY_S]) {
			glm::vec4 newDir = glm::vec4(front.x, 0.0f, front.z, 0.0f);
			glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(-135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			newDir = rot * newDir;
			avatar->setDir(newDir);
			avatar->moveToDir(velocity * 0.707); // Cuidado con la velocidad en diagonal
			avatar->setMoving(true);
                } else {
			if (keys[GLFW_KEY_W]) {
				avatar->setDir(glm::vec3(front.x, 0.0f, front.z));
				avatar->moveToDir(velocity);
				avatar->setMoving(true);
			} if (keys[GLFW_KEY_S]) {
				avatar->setDir(glm::vec3(-front.x, 0.0f, -front.z));
				avatar->moveToDir(velocity);
				avatar->setMoving(true);
			} if (keys[GLFW_KEY_A]) {
				glm::vec4 newDir = glm::vec4(front.x, 0.0f, front.z, 0.0f);
				glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				newDir = rot * newDir;
				avatar->setDir(newDir);
				avatar->moveToDir(velocity);
				avatar->setMoving(true);
			} if (keys[GLFW_KEY_D]) {
				glm::vec4 newDir = glm::vec4(front.x, 0.0f, front.z, 0.0f);
				glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				newDir = rot * newDir;
				avatar->setDir(newDir);
				avatar->moveToDir(velocity);
				avatar->setMoving(true);
			}
		}
                
		return;
	}

	if (keys[GLFW_KEY_W]) {
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S]) {
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A]) {
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D]) {
		position += right * velocity;
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}

	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}


glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));

        if (estado == THIRD_PERSON_CAMERA) {
		position = avatar->getPos() - distanceToAvatar * front;
		position += glm::vec3(0.0f, 3.0f, 0.0f);
	}
}

void Camera::updateRig(GLfloat dt) {
	cameraRig.update(dt);
	position = cameraRig.getPos();
	front = glm::normalize(cameraRig.getDiff());
}

void Camera::setAvatar(Avatar *newAvatar) {
	avatar = newAvatar;
	lookAtAvatar = true;
}

void Camera::setEstado(CameraEstado newEstado) {
	if (newEstado == THIRD_PERSON_CAMERA && avatar == nullptr) {
		return;
	}
	estado = newEstado;
}

void Camera::goToNextLocation() {
	setEstado(FREE_CAMERA);
	locationIndex = (locationIndex + 1) % locations.size();
	position = locations[locationIndex].first;
	pitch = locations[locationIndex].second.x;
	yaw = locations[locationIndex].second.y;
	update();
}

void Camera::startRig() {
	cameraRig.setT(0.0f);
	setEstado(RIGGING_CAMERA);
}

void Camera::addLocation(glm::vec3 pos, glm::vec2 py) {
	locations.push_back({pos, {py.x, py.y}});
}

Camera::~Camera()
{
}
