#include "Image.h"
#pragma once


class SlimeShader : public Image{

	private:

		double m_animation_density;
		double m_animation_speed;

	public:

SlimeShader(int height, int width, double density, double speed);//constructor -returns nothing, passes height/width to image parent class

void RainbowWave(double elapsed_seconds);// recieves a value in seconds of where to start animating from. 

};

