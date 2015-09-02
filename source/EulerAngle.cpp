#include "EulerAngle.h"
#include <stdio.h>

EulerAngle::EulerAngle(float yaw, float pitch, float roll) {
	this->yaw = yaw;
	this->pitch = pitch;
	this->roll = roll;
}

EulerAngle::EulerAngle() {
	this->pitch = 0;
	this->yaw = 0;
	this->roll = 0;
}

EulerAngle::~EulerAngle()
{
}

//Converts the euler angles into a direction vector
glm::vec3 EulerAngle::toVector() {

	//Convert the yaw and pitch into radians
	yaw = (yaw * PI) / 180;
	pitch = (pitch * PI) / 180;

	glm::vec3 result;

	//Calculate the vector components from the Euler angles
	result.x = sin(yaw) * cos(pitch);
	result.y = sin(pitch);
	result.z = -cos(yaw) * cos(pitch);

	return result;
}

//Converts a vector back into its euler angles
void EulerAngle::toAngles(glm::vec3 direction) {

	float pitchTemp = 0;
	float yawTemp = 0;

	//Normalize the vector
	direction = glm::normalize(direction);

	//Calculate the yaw and the pitch from the direction vector
	yawTemp = atan2(-direction.x, direction.z);
	pitchTemp = atan2(direction.y, sqrt(fabs(direction.z * direction.x) + fabs(direction.z * direction.z)));

	//Convert back into degrees
	pitchTemp = (pitchTemp * 180) / PI;
	yawTemp = (yawTemp * 180) / PI;

	this->pitch = -pitchTemp;
	this->yaw = yawTemp;

	//yaw += 90;

}

//Stops the angles from extending in unwanted ways
void EulerAngle::constrain() {
	
	//Stop the pitch from moving past 90 degrees
	if (pitch > 90) {
		pitch = 90;
	}
	else if (pitch < -90) {
		pitch = -90;
	}

	//Stop the yaw from increasing indefinately
	while (yaw > 360) {
		yaw -= 360;
	}
	while (yaw < -360) {
		yaw += 360;
	}
}

/*
GETTERS AND SETTERS
*/

//Getters
//Return the pitch
float EulerAngle::getPitch() {
	return this->pitch;
}

//Return the yaw
float EulerAngle::getYaw() {
	return this->yaw;
}

//Return the roll
float EulerAngle::getRoll() {
	return this->roll;
}

//Setters
//Set the pitch
void EulerAngle::setPitch(float pitch) {
	this->pitch = pitch;
}

//Set the yaw
void EulerAngle::setYaw(float yaw) {
	this->yaw = yaw;
}

//Set the roll
void EulerAngle::setRoll(float roll) {
	this->roll = roll;
}