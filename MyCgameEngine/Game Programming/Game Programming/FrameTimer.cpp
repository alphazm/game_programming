#include "FrameTimer.h"
#include <profileapi.h>

void FrameTimer::Init(int fps)
{
	QueryPerformanceFrequency(&timer_freq);
	QueryPerformanceCounter(&time_now);
	QueryPerformanceCounter(&time_previous);

	requestedFPS = fps;

	intervalsPerFrame = (float)(timer_freq.QuadPart / requestedFPS);
}

int FrameTimer::FramesToUpdate()
{
	int framesToUpdate = 0;

	QueryPerformanceCounter(&time_now);

	deltaTime = time_now.QuadPart - time_previous.QuadPart;
	framesToUpdate = (int)(deltaTime / intervalsPerFrame);
	if (framesToUpdate != 0)
		QueryPerformanceCounter(&time_previous);
	return framesToUpdate;
}
