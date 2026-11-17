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
								              const double radians_per_cycle = 6.283185307179586;//2 pi rads in a cycle							  
	for (int row = 0; row < getHeight(); row++)
		for (int column = 0; column < getWidth(); column++) {
		

			double x = static_cast<double>(column) / getWidth(); //turn into a fractional value

				double wave_position =
					x * m_animation_density - animation_cycles; // Position along the moving wave
				double angle = wave_position * radians_per_cycle; // Convert the wave position to radians
								


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
}// this function renders the wave animation by offsetting each channel and mapping their x coordinates to a point in the animation's wave cycle
void SlimeShader::RainbowGoop(double elapsed_seconds) {
	RainbowWave(elapsed_seconds);//make the rainbow wave first
	Image rainbow = *this;//make a copy so we don't overwrite colors we still need
	double animation_cycles = elapsed_seconds * m_animation_speed;
	const double radians_per_cycle = 6.283185307179586;
	//same as rainbow wave


	for (int row = 0; row < getHeight(); row++) {
		for (int column = 0; column < getWidth(); column++) {
			double x = static_cast<double>(column) / getWidth();
				double y = static_cast<double>(row) / getHeight();//use fractional positions so the pattern scales with image size

			//bend the waves using x, y, and time
			double source_x = x
					+ 0.25 * std::sin((y + animation_cycles * 0.2) * radians_per_cycle)//bend the rows sideways with a moving sine wave
					+ 0.20 * std::sin((x + y - animation_cycles * 0.15) * radians_per_cycle);//add another sideways bend that varies diagonally.
														 //The goop animation can be altered by changing these magic numbers, or changing from sin to cos

			source_x -= std::floor(source_x);//wrap around for coherency
			int source_column = static_cast<int>(source_x * getWidth()) % getWidth();

			//copy the original colors to this pixel
			for (int channel = 0; channel < 3; channel++) {

				setChannel(row, column, channel, rainbow.getChannel(row, source_column, channel));
			}
		}
	}
}//takes RainbowWave and modifies it to look goopier by stretching the wave lines in either direction with two more sin/time calculations
