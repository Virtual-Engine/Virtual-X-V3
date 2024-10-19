#include "common.hpp"


namespace VX
{
	inline bool IsKeyPressed(std::uint16_t key)
	{
		if (GetForegroundWindow())
		{
			if (GetAsyncKeyState(key) & 0x8000)
			{
				return true;
			}
		}

		return false;
	}
	Vector3 RotationToDirectionV3(Vector3 rot) {
		Vector3 dir;
		float radiansZ = rot.z * 0.0174532924f;
		float radiansX = rot.x * 0.0174532924f;
		float num = abs((float)cos((double)radiansX));
		dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
		dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
		dir.z = (float)sin((double)radiansX);
		return dir;
	}

	Vector3 AddV3(Vector3 vectorA, Vector3 vectorB) {
		Vector3 result;
		result.x = vectorA.x;
		result.y = vectorA.y;
		result.z = vectorA.z;
		result.x += vectorB.x;
		result.y += vectorB.y;
		result.z += vectorB.z;
		return result;
	}

	Vector3 MultiplyV3(Vector3 vector, float x) {
		Vector3 result;
		result.x = vector.x;
		result.y = vector.y;
		result.z = vector.z;
		result.x *= x;
		result.y *= x;
		result.z *= x;
		return result;
	}

	inline float GetDistanceFloat(Vector3 pointA, Vector3 pointB) {
		float a_x = pointA.x;
		float a_y = pointA.y;
		float a_z = pointA.z;
		float b_x = pointB.x;
		float b_y = pointB.y;
		float b_z = pointB.z;
		double x_ba = (double)(b_x - a_x);
		double y_ba = (double)(b_y - a_y);
		double z_ba = (double)(b_z - a_z);
		double y_2 = y_ba * y_ba;
		double x_2 = x_ba * x_ba;
		double sum_2 = y_2 + x_2;
		return(float)sqrt(sum_2 + z_ba);
	}

	float GetVectorLengthFloat(Vector3* vector) {
		double x = (double)vector->x;
		double y = (double)vector->y;
		double z = (double)vector->z;
		return(float)sqrt(x * x + y * y + z * z);
	}
}