#pragma once

#include <cmath>
#include "matrix.h"
#include <tuple>

#pragma push_macro("near")
#pragma push_macro("far")
#undef near
#undef far

namespace xm
{
	template <uint8_t N, typename T, typename K = float>
	matrix<N, K> eulRotZ(T radians)
	{
		static_assert(N == 3 || N == 4, "N must be 3 or 4");
		T cos_theta = cos(radians);
		T sin_theta = sin(radians);
		if constexpr (N == 4)
		{
			vector<4, K> a(cos_theta, sin_theta, 0.0, 0.0);
			vector<4, K> b(-sin_theta, cos_theta, 0.0, 0.0);
			vector<4, K> c(0.0, 0.0, 1.0, 0.0);
			vector<4, K> d(0.0, 0.0, 0.0, 1.0);

			matrix<4, K> res(a, b, c, d);
			return res;
		}
		else
		{
			vector<3, K> a(cos_theta, sin_theta, 0.0);
			vector<3, K> b(-sin_theta, cos_theta, 0.0);
			vector<3, K> c(0.0, 0.0, 1.0);

			matrix<3, K> res(a, b, c);
			return res;
		}
	}

	template <uint8_t N, typename T, typename K = float>
	matrix<N, K> eulRotX(T radians)
	{
		static_assert(N == 3 || N == 4, "N must be 3 or 4");
		T cos_theta = cos(radians);
		T sin_theta = sin(radians);
		if constexpr (N == 4)
		{
			vector<4, K> a(1.0, 0.0, 0.0, 0.0);
			vector<4, K> b(0.0, cos_theta, sin_theta, 0.0);
			vector<4, K> c(0.0, -sin_theta, cos_theta, 0.0);
			vector<4, K> d(0.0, 0.0, 0.0, 1.0);

			matrix<4, K> res(a, b, c, d);
			return res;
		}
		else
		{
			vector<3, K> a(1.0, 0.0, 0.0);
			vector<3, K> b(0.0, cos_theta, sin_theta);
			vector<3, K> c(0.0, -sin_theta, cos_theta);

			matrix<3, K> res(a, b, c);
			return res;
		}
	}

	template <uint8_t N, typename T, typename K = float>
	matrix<N, K> eulRotY(T radians)
	{
		static_assert(N == 3 || N == 4, "N must be 3 or 4");
		T cos_theta = cos(radians);
		T sin_theta = sin(radians);
		if constexpr (N == 4)
		{
			vector<4, K> a(cos_theta, 0.0, -sin_theta, 0.0);
			vector<4, K> b(0.0, 1.0, 0.0, 0.0);
			vector<4, K> c(sin_theta, 0.0, cos_theta, 0.0);
			vector<4, K> d(0.0, 0.0, 0.0, 1.0);

			matrix<4, K> res(a, b, c, d);
			return res;
		}
		else
		{
			vector<3, K> a(cos_theta, 0.0, -sin_theta);
			vector<3, K> b(0.0, 1.0, 0.0);
			vector<3, K> c(sin_theta, 0.0, cos_theta);

			matrix<3, K> res(a, b, c);
			return res;
		}
	}

	// axis must be unit vector
	template <uint8_t N, typename T, typename K>
	matrix<N, T> rodriguesMatrix(vector<3, T> axis, K radians)
	{
		static_assert(N == 3 || N == 4, "N must be 3 or 4");
		T s = sin(radians);
		T c = cos(radians);
		T ic = 1 - c;
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

			matrix<3, T> res(a1, a2, a3);
			return res;
		}
		else
		{
			vector<4, T> a1(
				c + axis.x * axis.x * ic,
				axis.x * axis.y * ic + axis.z * s,
				axis.x * axis.z * ic - axis.y * s,
				0.0);

			vector<4, T> a2(
				axis.x * axis.y * ic - axis.z * s,
				c + axis.y * axis.y * ic,
				axis.y * axis.z * ic + axis.x * s,
				0.0);

			vector<4, T> a3(
				axis.x * axis.z * ic + axis.y * s,
				axis.y * axis.z * ic - axis.x * s,
				c + axis.z * axis.z * ic,
				0.0);
			vector<4, T> a4(
				0.0,
				0.0,
				0.0,
				1.0);

			matrix<4, T> res(a1, a2, a3, a4);
			return res;
		}
	}

	// axis		- asix of rotation, must be unit vector
	// rotated	- rotated vector
	// radians	- angle in radians
	template <uint8_t N, typename T, typename K, typename W>
	matrix<N, T> rotate(const matrix<N, T>& rotated, vector<3, K> axis, W radians)
	{
		static_assert(N == 3 || N == 4, "N must be 3 or 4");
		matrix<N, T> rotation_matrix = rodriguesMatrix<N>(axis, radians);
		return rotated * rotation_matrix;
	}

	template <uint8_t N, typename T, typename K>
	matrix<N, T> scale(const matrix<N, T>& scaled, vector<3, K> scale_vec)
	{
		static_assert(N == 3 || N == 4, "N must be 3 or 4");
		if constexpr (N == 3)
		{
			vector<3, T> a = scaled.a * scale_vec.x;
			vector<3, T> b = scaled.b * scale_vec.y;
			vector<3, T> c = scaled.c * scale_vec.z;
			return matrix<3, T>(a, b, c);
		}
		else
		{
			vector<4, T> a = vector<4, T>(scaled.a.x * scale_vec.x,
				scaled.a.y * scale_vec.x,
				scaled.a.z * scale_vec.x,
				scaled.a.w);
			vector<4, T> b = vector<4, T>(scaled.b.x * scale_vec.y,
				scaled.b.y * scale_vec.y,
				scaled.b.z * scale_vec.y,
				scaled.b.w);
			vector<4, T> c = vector<4, T>(scaled.c.x * scale_vec.z,
				scaled.c.y * scale_vec.z,
				scaled.c.z * scale_vec.z,
				scaled.c.w);
			vector<4, T> d = scaled.d;
			return matrix<4, T>(a, b, c, d);
		}
	}

	template <typename T, typename K>
	matrix<4, T> translate(const matrix<4, T>& translated, vector<3, K> translation)
	{
		if (translated[3][3] == T(1.0))
		{
			matrix<4, T> ret(1.0);
			ret.a = vector<4, T>(vector<3, T>(translated.a), translated.a.w + translation.x);
			ret.b = vector<4, T>(vector<3, T>(translated.b), translated.b.w + translation.y);
			ret.c = vector<4, T>(vector<3, T>(translated.c), translated.c.w + translation.z);
			return ret;
		}
		return translated;
	}

	// eye_pos	-	view position
	// look_dir	-	direction of view, must be unit
	// world_up -	world up vector, must be unit
	// return	-	tuple [view matrix, right vector, up vector]
	template <typename T, typename K, typename W>
	auto lookAtLH_EXT(vector<3, T> eye_pos, vector<3, K> look_dir, vector<3, W> up)
	{
		using type = mul_result_t<T, K, W>;
		xm::vector<3, type> z = look_dir;
		xm::vector<3, type> x = xm::normalize(xm::crossLH(z, up));
		xm::vector<3, type> y = xm::normalize(xm::crossLH(x, z));
		xm::vector<3, type> t = xm::vec3(dot(-eye_pos, x), dot(-eye_pos, y), dot(-eye_pos, z));

		xm::matrix<4, type> ret(1.0);
		ret.a = xm::vector<4, type>(x, t.x);
		ret.b = xm::vector<4, type>(y, t.y);
		ret.c = xm::vector<4, type>(z, t.z);
		return std::make_tuple(ret, x, y);
	}

	// eye_pos	-	view position
	// look_dir	-	direction of view, must be unit
	// world_up -	world up vector, must be unit
	// return	-	tuple [view matrix, right vector, up vector]
	template <typename T, typename K, typename W>
	auto lookAtRH_EXT(vector<3, T> eye_pos, vector<3, K> look_dir, vector<3, W> up)
	{
		using type = mul_result_t<T, K, W>;
		xm::vector<3, type> z = -look_dir;
		xm::vector<3, type> x = xm::normalize(xm::crossRH(up, z));
		xm::vector<3, type> y = xm::normalize(xm::crossRH(z, x));
		xm::vector<3, type> t = xm::vec3(dot(-eye_pos, x), dot(-eye_pos, y), dot(-eye_pos, z));

		xm::matrix<4, type> ret(1.0);
		ret.a = xm::vector<4, type>(x, t.x);
		ret.b = xm::vector<4, type>(y, t.y);
		ret.c = xm::vector<4, type>(z, t.z);
		return std::make_tuple(ret, x, y);
	}

	template <typename T, typename K, typename W>
	auto lookAtLH(vector<3, T> eye_pos, vector<3, K> look_dir, vector<3, W> up)
	{
		return std::get<0>(lookAtLH_EXT(eye_pos, look_dir, up));
	}

	template <typename T, typename K, typename W>
	auto lookAtRH(vector<3, T> eye_pos, vector<3, K> look_dir, vector<3, W> up)
	{
		return std::get<0>(lookAtRH_EXT(eye_pos, look_dir, up));
	}

	// eye_pos	-	view position
	// look_dir	-	direction of view, must be unit
	// world_up -	world up vector, must be unit
	// return	-	tuple [view matrix, right vector, up vector]
	template <typename T, typename K, typename W>
	auto lookAt(vector<3, T> eye_pos, vector<3, K> look_dir, vector<3, W> world_up = vector<3, W>(0.0, 1.0, 0.0))
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
		T half_tan = std::tan(fov_vert_radians / T(2.0));
		T A;
		if (z_ndc_min_edge_is_zero)
		{
			A = -far / (near - far);
		}
		else
		{
			A = -(near + far) / (near - far);
		}
		T B = far - far * A;

		xm::matrix<4, T> ret;
		ret.a = xm::vector<4, T>(1.0 / (half_tan * aspect), 0.0, 0.0, 0.0);
		ret.b = xm::vector<4, T>(0.0, 1.0 / half_tan, 0.0, 0.0);
		ret.c = xm::vector<4, T>(0.0, 0.0, A, B);
		ret.d = xm::vector<4, T>(0.0, 0.0, 1.0, 0.0);
		return ret;
	}

	template <typename T>
	matrix<4, T> perspectiveRH(T fov_vert_radians, T aspect, T near, T far, bool z_ndc_min_edge_is_zero = false)
	{
		T half_tan = std::tan(fov_vert_radians / T(2.0));
		T A;
		if (z_ndc_min_edge_is_zero)
		{
			A = -far / (far - near);
		}
		else 
		{
			A = -(near + far) / (far - near);
		}
		T B = far + far * A;
		
		xm::matrix<4, T> ret;
		ret.a = xm::vector<4, T>(1.0 / (half_tan * aspect), 0.0, 0.0, 0.0);
		ret.b = xm::vector<4, T>(0.0, 1.0 / half_tan, 0.0, 0.0);
		ret.c = xm::vector<4, T>(0.0, 0.0, A, B);
		ret.d = xm::vector<4, T>(0.0, 0.0, -1.0, 0.0);
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
		T t_minus_b = top - bottom;
		T n_minus_f = near - far;
		T r_minus_l = right - left;

		vector<4, T> a(2.0 / r_minus_l, 0.0, 0.0, 0.0);
		vector<4, T> b(0.0, 2.0 / t_minus_b, 0.0, 0.0);
		vector<4, T> c(0.0, 0.0, -2.0 / n_minus_f, 0.0);
		vector<4, T> d(
			-(right + left) / r_minus_l,
			-(top + bottom) / t_minus_b,
			(far + near) / n_minus_f,
			1.0);

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	matrix<4, T> orthographicLH_STRIP(T top, T right, T near, T far)
	{
		T n_minus_f = near - far;

		vector<4, T> a(1.0 / right, 0.0, 0.0, 0.0);
		vector<4, T> b(0.0, 1.0 / top, 0.0, 0.0);
		vector<4, T> c(0.0, 0.0, -2.0 / n_minus_f, 0.0);
		vector<4, T> d(0.0, 0.0, (far + near) / n_minus_f, 1.0);

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	inline matrix<4, T> orthographicRH_EXT(T top, T bottom, T right, T left, T near, T far)
	{
		T t_minus_b = top - bottom;
		T n_minus_f = near - far;
		T r_minus_l = right - left;

		vector<4, T> a(2.0 / r_minus_l, 0.0, 0.0, 0.0);
		vector<4, T> b(0.0, 2.0 / t_minus_b, 0.0, 0.0);
		vector<4, T> c(0.0, 0.0, 2.0 / n_minus_f, 0.0);
		vector<4, T> d(
			-(right + left) / r_minus_l,
			-(top + bottom) / t_minus_b,
			(far + near) / n_minus_f,
			1.0);

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	inline matrix<4, T> orthographicRH_STRIP(T top, T right, T near, T far)
	{
		T n_minus_f = near - far;

		vector<4, T> a(1.0 / right, 0.0, 0.0, 0.0);
		vector<4, T> b(0.0, 1.0 / top, 0.0, 0.0);
		vector<4, T> c(0.0, 0.0, 2.0 / n_minus_f, 0.0);
		vector<4, T> d(0.0, 0.0, (far + near) / n_minus_f, 1.0);

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
} // namespace xm

#pragma pop_macro("near")
#pragma pop_macro("far")