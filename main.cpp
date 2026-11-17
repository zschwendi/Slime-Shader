#include "Slime_Shader.h"
#include <cmath>
#include <iostream>

int main() {

	int width = 0;
	int height = 0;
	int effect = 0;
	double elapsed_seconds = 0.0;

	//have user provide the image settings
	std::cout << "Width (1-2048): ";
	std::cin >> width;
	std::cout << "Height (1-2048): ";
	std::cin >> height;
	std::cout << "Time in seconds: ";
	std::cin >> elapsed_seconds;
	std::cout << "Effect (1 = RainbowWave, 2 = RainbowGoop): ";
	std::cin >> effect;


	//input validation
	if (!std::cin || width < 1 || width > 2048 || height < 1 || height > 2048 ||
		!std::isfinite(elapsed_seconds) || (effect != 1 && effect != 2)) {
		std::cout << "Invalid settings. Use dimensions from 1 to 2048, a finite time, and effect 1 or 2.\n";
		return 1;
	}


	//init selected shader
	SlimeShader shader(height, width, 4.0, 0.25);
	if (effect == 1)
		shader.RainbowWave(elapsed_seconds);
	else
		shader.RainbowGoop(elapsed_seconds);

	//print every pixel in the requested frame to the console
	std::cout << "Rendered " << width << " x " << height << " at " << elapsed_seconds << " seconds.\n";
	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++) {
			std::cout << "Pixel (" << row << ", " << column << ") RGB: "
				<< shader.getChannel(row, column, 0) << ", "
				<< shader.getChannel(row, column, 1) << ", "
				<< shader.getChannel(row, column, 2) << "\n";
		}
	return 0;
}
