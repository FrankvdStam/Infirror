#include "simulator_pch.h"
#include "renderer.h"

renderer* r;


void renderer_run()
{
	while (!glfwWindowShouldClose(r->m_window))
	{
		r->poll_events();
	}
}

int main(int argc, char* argv[]) 
{
	r = new renderer();
	renderer_run();	
	return 0;
}
