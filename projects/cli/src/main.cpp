#include <iostream>

#define MIN_MAP_GRAPH 0
#define MAX_MAP_GRAPH 767

#define R_OFFSET 0
#define G_OFFSET 256
#define B_OFFSET 512

long map_graph_color(long position, long offset)
{
	//loop position around, phases can loop around
	position = position + offset > MAX_MAP_GRAPH ? (position + offset) - MAX_MAP_GRAPH : position + offset;

	//get graph value
	long y = 0;
	if (position < 256)
	{
		y = position;
	}
	else if (position > 255 && position < 512)
	{
		y = position - 256;
	}
	else
	{
		y = 0;
	}
	return y;
}
unsigned char test(long position, long offset);
void get_color_from_graph(long position)
{
	std::cout << "pos: " << position << std::endl;

	unsigned char r = test(position, R_OFFSET);
	unsigned char g = test(position, G_OFFSET);
	unsigned char b = test(position, B_OFFSET);

	std::cout << "r: " << (int)r << std::endl;
	std::cout << "g: " << (int)g << std::endl;
	std::cout << "b: " << (int)b << std::endl;
	std::cout << std::endl;
	//helper::log_rgb(rgb(r, g, b), true);
	//
	//return rgb(r, g, b);
}


unsigned char test(long position, long offset)
{
	//loop pos around 0-767
	position = position + offset > MAX_MAP_GRAPH ? (position + offset) - MAX_MAP_GRAPH : position + offset;

	//generate the graph
	if (position <= 255)
	{
		return static_cast<unsigned char>(position);
	}

	if (position >= 256 && position <= 511)
	{
		return static_cast<unsigned char>(255 - (position- 256));
	}

	return 0;
}

int main()
{
	get_color_from_graph(255);
	get_color_from_graph(256);
	get_color_from_graph(257);
	return 0;
}