#pragma once

#include <fstream>



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
		std::cerr << "Shader Buffer was too small! (needed: " << length << ")" << std::endl;
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

//static const bgfx::TextureHandle loadTexture(const char* _filePath)
//{
//	auto textureMem = load(_filePath);
//
//	return bgfx::createTexture2D(
//		bgfx::BackbufferRatio::Equal,
//		true,
//		1,
//		bgfx::TextureFormat::RGBA8I
//	);
//}