#include "Slime_Shader.h"
#include <cmath>

SlimeShader::SlimeShader(int height,int width,double density, double speed) 
	: Image(height,width) ,
	m_animation_density(density),
	m_animation_speed(speed)
{
}// constructor


void SlimeShader::RainbowWave(double elapsed_seconds) {
	double animation_cycles = elapsed_seconds * m_animation_speed;//tracks how many cycles have occurred				      
								              const double radians_per_cycle = 6.283185307179586;//a cycle = 2pi radians (this is for sin math calculations)
							  
	for (int row = 0; row < getHeight(); row++)
		for (int column = 0; column < getWidth(); column++) {
		

			double x = static_cast<double>(column) / getWidth(); //turn into a fractional value

				double wave_position =
					x * m_animation_density - animation_cycles; // Position along the moving wave
				double angle = wave_position * radians_per_cycle; // Convert the wave position to radians for sin.
								


			//offset the waves by 3rds
			double red_wave = std::sin(angle);

			double green_wave = std::sin(angle + radians_per_cycle / 3.0);
			double blue_wave = std::sin(angle + 2.0 * radians_per_cycle / 3.0);
			
			//calculate each pixel value in range from  0-255
			int red = static_cast<int>((red_wave + 1.0) * 127.5);
			int green = static_cast<int>((green_wave + 1.0) * 127.5);
			int blue = static_cast<int>((blue_wave + 1.0) * 127.5);

			setChannel(row, column, 0, red);
			setChannel(row, column, 1, green);
			setChannel(row, column, 2, blue);
		}
}// function that renders the shader animation
