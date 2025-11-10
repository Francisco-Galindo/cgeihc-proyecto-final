#pragma once

#include "MovingEntity.hpp"
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);
	void updateRig(GLfloat dt);

	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();
	glm::mat4 calculateViewMatrix();

	~Camera();

private:
	class CameraRig : public MovingEntity {
	public:
		CameraRig() {}
		CameraRig(glm::vec3 orig, std::function<glm::vec3(GLfloat)> callback)
		: MovingEntity(orig, callback) {
			return;
		}
                void updateAnimation(GLfloat dt) {
			return;
		}
                void render(GLint uniformModel) {
			return;
		}
		// ~Beastie() = default;
	private:
		GLfloat roll;
	};

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

        CameraRig cameraRig;

	void update();
};

