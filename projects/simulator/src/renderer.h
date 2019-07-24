#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

enum class draw_state {
	histogram,
	graph,
};

enum class screen_state 
{
	all,
	cpu_temp,
	cpu_load,
	gpu_temp,
	gpu_load,
};

class renderer
{
public:
	renderer();
	~renderer();

	void draw(const std::vector<float>* cpu_temperatures, const std::vector<float>* cpu_loads, const std::vector<float>* gpu_temperatures, const std::vector<float>* gpu_loads);
	void poll_events();

	GLFWwindow* m_window;
private:
	bool draw_plot(const std::vector<float>* data, float min, float max, std::string text, screen_state* screen_state, draw_state* draw_state, ImGuiIO& io);

	//const float ySlope = (outMaxY - outMinY) / (inMaxY - inMinY);
	const float draw_slope = (1.0f - 0.0f) / (100 - 20);

	const int window_width = 480;
	const int window_height = 320;

	const unsigned int plot_width  = 230;
	const unsigned int plot_height = 150;

	const unsigned int plot_fullscreen_width = 460;
	const unsigned int plot_fullscreen_height = 280;

	bool m_show_lines = true;
	
	screen_state m_screen_state = screen_state::all;
	draw_state m_cpu_temp_draw_state = draw_state::graph;
	draw_state m_cpu_load_draw_state = draw_state::graph;
	draw_state m_gpu_temp_draw_state = draw_state::graph;
	draw_state m_gpu_load_draw_state = draw_state::graph;
};




