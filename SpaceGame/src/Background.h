#pragma once

#include "Hazel.h"

class Background
{
private:

public:
	Background();
	~Background();

	void init();
	void draw();
	void update(Hazel::Timestep ts);
};
