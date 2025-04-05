// OpenGL Learning Project camera header

#ifndef CAMERA_H
#define CAMERA_H

// Includes
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Camera movement enumerator
enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENS = 0.07f;
const float FOV = 75.0f;

// Camera class
class Camera {
public:
	// Camera attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// Euler angles
	float Yaw;
	float Pitch;

	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Fov;

	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENS), Fov(FOV) {
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	// Constructor with scalars
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENS), Fov(FOV) {
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	// Returns view matrix from Euler angles and the LookAt matrix
	glm::mat4 getViewMatrix() {
		return glm::lookAt(Position, Position + Front, Up);
	}

	// Process keyboard input
	void processKeyboard(CameraMovement direction, float deltaTime, float sprintMult) {
		float velocity = 5.0f * deltaTime * sprintMult;
		float xzdirect = glm::length(glm::vec3(Front.x, 0.0f, Front.z));
		if (direction == FORWARD) {
			Position.x += velocity * (Front.x / xzdirect);
			Position.z += velocity * (Front.z / xzdirect);
		}
		if (direction == BACKWARD) {
			Position.x -= velocity * (Front.x / xzdirect);
			Position.z -= velocity * (Front.z / xzdirect);
		}
		if (direction == LEFT) {
			Position -= velocity * Right;
		}
		if (direction == RIGHT) {
			Position += velocity * Right;
		}
		if (direction == UP) {
			Position += velocity * Up;
		}
		if (direction == DOWN) {
			Position -= velocity * Up;
		}
	}

	// Process mouse input
	void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch -= yoffset;

		if (constrainPitch) {
			if (Pitch > 89.0f) {
				Pitch = 89.0f;
			}
			if (Pitch < -89.0f) {
				Pitch = -89.0f;
			}
		}

		updateCameraVectors();
	}

	// Process scroll input
	void processMouseScroll(float yoffset) {
		Fov -= static_cast<float>(yoffset) * 5.0f;
		if (Fov < 1.0f) {
			Fov = 1.0f;
		}
		if (Fov > 115.0f) {
			Fov = 115.0f;
		}
	}

private:
	// Update the camera vectors based on Euler angles
	void updateCameraVectors() {
		glm::vec3 front;

		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

		Front = glm::normalize(front);
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
};

#endif