#include "simulator_pch.h"
#include "renderer.h"

renderer::renderer() 
{
	glfwInit();

	m_window = glfwCreateWindow(window_width, window_height, "Tempy", nullptr, nullptr);
	glfwMakeContextCurrent(m_window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL2_Init();

	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//ImGui::PushFont(io.Fonts->Fonts[0]);
}

renderer::~renderer()
{
}

void renderer::poll_events()
{
	glfwPollEvents();
}

void renderer::draw(const std::vector<float>* cpu_temperatures, const std::vector<float>* cpu_loads, const std::vector<float>* gpu_temperatures, const std::vector<float>* gpu_loads)
{
	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == 1)
	{
		glfwSetWindowShouldClose(m_window, 1);
	}


	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	bool open = true;
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(window_width, window_height), ImGuiSetCond_Always);
	ImGui::Begin("main window", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	bool mouse_clicked = io.MouseClicked[0];


	switch (m_screen_state)
	{
		case screen_state::all:

			if (draw_plot(cpu_temperatures, 20.0f, 100.0f, "CPU temperature", &m_screen_state, &m_cpu_temp_draw_state, io))
			{
				m_screen_state = screen_state::cpu_temp;
			}
			ImGui::SameLine();
			if (draw_plot(cpu_loads, 0.0f, 100.0f, "CPU load", &m_screen_state, &m_cpu_load_draw_state, io))
			{
				m_screen_state = screen_state::cpu_load;
			}
			
			if (draw_plot(gpu_temperatures, 20.0f, 100.0f, "GPU temperature", &m_screen_state, &m_gpu_temp_draw_state, io))
			{
				m_screen_state = screen_state::gpu_temp;
			}
			ImGui::SameLine();
			if (draw_plot(gpu_loads, 0.0f, 100.0f, "GPU load", &m_screen_state, &m_gpu_load_draw_state, io))
			{
				m_screen_state = screen_state::gpu_load;
			}
			break;

		case screen_state::cpu_temp:
			draw_plot(cpu_temperatures, 20.0f, 100.0f, "CPU temperature", &m_screen_state, &m_cpu_temp_draw_state, io);
			break;

		case screen_state::cpu_load:
			draw_plot(cpu_loads, 0.0f, 100.0f, "CPU load", &m_screen_state, &m_cpu_load_draw_state, io);
			break;

		case screen_state::gpu_temp:
			draw_plot(gpu_temperatures, 20.0f, 100.0f, "GPU temperature", &m_screen_state, &m_gpu_temp_draw_state, io);
			break;

		case screen_state::gpu_load:
			draw_plot(gpu_loads, 0.0f, 100.0f, "GPU load", &m_screen_state, &m_gpu_load_draw_state, io);
			break;

		default:
			std::cout << "ilegal state." << std::endl;
			break;
	}

	ImGui::End();

	//bool yes = false;
	//ImGui::ShowDemoWindow(&yes);

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(m_window);
}

//Draws the plot in the given state. Updates the state according to button pressses. Returns true if the plot is clicked
bool renderer::draw_plot(const std::vector<float>* data, float min, float max, std::string text, screen_state* screen_state, draw_state* draw_state, ImGuiIO& io)
{
	//Screenstate all means we are not in fullscreen mode. 
	if(*screen_state == screen_state::all)
	{
		if (*draw_state == draw_state::graph)
		{
			ImGui::PlotLines("", data->data(), data->size(), 0, text.c_str(), min, max, ImVec2(plot_width, plot_height));
		}
		else
		{
			ImGui::PlotHistogram("", data->data(), data->size(), 0, text.c_str(), min, max, ImVec2(plot_width, plot_height));
		}
	}
	else
	{
		//Exit fullscreen
		if (ImGui::Button("back"))
		{
			*screen_state = screen_state::all;
		}

		ImGui::SameLine();

		//Configure the draw method for this plot
		if (ImGui::Button("graph"))
		{
			*draw_state = draw_state::graph;
		}
		ImGui::SameLine();
		if (ImGui::Button("histogram"))
		{
			*draw_state = draw_state::histogram;
		}

		if (*draw_state == draw_state::graph)
		{
			ImGui::PlotLines("", data->data(), data->size(), 0, text.c_str(), min, max, ImVec2(plot_fullscreen_width, plot_fullscreen_height));
		}
		else
		{
			ImGui::PlotHistogram("", data->data(), data->size(), 0, text.c_str(), min, max, ImVec2(plot_fullscreen_width, plot_fullscreen_height));
		}
	}
	
	return ImGui::IsItemHovered() && io.MouseClicked[0];
}
