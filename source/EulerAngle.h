#ifndef EULERANGLE_H
#define EULERANGLE_H

#include <glm.hpp>
#include <euler_angles.hpp>
#include <matrix_transform.hpp>
#include <rotate_vector.hpp>

class EulerAngle
{
	public:
		EulerAngle(float, float, float);
		EulerAngle();
		~EulerAngle();

		glm::vec3 toVector();
		void toAngles(glm::vec3 direction);
		void constrain();
		const float PI = 3.14159;

		float getPitch();
		float getYaw();
		float getRoll();
		void setPitch(float);
		void setYaw(float);
		void setRoll(float);

	private:
		float pitch;
		float yaw;
		float roll;
};

#endif