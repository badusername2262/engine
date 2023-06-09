#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <cstring>
#include <glm/glm.hpp>

namespace Graphics {
	
	struct Camera
	{
	public:
		float elements[4 * 4];

		Camera();
		Camera(float diagonal);

		static Camera identity();

		static Camera Orthographic(float left, float right, float bottom, float top, float near, float far);

		static Camera translation(const glm::vec3& translation);
		static Camera rotation(float angle, const glm::vec3& axis);
		static Camera scale(const glm::vec3& scale);
	};
	
}

#endif // CAMERA_H