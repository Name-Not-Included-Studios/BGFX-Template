/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */
#define BX_CONFIG_DEBUG true

#include <iostream>
#include <stdio.h>

#include <bx/bx.h>
#include <bx/math.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <glm/matrix.hpp>
#include <glm/gtx/transform.hpp>

#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

 //#include "BGFX_Callback.h"

 //#include "data/vs_cubes.gl.h"
 //#include "data/fs_cubes.gl.h"

#include "cube.h"
#include "util.h"

const float verts[] =
{
	/*   Position   /      Color      */
	0.0f, 0.0f, 1.0f,//   1.0f, 0.0f, 0.0f, 1.0f, // 0
	0.0f, 1.0f, 1.0f,//   0.0f, 1.0f, 0.0f, 1.0f, // 1
	1.0f, 1.0f, 1.0f,//   0.0f, 0.0f, 1.0f, 1.0f, // 2
	1.0f, 0.0f, 1.0f,//   1.0f, 1.0f, 1.0f, 1.0f, // 3
};

const uint32_t indices[] =
{
	0, 1, 2,
	0, 2, 3,
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

int test_main(int argc, char** argv)
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
	bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR, 0x88aaffff);
	bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);





	// Shader Stuff

	//auto vertexShaderData = bgfx::copy(vs_cubes, sizeof(vs_cubes));// - USED
	//auto fragmentShaderData = bgfx::copy(fs_cubes, sizeof(fs_cubes));// - USED

	//auto vertexShader = bgfx::createShader(vertexShaderData);// - USED
	//auto fragmentShader = bgfx::createShader(fragmentShaderData);// - USED



	//auto vertexShaderData = loadShader("vs_cubes");
	//auto fragmentShaderData = loadShader("fs_cubes");

	//auto vertexShader = bgfx::createShader(vertexShaderData);// - USED
	//auto fragmentShader = bgfx::createShader(fragmentShaderData);// - USED

	// Program stuff
	//auto shaderProgram = bgfx::createProgram(vertexShader, fragmentShader, false);// - USED
	//auto shaderProgram = loadProgram("vs_cubes.gl", "fs_cubes.gl");

	// Uniform and Attribute Stuff
	//auto u_modelViewProj = bgfx::createUniform("u_modelViewProj", bgfx::UniformType::Mat4);
	//bgfx::setUniform(u_modelViewProj, );
	//auto s_texStipple = bgfx::createUniform("a_color0", bgfx::UniformType::Sampler);
	// _stipple = bgfx::createUniform("u_stipple", bgfx::UniformType::Vec4);

	// Vertex Layout Stuff
	bgfx::VertexLayout vertexLayout = bgfx::VertexLayout();
	vertexLayout
		.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();

	//bgfx::VertexLayoutHandle vertexLayoutHandle = bgfx::createVertexLayout(vertexLayout);



	/*
	// Vertex Data Memory
	auto vertexData = bgfx::copy(verts, sizeof(verts));// - USED

	// bgfx::DynamicVertexBufferHandle
	auto vertexBuf = bgfx::createDynamicVertexBuffer(
		vertexData,
		vertexLayout,
		BGFX_BUFFER_ALLOW_RESIZE
	);// - USED

	// Index Data
	auto indexData = bgfx::copy(indices, sizeof(indices));// - USED

	auto indexBuf = bgfx::createDynamicIndexBuffer(
		indexData,
		BGFX_BUFFER_ALLOW_RESIZE | BGFX_BUFFER_INDEX32
	);// - USED
	*/





	bgfx::VertexBufferHandle vertexBuf;
	bgfx::IndexBufferHandle indexBuf;
	//bgfx::ProgramHandle m_program; // we create a program handle
	auto shaderProgram = loadProgram("vs_cubes.gl", "fs_cubes.gl");

	//bgfx::ShaderHandle vsh = loadShader("v_simple.bin");
	//bgfx::ShaderHandle fsh = loadShader("f_simple.bin");
	//m_program = bgfx::createProgram(vsh, fsh, true);

	PosColorVertex::init();
	vertexBuf = bgfx::createVertexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices)),
		PosColorVertex::ms_decl
	);

	indexBuf = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList))
	);

	float bearing = 0.0f;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// Handle window resize.
		int oldWidth = width, oldHeight = height;
		glfwGetWindowSize(window, &width, &height);

		if (width != oldWidth || height != oldHeight) {
			bgfx::reset((uint32_t)width, (uint32_t)height, BGFX_RESET_VSYNC);
			bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
		}


		bgfx::setState(BGFX_STATE_DEFAULT);

		// This dummy draw call is here to make sure that view 0 is cleared if no other draw calls are submitted to view 0.
		bgfx::touch(kClearView);


		bgfx::setState(BGFX_STATE_DEFAULT);

		bgfx::setVertexBuffer(0, vertexBuf);// - USED
		//bgfx::setVertexBuffer(0, vertexBuf, 0, (sizeof(verts) / (sizeof(float))), vertexLayoutHandle);
		bgfx::setIndexBuffer(indexBuf);// - USED

		{
			glm::mat4 view;

			{
				float pitch = 0.0f;
				bearing += 0.01f;

				std::cout << "Bearing: " << bearing << std::endl;

				// define your up vector
				glm::vec3 upVector = glm::vec3(0, 1, 0);
				// rotate around to a given bearing: yaw
				glm::mat4 camera = glm::rotate(glm::mat4(), bearing, upVector);
				// Define the 'look up' axis, should be orthogonal to the up axis
				glm::vec3 pitchVector = glm::vec3(1, 0, 0);
				// rotate around to the required head tilt: pitch
				camera = glm::rotate(camera, pitch, pitchVector);

				// now get the view matrix by taking the camera inverse
				view = glm::inverse(camera);
			}

			/*float viewArr[16];
			const float* pSource = (const float*)glm::value_ptr(pMat4);
			for (int i = 0; i < 16; ++i)
				viewArr[i] = pSource[i];*/

			float proj[16];
			bx::mtxProj(proj, 110.0f, float(width) / float(height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

			bgfx::setViewTransform(0, &view[0][0], proj);
		}


		bgfx::submit(kClearView, shaderProgram);// - USED



		// Use debug font to print information about this example.
		//bgfx::dbgTextClear();

		const bgfx::Stats* stats = bgfx::getStats();

		// Enable stats or debug text.
		bgfx::setDebug(s_showStats ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);

		// Advance to next frame. Process submitted rendering primitives.
		bgfx::frame();
	}


	bgfx::destroy(shaderProgram);// - USED

	// bgfx::destroy(vertexShaderData);
	// bgfx::destroy(fragmentShaderData);

	bgfx::destroy(vertexBuf);// - USED
	bgfx::destroy(indexBuf);// - USED

	bgfx::shutdown();
	glfwTerminate();
	return 0;
}