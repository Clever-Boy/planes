#pragma once

namespace math {
    template <typename T>
    T lerp(const T & A, const T & B, const T & t) {
	return A * t + (1 - t) * B;
    }
}
