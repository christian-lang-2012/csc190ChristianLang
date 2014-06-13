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

	inline void Drawvalue( Core::Graphics& graphics, int x, int y, unsigned int num ) {
		stringstream ss;
		ss << num;
		graphics.DrawString( x, y, ss.str().c_str());
	}

	inline void Drawvalue( Core::Graphics& graphics, int x, int y, int num ) {
		stringstream ss;
		ss << num;
		graphics.DrawString( x, y, ss.str().c_str());
	}

	inline void DrawDebugStuff(Core::Graphics& g)
	{
		#ifdef _DEBUG
		_CrtMemState localState;
		_CrtMemCheckpoint(&localState);

		std::stringstream ss;

		ss << "Block Count: "<<localState.lCounts[_CLIENT_BLOCK] << "\n"
			<<"Total Bytes/Blocks: " << localState.lSizes[_CLIENT_BLOCK]<<"\n"
			<<"Most Bytes EVER: "<< localState.lHighWaterCount;
		g.DrawString(10,10,ss.str().c_str());
		#endif
	}
}

#endif