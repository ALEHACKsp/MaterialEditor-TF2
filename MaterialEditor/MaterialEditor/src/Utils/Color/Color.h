#pragma once
#include "../Vector/Vector.h"

using byte = unsigned char;

struct Color_t { byte r = 0, g = 0, b = 0, a = 0; };

namespace Color
{
	inline float TOFLOAT(byte x) {
		return (static_cast<float>(x) / 255.0f);
	}

	inline Vector TOVEC3(const Color_t &x) {
		return Vector(TOFLOAT(x.r), TOFLOAT(x.g), TOFLOAT(x.b));
	}

	inline unsigned long TODWORD(const Color_t &x) {
		return (static_cast<unsigned long>(((x.r & 0xFF) << 24) | ((x.g & 0xFF) << 16) | ((x.b & 0xFF) << 8) | (x.a & 0xFF)));
	}
}