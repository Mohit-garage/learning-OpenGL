#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Directions
{
	Forward,
	Backward,
	Right,
	Left,
	Up,
	Down
};

float YAW			= -90.0f;
float PITCH			= 0.0f;
float SPEED			= 2.5f;
float SENSTIVITY	= 0.01f;
float ZOOM			= 45.0f;

class camera {
public:
	glm::vec3 cameraPosition;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
	glm::vec3 WorldUp;
	//Euler Angles
	float Yaw, Pitch;
	//Camera Options
	float MovementSpeed, MouseSenstivity;
	float Zoom;

	camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), MouseSenstivity(SENSTIVITY), MovementSpeed(SPEED), Zoom(ZOOM)
	{
		cameraPosition = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;

		UpdateCameraParameters();
	}
	glm::mat4 getViewMatrix()
	{
		return view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, WorldUp);
	}void processKeyboardInput(Directions direction, float dt)
	{
		float velocity = MovementSpeed * dt;
		if (direction == Forward)
			cameraPosition += cameraFront * velocity;
		if (direction == Backward)
			cameraPosition -= cameraFront * velocity;
		if (direction == Right)
			cameraPosition -= cameraRight * velocity;
		if (direction == Left)
			cameraPosition += cameraRight * velocity;
		if (direction == Up)
			cameraPosition += cameraUp * velocity;
		if (direction == Down)
			cameraPosition -= cameraUp * velocity;

	}
	void processMouseInput(float xoffset, float yoffset, GLboolean constrainRotation = GL_TRUE)
	{
		Yaw += xoffset * MouseSenstivity;
		Pitch -= yoffset * MouseSenstivity;

		if (constrainRotation)
		{
			if (Pitch < -89.0f)
				Pitch = -89.0f;
			if (Pitch > 89.0f)
				Pitch = 89.0f;

		}

		UpdateCameraParameters();
	}
	void processMouseScrollInput(float yoffset)
	{
		Zoom -= yoffset;

		if (Zoom < 0.1f)
			Zoom = 0.1f;
		if (Zoom > 60)
			Zoom = 60.0f;

	}
private:
	void UpdateCameraParameters()
	{
		cameraFront.x = cos(Pitch) * cos(Yaw);
		cameraFront.y = sin(Pitch);
		cameraFront.z = cos(Pitch) * sin(Yaw);
		cameraFront = glm::normalize(cameraFront);

		cameraRight = glm::normalize(glm::cross(WorldUp, cameraFront));
		cameraUp = glm::normalize(glm::cross(cameraFront, cameraRight));
	}
	
	glm::mat4 view;
};

#endif