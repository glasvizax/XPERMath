#pragma once

#include <cmath>
#include <tuple>

#include "vector.h"
#include "matrix.h"
#include "math_helpers.h"
#include "misc_helpers.h"

#pragma push_macro("near")
#pragma push_macro("far")
#undef near
#undef far

namespace xm
{

#define ASSERT_FLOAT(T) static_assert(std::is_floating_point_v<T>, "T must be a floating-point type (float, double)")

	template <uint8_t N, typename T>
	matrix<N, T> eulRotZ(T radians)
	{
		static_assert(N == 3 || N == 4, "N must be 3 or 4");
		ASSERT_FLOAT(T);

		T cos_theta = std::cos(radians);
		T sin_theta = std::sin(radians);

		if constexpr (N == 4)
		{
			vector<4, T> a(cos_theta, sin_theta, T(0), T(0));
			vector<4, T> b(-sin_theta, cos_theta, T(0), T(0));
			vector<4, T> c(T(0), T(0), T(1), T(0));
			vector<4, T> d(T(0), T(0), T(0), T(1));
			return matrix<4, T>(a, b, c, d);
		}
		else
		{
			vector<3, T> a(cos_theta, sin_theta, T(0));
			vector<3, T> b(-sin_theta, cos_theta, T(0));
			vector<3, T> c(T(0), T(0), T(1));
			return matrix<3, T>(a, b, c);
		}
	}

	template <uint8_t N, typename T>
	matrix<N, T> eulRotX(T radians)
	{
		static_assert(N == 3 || N == 4, "N must be 3 or 4");
		ASSERT_FLOAT(T);

		T cos_theta = std::cos(radians);
		T sin_theta = std::sin(radians);

		if constexpr (N == 4)
		{
			vector<4, T> a(T(1), T(0), T(0), T(0));
			vector<4, T> b(T(0), cos_theta, sin_theta, T(0));
			vector<4, T> c(T(0), -sin_theta, cos_theta, T(0));
			vector<4, T> d(T(0), T(0), T(0), T(1));
			return matrix<4, T>(a, b, c, d);
		}
		else
		{
			vector<3, T> a(T(1), T(0), T(0));
			vector<3, T> b(T(0), cos_theta, sin_theta);
			vector<3, T> c(T(0), -sin_theta, cos_theta);
			return matrix<3, T>(a, b, c);
		}
	}

	template <uint8_t N, typename T>
	matrix<N, T> eulRotY(T radians)
	{
		static_assert(N == 3 || N == 4, "N must be 3 or 4");
		ASSERT_FLOAT(T);

		T cos_theta = std::cos(radians);
		T sin_theta = std::sin(radians);

		if constexpr (N == 4)
		{
			vector<4, T> a(cos_theta, T(0), -sin_theta, T(0));
			vector<4, T> b(T(0), T(1), T(0), T(0));
			vector<4, T> c(sin_theta, T(0), cos_theta, T(0));
			vector<4, T> d(T(0), T(0), T(0), T(1));
			return matrix<4, T>(a, b, c, d);
		}
		else
		{
			vector<3, T> a(cos_theta, T(0), -sin_theta);
			vector<3, T> b(T(0), T(1), T(0));
			vector<3, T> c(sin_theta, T(0), cos_theta);
			return matrix<3, T>(a, b, c);
		}
	}

	// axis must be a unit vector
	template <uint8_t N, typename T>
	matrix<N, T> rodriguesMatrix(const vector<3, T>& axis, T radians)
	{
		static_assert(N == 3 || N == 4, "N must be 3 or 4");
		ASSERT_FLOAT(T);

		T s = std::sin(radians);
		T c = std::cos(radians);
		T ic = T(1) - c;

		if constexpr (N == 3)
		{
			vector<3, T> a1(
				c + axis.x * axis.x * ic,
				axis.x * axis.y * ic + axis.z * s,
				axis.x * axis.z * ic - axis.y * s);

			vector<3, T> a2(
				axis.x * axis.y * ic - axis.z * s,
				c + axis.y * axis.y * ic,
				axis.y * axis.z * ic + axis.x * s);

			vector<3, T> a3(
				axis.x * axis.z * ic + axis.y * s,
				axis.y * axis.z * ic - axis.x * s,
				c + axis.z * axis.z * ic);

			return matrix<3, T>(a1, a2, a3);
		}
		else
		{
			vector<4, T> a1(
				c + axis.x * axis.x * ic,
				axis.x * axis.y * ic + axis.z * s,
				axis.x * axis.z * ic - axis.y * s,
				T(0));

			vector<4, T> a2(
				axis.x * axis.y * ic - axis.z * s,
				c + axis.y * axis.y * ic,
				axis.y * axis.z * ic + axis.x * s,
				T(0));

			vector<4, T> a3(
				axis.x * axis.z * ic + axis.y * s,
				axis.y * axis.z * ic - axis.x * s,
				c + axis.z * axis.z * ic,
				T(0));

			vector<4, T> a4(T(0), T(0), T(0), T(1));

			return matrix<4, T>(a1, a2, a3, a4);
		}
	}

	template <uint8_t N, typename T>
	matrix<N, T> rotate(const matrix<N, T>& rotated, const vector<3, T>& axis, T radians)
	{
		return rotated * rodriguesMatrix<N, T>(axis, radians);
	}

	template <uint8_t N, typename T>
	matrix<N, T> scale(const matrix<N, T>& scaled, const vector<3, T>& scale_vec)
	{
		static_assert(N == 3 || N == 4, "N must be 3 or 4");
		ASSERT_FLOAT(T);

		if constexpr (N == 3)
		{
			return matrix<3, T>(
				scaled.a * scale_vec.x,
				scaled.b * scale_vec.y,
				scaled.c * scale_vec.z);
		}
		else
		{
			return matrix<4, T>(
				vector<4, T>(scaled.a.x * scale_vec.x, scaled.a.y * scale_vec.x, scaled.a.z * scale_vec.x, scaled.a.w),
				vector<4, T>(scaled.b.x * scale_vec.y, scaled.b.y * scale_vec.y, scaled.b.z * scale_vec.y, scaled.b.w),
				vector<4, T>(scaled.c.x * scale_vec.z, scaled.c.y * scale_vec.z, scaled.c.z * scale_vec.z, scaled.c.w),
				scaled.d);
		}
	}

	template <typename T>
	matrix<4, T> translate(const matrix<4, T>& translated, const vector<3, T>& translation)
	{
		ASSERT_FLOAT(T);

		if (translated[3][3] == T(1))
		{
			matrix<4, T> ret(T(1));
			ret.a = vector<4, T>(vector<3, T>(translated.a), translated.a.w + translation.x);
			ret.b = vector<4, T>(vector<3, T>(translated.b), translated.b.w + translation.y);
			ret.c = vector<4, T>(vector<3, T>(translated.c), translated.c.w + translation.z);
			return ret;
		}
		return translated;
	}

	// tuple [view matrix, right vector, up vector]
	template <typename T>
	auto lookAtLH_EXT(const vector<3, T>& eye_pos, const vector<3, T>& look_dir, const vector<3, T>& up)
	{
		ASSERT_FLOAT(T);
		vector<3, T> z = look_dir;
		vector<3, T> x = xm::normalize(xm::crossLH(z, up));
		vector<3, T> y = xm::normalize(xm::crossLH(x, z));
		vector<3, T> t = xm::vec3(xm::dot(-eye_pos, x), xm::dot(-eye_pos, y), xm::dot(-eye_pos, z));

		matrix<4, T> ret(T(1));
		ret.a = vector<4, T>(x, t.x);
		ret.b = vector<4, T>(y, t.y);
		ret.c = vector<4, T>(z, t.z);
		return std::make_tuple(ret, x, y);
	}

	template <typename T>
	auto lookAtRH_EXT(const vector<3, T>& eye_pos, const vector<3, T>& look_dir, const vector<3, T>& up)
	{
		ASSERT_FLOAT(T);
		vector<3, T> z = -look_dir;
		vector<3, T> x = xm::normalize(xm::crossRH(up, z));
		vector<3, T> y = xm::normalize(xm::crossRH(z, x));
		vector<3, T> t = xm::vec3(xm::dot(-eye_pos, x), xm::dot(-eye_pos, y), xm::dot(-eye_pos, z));

		matrix<4, T> ret(T(1));
		ret.a = vector<4, T>(x, t.x);
		ret.b = vector<4, T>(y, t.y);
		ret.c = vector<4, T>(z, t.z);
		return std::make_tuple(ret, x, y);
	}

	template <typename T>
	matrix<4, T> lookAtLH(const vector<3, T>& eye_pos, const vector<3, T>& look_dir, const vector<3, T>& up)
	{
		return std::get<0>(lookAtLH_EXT(eye_pos, look_dir, up));
	}

	template <typename T>
	matrix<4, T> lookAtRH(const vector<3, T>& eye_pos, const vector<3, T>& look_dir, const vector<3, T>& up)
	{
		return std::get<0>(lookAtRH_EXT(eye_pos, look_dir, up));
	}

	template <typename T>
	matrix<4, T> lookAt(const vector<3, T>& eye_pos, const vector<3, T>& look_dir, const vector<3, T>& world_up = vector<3, T>(T(0), T(1), T(0)))
	{
#ifdef XM_LEFT_HANDED
		return lookAtLH(eye_pos, look_dir, world_up);
#else
		return lookAtRH(eye_pos, look_dir, world_up);
#endif
	}

	template <typename T>
	matrix<4, T> perspectiveLH(T fov_vert_radians, T aspect, T near, T far, bool z_ndc_min_edge_is_zero = false)
	{
		ASSERT_FLOAT(T);
		T half_tan = std::tan(fov_vert_radians / T(2));
		T A = z_ndc_min_edge_is_zero ? (-far / (near - far)) : (-(near + far) / (near - far));
		T B = far - far * A;

		matrix<4, T> ret;
		ret.a = vector<4, T>(T(1) / (half_tan * aspect), T(0), T(0), T(0));
		ret.b = vector<4, T>(T(0), T(1) / half_tan, T(0), T(0));
		ret.c = vector<4, T>(T(0), T(0), A, B);
		ret.d = vector<4, T>(T(0), T(0), T(1), T(0));
		return ret;
	}

	template <typename T>
	matrix<4, T> perspectiveRH(T fov_vert_radians, T aspect, T near, T far, bool z_ndc_min_edge_is_zero = false)
	{
		ASSERT_FLOAT(T);
		T half_tan = std::tan(fov_vert_radians / T(2));
		T A = z_ndc_min_edge_is_zero ? (-far / (far - near)) : (-(near + far) / (far - near));
		T B = far + far * A;

		matrix<4, T> ret;
		ret.a = vector<4, T>(T(1) / (half_tan * aspect), T(0), T(0), T(0));
		ret.b = vector<4, T>(T(0), T(1) / half_tan, T(0), T(0));
		ret.c = vector<4, T>(T(0), T(0), A, B);
		ret.d = vector<4, T>(T(0), T(0), T(-1), T(0));
		return ret;
	}

	template <typename T>
	inline matrix<4, T> perspective(T fov_vert_radians, T aspect, T near, T far, bool z_ndc_min_edge_is_zero = false)
	{
#ifdef XM_LEFT_HANDED
		return perspectiveLH(fov_vert_radians, aspect, near, far, z_ndc_min_edge_is_zero);
#else
		return perspectiveRH(fov_vert_radians, aspect, near, far, z_ndc_min_edge_is_zero);
#endif
	}

	template <typename T>
	matrix<4, T> orthographicLH_EXT(T top, T bottom, T right, T left, T near, T far)
	{
		ASSERT_FLOAT(T);
		T t_minus_b = top - bottom;
		T n_minus_f = near - far;
		T r_minus_l = right - left;

		vector<4, T> a(T(2) / r_minus_l, T(0), T(0), T(0));
		vector<4, T> b(T(0), T(2) / t_minus_b, T(0), T(0));
		vector<4, T> c(T(0), T(0), T(-2) / n_minus_f, T(0));
		vector<4, T> d(
			-(right + left) / r_minus_l,
			-(top + bottom) / t_minus_b,
			(far + near) / n_minus_f,
			T(1));

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	matrix<4, T> orthographicLH_STRIP(T top, T right, T near, T far)
	{
		ASSERT_FLOAT(T);
		T n_minus_f = near - far;

		vector<4, T> a(T(1) / right, T(0), T(0), T(0));
		vector<4, T> b(T(0), T(1) / top, T(0), T(0));
		vector<4, T> c(T(0), T(0), T(-2) / n_minus_f, T(0));
		vector<4, T> d(T(0), T(0), (far + near) / n_minus_f, T(1));

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	inline matrix<4, T> orthographicRH_EXT(T top, T bottom, T right, T left, T near, T far)
	{
		ASSERT_FLOAT(T);
		T t_minus_b = top - bottom;
		T n_minus_f = near - far;
		T r_minus_l = right - left;

		vector<4, T> a(T(2) / r_minus_l, T(0), T(0), T(0));
		vector<4, T> b(T(0), T(2) / t_minus_b, T(0), T(0));
		vector<4, T> c(T(0), T(0), T(2) / n_minus_f, T(0));
		vector<4, T> d(
			-(right + left) / r_minus_l,
			-(top + bottom) / t_minus_b,
			(far + near) / n_minus_f,
			T(1));

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	inline matrix<4, T> orthographicRH_STRIP(T top, T right, T near, T far)
	{
		ASSERT_FLOAT(T);
		T n_minus_f = near - far;

		vector<4, T> a(T(1) / right, T(0), T(0), T(0));
		vector<4, T> b(T(0), T(1) / top, T(0), T(0));
		vector<4, T> c(T(0), T(0), T(2) / n_minus_f, T(0));
		vector<4, T> d(T(0), T(0), (far + near) / n_minus_f, T(1));

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	inline matrix<4, T> orthographic(T top, T bottom, T right, T left, T near, T far)
	{
#ifdef XM_LEFT_HANDED
		return orthographicLH_EXT(top, bottom, right, left, near, far);
#else
		return orthographicRH_EXT(top, bottom, right, left, near, far);
#endif
	}

#undef ASSERT_FLOAT

} // namespace xm

#pragma pop_macro("near")
#pragma pop_macro("far")