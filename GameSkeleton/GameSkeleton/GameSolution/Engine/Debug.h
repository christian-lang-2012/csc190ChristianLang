#ifndef DEBUG_H
#define DEBUG_H

#include "Core.h"
#include "Matrix3.h"

using Engine::Matrix3;

#include <sstream>

using std::stringstream;
using std::ceil;
using std::floor;

namespace Debug{
	inline float Debug_RoundValue(float val){
		int normalized = (int)(val * 1000.0f);
		return normalized / 1000.0f;
	}

	inline void Drawvalue( Core::Graphics& graphics, int x, int y, float num ) {
		stringstream ss;
		ss << num;
		graphics.DrawString( x, y, ss.str().c_str());
	}

	inline void Drawvalue( Core::Graphics& graphics, int x, int y, int num ) {
		stringstream ss;
		ss << num;
		graphics.DrawString( x, y, ss.str().c_str());
	}
}

#endif