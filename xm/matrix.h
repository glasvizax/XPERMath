#pragma once

#include <cstring>
#include "vector.h"
#include "math_helpers.h"

template <typename... Ts>
using mul_result_t = decltype((std::declval<Ts>() * ...));

namespace xm
{
	template <uint8_t N, typename T>
	struct matrix;

	template <typename T>
	struct matrix<2, T>
	{
		matrix()
		{
			memset(&this->a.x, static_cast<int>(T(0)), 4 * sizeof(T));
		}
		template <typename K>
		explicit matrix(K a)
		{
			this->a.x = a;
			this->a.y = 0.0;
			this->b.x = 0.0;
			this->b.y = a;
		}

		template <typename K>
		explicit matrix(matrix<3, K> other)
		{
			this->a = vector<2, T>(other.a);
			this->b = vector<2, T>(other.b);
		}

		template <typename K>
		explicit matrix(matrix<4, K> other)
		{
			this->a = vector<2, T>(other.a);
			this->b = vector<2, T>(other.b);
		}

		template <typename K>
		explicit matrix(vector<2, K> a)
		{
			this->a = vector<2, T>(a.x, 0.0);
			this->b = vector<2, T>(0.0, a.y);
		}

		template <typename K, typename W>
		matrix(vector<2, K> a, vector<2, W> b)
		{
			this->a = vector<2, T>(a);
			this->b = vector<2, T>(b);
		}

		vector<2, T>& operator[](uint8_t i)
		{
			return *(&a + i);
		}

		const vector<2, T>& operator[](uint8_t i) const
		{
			return *(&a + i);
		}

		vector<2, T> a;
		vector<2, T> b;
	};

	template <typename T>
	struct matrix<3, T>
	{
		matrix()
		{
			memset(&this->a.x, static_cast<int>(T(0)), 9 * sizeof(T));
		}

		template <typename K>
		explicit matrix(K a)
		{
			this->a.x = a;
			this->a.y = 0.0;
			this->a.z = 0.0;

			this->b.x = 0.0;
			this->b.y = a;
			this->b.z = 0.0;

			this->c.x = 0.0;
			this->c.y = 0.0;
			this->c.z = a;
		}

		template <typename K>
		explicit matrix(vector<3, K> a)
		{
			this->a = vector<3, T>(a.x, 0.0, 0.0);
			this->b = vector<3, T>(0.0, a.y, 0.0);
			this->c = vector<3, T>(0.0, 0.0, a.z);
		}

		template <typename K>
		explicit matrix(matrix<2, K> other)
		{
			this->a = vector<3, T>(other.a, 0.0f);
			this->b = vector<3, T>(other.b, 0.0f);
			this->c = vector<3, T>(0.0f);
		}

		template <typename K>
		explicit matrix(matrix<4, K> other)
		{
			this->a = vector<3, T>(other.a);
			this->b = vector<3, T>(other.b);
			this->c = vector<3, T>(other.c);
		}

		template <typename K, typename W, typename U>
		matrix(vector<3, K> a, vector<3, W> b, vector<3, U> c)
		{
			this->a = xm::vector<3, T>(a);
			this->b = b;
			this->c = c;
		}

		vector<3, T>& operator[](uint8_t i)
		{
			return *(&a + i);
		}

		const vector<3, T>& operator[](uint8_t i) const
		{
			return *(&a + i);
		}

		vector<3, T> a;
		vector<3, T> b;
		vector<3, T> c;
	};

	template <typename T>
	struct matrix<4, T>
	{
		matrix()
		{
			memset(&this->a.x, static_cast<int>(T(0)), 16 * sizeof(T));
		}

		template <typename K>
		matrix(K a)
		{
			this->a.x = a;
			this->a.y = 0.0;
			this->a.z = 0.0;
			this->a.w = 0.0;

			this->b.x = 0.0;
			this->b.y = a;
			this->b.z = 0.0;
			this->b.w = 0.0;

			this->c.x = 0.0;
			this->c.y = 0.0;
			this->c.z = a;
			this->c.w = 0.0;

			this->d.x = 0.0;
			this->d.y = 0.0;
			this->d.z = 0.0;
			this->d.w = a;
		}

		template <typename K>
		matrix(vector<3, K> a)
		{
			this->a = vector<4, T>(a.x, 0.0, 0.0, 0.0);
			this->b = vector<4, T>(0.0, a.y, 0.0, 0.0);
			this->c = vector<4, T>(0.0, 0.0, a.z, 0.0);
			this->d = vector<4, T>(0.0, 0.0, 0.0, 1.0);
		}
		template <typename K>
		matrix(vector<4, K> a)
		{
			this->a = vector<4, T>(a.x, 0.0, 0.0, 0.0);
			this->b = vector<4, T>(0.0, a.y, 0.0, 0.0);
			this->c = vector<4, T>(0.0, 0.0, a.z, 0.0);
			this->d = vector<4, T>(0.0, 0.0, 0.0, a.w);
		}

		template <typename K, typename W, typename U, typename H>
		matrix(const vector<4, K>& a, const vector<4, W>& b, const vector<4, U>& c, const vector<4, H>& d)
		{
			this->a = xm::vector<4, T>(a);
			this->b = xm::vector<4, T>(b);
			this->c = xm::vector<4, T>(c);
			this->d = xm::vector<4, T>(d);
		}

		template <typename K>
		explicit matrix(matrix<2, K> other)
		{
			this->a = vector<4, T>(other.a, 0.0f, 0.0f);
			this->b = vector<4, T>(other.b, 0.0f, 0.0f);
			this->c = vector<4, T>(0.0f);
			this->d = vector<4, T>(0.0f);
		}

		template <typename K>
		explicit matrix(matrix<3, K> other)
		{
			this->a = vector<4, T>(other.a, 0.0f);
			this->b = vector<4, T>(other.b, 0.0f);
			this->c = vector<4, T>(other.c, 0.0f);
			this->d = vector<4, T>(0.0f, 0.0f, 0.0f, 1.0f);
		}

		template <typename K>
		explicit matrix(matrix<4, K> other)
		{
			this->a = vector<4, T>(other.a);
			this->b = vector<4, T>(other.b);
			this->c = vector<4, T>(other.c);
		}

		vector<4, T> a;
		vector<4, T> b;
		vector<4, T> c;
		vector<4, T> d;

		vector<4, T>& operator[](uint8_t i)
		{
			return *(&a + i);
		}

		const vector<4, T>& operator[](uint8_t i) const
		{
			return *(&a + i);
		}
	};

	template <uint8_t N, typename T, typename K>
	auto operator*(const matrix<N, T>& a, const matrix<N, K>& b)
	{
		matrix<N, mul_result_t<T, K>> res;

		for (uint8_t i = 0; i < N; ++i)
		{
			for (uint8_t j = 0; j < N; ++j)
			{
				for (uint8_t k = 0; k < N; ++k)
				{
					res[i][j] += a[i][k] * b[k][j];
				}
			}
		}

		return res;
	}

	template <uint8_t N, typename T, typename K>
#ifdef XM_VECTOR_ROW
	auto operator*(vector<N, K> b, const matrix<N, T>& a)
#else
	auto operator*(const matrix<N, T>& a, vector<N, K> b)
#endif
	{
		vector<N, mul_result_t<T, K>> res{};

		for (uint8_t i = 0; i < N; ++i)
		{
			for (uint8_t j = 0; j < N; ++j)
			{
				res[i] += a[i][j] * b[j];
			}
		}

		return res;
	}
#ifdef XM_VECTOR_ROW
	template <uint8_t N, typename T, typename K>
	auto operator*(const matrix<N, T>& a, vector<N, K> b) = delete;

#else
	template <uint8_t N, typename T, typename K>
	auto operator*(vector<N, K> b, const matrix<N, T>& a) = delete;

#endif

	template <uint8_t N, typename T, typename K>
	void operator*=(matrix<N, T>& a, const matrix<N, K>& b)
	{
		a = a * b;
	}

	template <uint8_t N, typename T>
	T determinant(matrix<N, T> m)
	{
		if constexpr (N == 2)
		{
			return m.a.x * m.b.y - m.a.y * m.b.x;
		}

		if constexpr (N == 3)
		{
			matrix<2, T> minor00{ { m.b.y, m.b.z }, { m.c.y, m.c.z } };
			matrix<2, T> minor10{ { m.b.x, m.b.z }, { m.c.x, m.c.z } };
			matrix<2, T> minor20{ { m.b.x, m.b.y }, { m.c.x, m.c.y } };

			T det00 = determinant(minor00);
			T det10 = determinant(minor10);
			T det20 = determinant(minor20);

			return m.a.x * det00 - m.a.y * det10 + m.a.z * det20;
		}

		if constexpr (N == 4)
		{
			matrix<3, T> minor00{ { m.b.y, m.b.z, m.b.w },
				{ m.c.y, m.c.z, m.c.w },
				{ m.d.y, m.d.z, m.d.w } };
			matrix<3, T> minor10{ { m.b.x, m.b.z, m.b.w },
				{ m.c.x, m.c.z, m.c.w },
				{ m.d.x, m.d.z, m.d.w } };
			matrix<3, T> minor20{ { m.b.x, m.b.y, m.b.w },
				{ m.c.x, m.c.y, m.c.w },
				{ m.d.x, m.d.y, m.d.w } };
			matrix<3, T> minor30{ { m.b.x, m.b.y, m.b.z },
				{ m.c.x, m.c.y, m.c.z },
				{ m.d.x, m.d.y, m.d.z } };

			T det00 = determinant(minor00);
			T det10 = determinant(minor10);
			T det20 = determinant(minor20);
			T det30 = determinant(minor30);

			return m.a.x * det00
				- m.a.y * det10
				+ m.a.z * det20
				- m.a.w * det30;
		}
	}

	template <uint8_t N, typename T>
	inline void swap(matrix<N, T>& a, matrix<N, T>& b)
	{
		matrix<N, T> tmp = a;
		a = b;
		b = tmp;
	}

	template <typename T>
	matrix<3, T> inverse(const matrix<3, T>& m)
	{
		T det_recip = static_cast<T>(1) / (m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) - m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2]) + m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]));

		matrix<3, T> inverse;
		inverse[0][0] = +(m[1][1] * m[2][2] - m[2][1] * m[1][2]) * det_recip;
		inverse[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * det_recip;
		inverse[2][0] = +(m[1][0] * m[2][1] - m[2][0] * m[1][1]) * det_recip;
		inverse[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * det_recip;
		inverse[1][1] = +(m[0][0] * m[2][2] - m[2][0] * m[0][2]) * det_recip;
		inverse[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * det_recip;
		inverse[0][2] = +(m[0][1] * m[1][2] - m[1][1] * m[0][2]) * det_recip;
		inverse[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * det_recip;
		inverse[2][2] = +(m[0][0] * m[1][1] - m[1][0] * m[0][1]) * det_recip;

		return inverse;
	}

	template <typename T>
	matrix<4, T> inverse(const matrix<4, T>& m)
	{
		T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		matrix<4, T> Inverse;
		Inverse[0][0] = (m[1][1] * Coef00 - m[1][2] * Coef04 + m[1][3] * Coef08);
		Inverse[0][1] = -(m[0][1] * Coef00 - m[0][2] * Coef04 + m[0][3] * Coef08);
		Inverse[0][2] = (m[0][1] * Coef02 - m[0][2] * Coef06 + m[0][3] * Coef10);
		Inverse[0][3] = -(m[0][1] * Coef03 - m[0][2] * Coef07 + m[0][3] * Coef11);

		Inverse[1][0] = -(m[1][0] * Coef00 - m[1][2] * Coef12 + m[1][3] * Coef16);
		Inverse[1][1] = (m[0][0] * Coef00 - m[0][2] * Coef12 + m[0][3] * Coef16);
		Inverse[1][2] = -(m[0][0] * Coef02 - m[0][2] * Coef14 + m[0][3] * Coef18);
		Inverse[1][3] = (m[0][0] * Coef03 - m[0][2] * Coef15 + m[0][3] * Coef19);

		Inverse[2][0] = (m[1][0] * Coef04 - m[1][1] * Coef12 + m[1][3] * Coef20);
		Inverse[2][1] = -(m[0][0] * Coef04 - m[0][1] * Coef12 + m[0][3] * Coef20);
		Inverse[2][2] = (m[0][0] * Coef06 - m[0][1] * Coef14 + m[0][3] * Coef22);
		Inverse[2][3] = -(m[0][0] * Coef07 - m[0][1] * Coef15 + m[0][3] * Coef23);

		Inverse[3][0] = -(m[1][0] * Coef08 - m[1][1] * Coef16 + m[1][2] * Coef20);
		Inverse[3][1] = (m[0][0] * Coef08 - m[0][1] * Coef16 + m[0][2] * Coef20);
		Inverse[3][2] = -(m[0][0] * Coef10 - m[0][1] * Coef18 + m[0][2] * Coef22);
		Inverse[3][3] = (m[0][0] * Coef11 - m[0][1] * Coef19 + m[0][2] * Coef23);

		T Det = m[0][0] * Inverse[0][0] + m[0][1] * Inverse[1][0] + m[0][2] * Inverse[2][0] + m[0][3] * Inverse[3][0];
		T OneOverDeterminant = static_cast<T>(1) / Det;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				Inverse[i][j] *= OneOverDeterminant;
			}
		}

		return Inverse;
	}

} // namespace xm