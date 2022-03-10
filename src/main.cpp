/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */
#define BX_CONFIG_DEBUG true

#include <iostream>
#include <stdio.h>
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>



#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include <GLFW/glfw3native.h>

//#include "BGFX_Callback.h"

#include "vs_cubes.gl.h"
#include "fs_cubes.gl.h"

const float verts[] =
{
	0.0, 0.0, 0.0,
	1.0, 1.0, 0.0,
	1.0, 0.0, 1.0,
};

const int indices[] =
{
	0, 1, 2,
	1, 3, 2,
};




static bool s_showStats = false;

static void glfw_errorCallback(int error, const char* description)
{
	fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

static void glfw_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F1 && action == GLFW_RELEASE)
		s_showStats = !s_showStats;
}

int main(int argc, char** argv)
{
	// Create a GLFW window without an OpenGL context.
	glfwSetErrorCallback(glfw_errorCallback);

	if (!glfwInit())
		return 1;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(1600, 900, "Hello bgfx!", nullptr, nullptr);

	if (!window)
		return 1;

	glfwSetKeyCallback(window, glfw_keyCallback);
	// Call bgfx::renderFrame before bgfx::init to signal to bgfx not to create a render thread.
	// Most graphics APIs must be used on the same thread that created the window.
	bgfx::renderFrame();

	// Initialize bgfx using the native window handle and window resolution.
	bgfx::Init init;

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
	init.platformData.ndt = glfwGetX11Display();
	init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(window);
#elif BX_PLATFORM_OSX
	init.platformData.nwh = glfwGetCocoaWindow(window);
#elif BX_PLATFORM_WINDOWS
	init.platformData.nwh = glfwGetWin32Window(window);
#endif

	//BgfxCallback m_callback;

	int width, height;
	glfwGetWindowSize(window, &width, &height);
	init.type = bgfx::RendererType::OpenGL; // automatically choose a renderer.
	//init.callback = m_callback;
	init.resolution.width = (uint32_t)width;
	init.resolution.height = (uint32_t)height;
	init.resolution.reset = BGFX_RESET_VSYNC;

	if (!bgfx::init(init))
		return 1;


	// Set view 0 to the same dimensions as the window and to clear the color buffer.
	const bgfx::ViewId kClearView = 0;
	bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
	bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);


	// Shader Stuff

	auto vertexShaderData = bgfx::copy(vs_cubes, 728);
	auto fragmentShaderData = bgfx::copy(fs_cubes, 681);

	auto vertexShader = bgfx::createShader(vertexShaderData);
	auto fragmentShader = bgfx::createShader(fragmentShaderData);


	// Program stuff
	auto shaderProgram = bgfx::createProgram(vertexShader, fragmentShader, true);



	// Vertex Layout Stuff
	bgfx::VertexLayout vertexLayout = bgfx::VertexLayout();
	vertexLayout
		.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Float)
		.end();

	bgfx::VertexLayoutHandle vertexLayoutHandle = bgfx::createVertexLayout(vertexLayout);


	// Vertex Data Memory
	//auto vertexData = bgfx::copy(verts, 9);
	//const bgfx::Memory* vertexData = bgfx::makeRef(verts, 9);
	auto vertexData = bgfx::makeRef(verts, sizeof(verts));

	// bgfx::DynamicVertexBufferHandle
	auto vertexBuf = bgfx::createDynamicVertexBuffer(
		vertexData,
		vertexLayout,
		BGFX_BUFFER_ALLOW_RESIZE
	);

	// Index Data
	auto indexData = bgfx::makeRef(indices, sizeof(indices));
	/*bgfx::DynamicIndexBufferHandle indexBuf = bgfx::createDynamicIndexBuffer(
		indexData,
		BGFX_BUFFER_NONE
	);*/
	auto indexBuf = bgfx::createDynamicIndexBuffer(
		indexData,
		BGFX_BUFFER_ALLOW_RESIZE
	);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// Handle window resize.
		int oldWidth = width, oldHeight = height;
		glfwGetWindowSize(window, &width, &height);

		if (width != oldWidth || height != oldHeight) {
			bgfx::reset((uint32_t)width, (uint32_t)height, BGFX_RESET_VSYNC);
			bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
		}



		// This dummy draw call is here to make sure that view 0 is cleared if no other draw calls are submitted to view 0.
		//bgfx::touch(kClearView);



		bgfx::setVertexBuffer(0, vertexBuf);
		bgfx::setIndexBuffer(indexBuf);

		bgfx::setState(BGFX_STATE_DEFAULT);

		bgfx::submit(kClearView, shaderProgram);



		// Use debug font to print information about this example.
		//bgfx::dbgTextClear();

		//const bgfx::Stats* stats = bgfx::getStats();

		// Enable stats or debug text.
		//bgfx::setDebug(s_showStats ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);

		// Advance to next frame. Process submitted rendering primitives.
		bgfx::frame();
	}


	bgfx::destroy(shaderProgram);

	// bgfx::destroy(vertexShaderData);
	// bgfx::destroy(fragmentShaderData);

	bgfx::destroy(vertexBuf);
	bgfx::destroy(indexBuf);

	bgfx::shutdown();
	glfwTerminate();
	return 0;
}