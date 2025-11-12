#pragma once

#include "MovingEntity.hpp"
#include "Avatar.hpp"
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>
#include <utility>

enum CameraEstado {THIRD_PERSON_CAMERA, FREE_CAMERA, RIGGING_CAMERA};

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);
	void updateRig(GLfloat dt);
        void setEstado(CameraEstado newEstado);
	void moveToNextLocation();
	void startRig();
	void goToNextLocation();
	void addLocation(glm::vec3 pos, glm::vec2 dir);

	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();
	CameraEstado getEstado() { return estado; };
	glm::mat4 calculateViewMatrix();
	void setAvatar(Avatar *avatar);

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
                void setT(GLfloat newT) {
			t = newT;
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
	Avatar *avatar;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

        CameraRig cameraRig;

        CameraEstado estado;

        bool lookAtAvatar;
	GLfloat distanceToAvatar;

        int locationIndex;
        std::vector<std::pair<glm::vec3, glm::vec2>> locations;

	void update();
};

