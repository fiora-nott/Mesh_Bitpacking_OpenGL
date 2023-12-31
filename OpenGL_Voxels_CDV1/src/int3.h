#pragma once

struct int3 {
	int x, y, z;

	inline int3(void) {
		x = 0;
		y = 0;
		z = 0;
	}
	inline int3(const int X, const int Y, const int Z) 
	{
		x = X;
		y = Y;
		z = Z;
	}

	inline int3 operator + (const int3& A) const
	{
		return int3(x + A.x, y + A.y, z + A.z);
	}

	inline int3 operator + (const int A) const
	{
		return int3(x + A, y + A, z + A);
	}

	inline int3 operator - (const int3& A) const
	{
		return int3(x - A.x, y - A.y, z - A.z);
	}
	inline int3 operator - (const int A) const
	{
		return int3(x - A, y - A, z - A);
	}

	inline int3 operator * (const int A) const
	{
		return int3(x * A, y * A, z * A);
	}

	/*std::ostream& operator<<(std::ostream& stream, const int3& A)
	{
		return stream << "(x:" << A.x << ", y:" << A.y << ", z:" << A.z;
	}*/
};

