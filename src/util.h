#pragma once

#include <fstream>
#include "bgfx/bgfx.h"
#include "bgfx/platform.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "util/util.hpp"

static const bgfx::Memory* load(const char* _filePath)
{
	//FILE* file = fopen(_filePath, "rb");
	char buffer[4096];

	std::ifstream file;
	file.open(_filePath);

	//get length of file
	file.seekg(0, std::ios::end);
	size_t length = file.tellg();
	file.seekg(0, std::ios::beg);

	// don't overflow the buffer!
	if (length > sizeof(buffer))
	{
		std::cerr << "File Buffer was too small! (needed: " << length << ")" << std::endl;
		length = sizeof(buffer);
	}

	//read file
	file.read(buffer, length);

	return bgfx::copy(buffer, length);
}

static const bgfx::ShaderHandle loadShader(const char* _path)
{
	//char filePath[512];
	//shaderFilePath(filePath, _name);
	return bgfx::createShader(load(_path));
}

static const bgfx::ProgramHandle loadProgram(const char* _vertName, const char* _fragName)
{
	return bgfx::createProgram(loadShader(_vertName), loadShader(_fragName), true);
}

inline util::Result<std::tuple<glm::ivec2, bgfx::TextureHandle>, std::string>
load_texture(const std::string& path) {
	// load image with stb_image
	glm::ivec2 size;
	int channels;
	stbi_set_flip_vertically_on_load(true);
	u8* data = stbi_load(path.c_str(), &size.x, &size.y, &channels, 0);

	auto res =
		bgfx::createTexture2D(
			size.x, size.y,
			false, 1,
			bgfx::TextureFormat::RGBA8,
			BGFX_SAMPLER_U_CLAMP
			| BGFX_SAMPLER_V_CLAMP
			| BGFX_SAMPLER_MIN_POINT
			| BGFX_SAMPLER_MAG_POINT,
			bgfx::copy(data, size.x * size.y * channels));

	if (!bgfx::isValid(res)) {
		return util::Err("Error loading texture " + path);
	}

	std::free(data);
	return util::Ok(std::tuple(size, res));
}

//static const bgfx::TextureHandle loadTexture(const char* _filePath)
//{
//	auto textureMem = load(_filePath);
//
//	return bgfx::createTexture2D(
//		w,
//		h,
//		false,
//		1,
//		bgfx::TextureFormat::RGB8,
//		BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE,
//		bgfx::copy(image, len));
//}