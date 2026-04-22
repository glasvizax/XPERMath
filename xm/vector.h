#pragma once

#include <type_traits>
#include "assert.h"
#include <cmath>

namespace xm
{
	template <uint8_t N, typename T>
	struct vector;

	template <typename T>
	struct vector<2, T>
	{
		static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>);

		template <typename K>
		explicit vector(vector<3, K> vec)
		{
			this->x = vec.x;
			this->y = vec.y;
		}

		template <typename K>
		explicit vector(vector<4, K> vec)
		{
			this->x = vec.x;
			this->y = vec.y;
		}

		template <typename K, typename W>
		vector(K x, W y)
		{
			this->x = x;
			this->y = y;
		}

		template <typename K>
		explicit vector(K a)
		{
			this->x = a;
			this->y = a;
		}

		vector()
		{
			this->x = 0;
			this->y = 0;
		}

		T& operator[](uint8_t i)
		{
			return *(&x + i);
		}

		T operator[](uint8_t i) const
		{
			return *(&x + i);
		}

		union
		{
			struct
			{
				T x, y;
			};
			struct
			{
				T r, g;
			};
			struct
			{
				T u, v;
			};
			struct
			{
				T width, height;
			};
		};
	};

	template <typename T>
	struct vector<3, T>
	{
		static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>);

		template <typename K, typename W>
		vector(vector<2, W> xy, K z)
		{
			this->x = xy.x;
			this->y = xy.y;
			this->z = z;
		}

		template <typename K, typename W>
		vector(K x, vector<2, W> yz)
		{
			this->x = x;
			this->y = yz.x;
			this->z = yz.y;
		}

		template <typename K>
		explicit vector(vector<4, K> vec)
		{
			this->x = vec.x;
			this->y = vec.y;
			this->z = vec.z;
		}

		template <typename K, typename W, typename U>
		vector(K x, W y, U z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		template <typename K>
		explicit vector(K a)
		{
			this->x = a;
			this->y = a;
			this->z = a;
		}

		vector()
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}

		T& operator[](uint8_t i)
		{
			return *(&x + i);
		}

		T operator[](uint8_t i) const
		{
			return *(&x + i);
		}

		union
		{
			struct
			{
				T x, y, z;
			};
			struct
			{
				T r, g, b;
			};
			struct
			{
				T pitch, yaw, roll;
			};
		};
	};

	template <typename T>
	struct vector<4, T>
	{
		static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>);

		template <typename K, typename W>
		vector(vector<2, K> xy, vector<2, W> zw)
		{
			this->x = xy.x;
			this->y = xy.y;
			this->z = zw.x;
			this->w = zw.y;
		}

		template <typename K, typename W>
		vector(vector<3, K> xyz, W w)
		{
			this->x = xyz.x;
			this->y = xyz.y;
			this->z = xyz.z;
			this->w = w;
		}

		template <typename K, typename W>
		vector(K x, vector<3, W> yzw)
		{
			this->x = x;
			this->y = yzw.x;
			this->z = yzw.y;
			this->w = yzw.z;
		}

		template <typename K, typename W, typename U, typename N>
		vector(K x, W y, U z, N w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		template <typename K>
		explicit vector(K a)
		{
			this->x = a;
			this->y = a;
			this->z = a;
			this->w = a;
		}

		vector()
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
			this->w = 0;
		}

		T& operator[](uint8_t i)
		{
			return *(&x + i);
		}

		T operator[](uint8_t i) const
		{
			return *(&x + i);
		}

		union
		{
			struct
			{
				T x, y, z, w;
			};
			struct
			{
				T r, g, b, a;
			};
		};
	};

	template <uint8_t N, typename T, typename K>
	vector<N, T> operator*(vector<N, T> a, K v)
	{
		vector<N, T> res;
		for (uint8_t i = 0; i < N; ++i)
		{
			res[i] = a[i] * v;
		}
		return res;
	}

	template <uint8_t N, typename T, typename K>
	inline vector<N, T> operator*(K v, vector<N, T> a)
	{
		return operator*(a, v);
	}

	template <uint8_t N, typename T, typename K>
	vector<N, T>& operator*=(vector<N, T>& a, K v)
	{
		for (uint8_t i = 0; i < N; ++i)
		{
			a[i] *= v;
		}
		return a;
	}

	template <uint8_t N, typename T, typename K>
	vector<N, T>& operator/=(vector<N, T>& a, K v)
	{
		for (uint8_t i = 0; i < N; ++i)
			a[i] /= v;
		return a;
	}

	template <uint8_t N, typename T, typename K>
	vector<N, T> operator/(vector<N, T> a, K v)
	{
		vector<N, T> res;
		for (uint8_t i = 0; i < N; ++i)
		{
			res[i] = a[i] / v;
		}
		return res;
	}

	template <uint8_t N, typename T, typename K>
	vector<N, T> operator+(vector<N, T> a, vector<N, K> b)
	{
		vector<N, T> res;
		for (uint8_t i = 0; i < N; ++i)
		{
			res[i] = a[i] + b[i];
		}
		return res;
	}

	template <uint8_t N, typename T>
	vector<N, T> operator-(vector<N, T> a)
	{
		for (uint8_t i = 0; i < N; ++i)
		{
			a[i] = -a[i];
		}
		return a;
	}

	template <uint8_t N, typename T, typename K>
	inline vector<N, T> operator-(vector<N, T> a, vector<N, K> b)
	{
		return operator+(a, -b);
	}

	template <uint8_t N, typename T, typename K>
	inline vector<N, T>& operator+=(vector<N, T>& a, vector<N, K> b)
	{
		for (uint8_t i = 0; i < N; ++i)
		{
			a[i] += b[i];
		}
		return a;
	}

	template <uint8_t N, typename T, typename K>
	inline vector<N, T>& operator-=(vector<N, T>& a, vector<N, K> b)
	{
		for (uint8_t i = 0; i < N; ++i)
		{
			a[i] -= b[i];
		}
		return a;
	}

	template <uint8_t N, typename T, typename K>
	T dot(vector<N, T> a, vector<N, K> b)
	{
		T res = T(0.0);

		for (uint8_t i = 0; i < N; ++i)
		{
			res += a[i] * b[i];
		}

		return res;
	}

	template <typename T, typename K>
	vector<3, T> crossRH(vector<3, T> a, vector<3, K> b)
	{
		vector<3, T> res;

		res.x = a.y * b.z - a.z * b.y;
		res.y = a.z * b.x - a.x * b.z;
		res.z = a.x * b.y - a.y * b.x;

		return res;
	}

	template <typename T, typename K>
	inline vector<3, T> crossLH(vector<3, T> a, vector<3, K> b)
	{
		return -crossRH(a, b);
	}

	template <typename T, typename K>
	inline vector<3, T> cross(vector<3, T> a, vector<3, K> b)
	{
#ifdef XM_LEFT_HANDED
		return crossLH(a, b);
#else
		return crossRH(a, b);
#endif
	}

	template <typename T, typename K>
	T cross2D(vector<2, T> a, vector<2, K> b)
	{
		return a.x * b.y - a.y * b.x;
	}

	template <uint8_t N, typename T>
	inline T sumOfSquares(vector<N, T> a)
	{
		T sum = 0.0;
		for (uint8_t i = 0; i < N; ++i)
		{
			sum += a[i] * a[i];
		}
		return sum;
	}

	template <uint8_t N, typename T>
	inline vector<N, T> normalize(vector<N, T> a)
	{
		return a / sqrt(sumOfSquares(a));
	}

	template <uint8_t N, typename T>
	inline void swap(vector<N, T>& a, vector<N, T>& b) 
	{
		vector<N, T> tmp = a;
		a = b;
		b = tmp;
	}

} // namespace xm
