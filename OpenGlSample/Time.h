#pragma once
#include <Windows.h>

class Time
{
public:
	LARGE_INTEGER _nowFrameCounter;
	LARGE_INTEGER _prevFrameCounter;
	LARGE_INTEGER _frameInfo;

	double _perFrame;
	int count;
	int _targetFrame;

	void init();
	bool isRenderTiming();
};