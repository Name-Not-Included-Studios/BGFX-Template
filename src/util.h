#pragma once

//static void shaderFilePath(char* _out, const char* _name)
//{
//	strcpy(_out, "");
//	strcat(_out, _name);
//	strcat(_out, ".gl");
//}

#include <fstream>

//long int fsize(FILE* _file)
//{
//	long int pos = ftell(_file);
//	fseek(_file, 0L, SEEK_END);
//	long int size = ftell(_file);
//	fseek(_file, pos, SEEK_SET);
//	return size;
//}

//static const bgfx::Memory* loadFOPEN(const char* _filePath)
//{
//	FILE* file = fopen(_filePath, "rb");
//	if (NULL != file)
//	{
//		uint32_t size = (uint32_t)fsize(file);
//		const bgfx::Memory* mem = bgfx::alloc(size + 1);
//		size_t ignore = fread(mem->data, 1, size, file);
//		BX_UNUSED(ignore);
//		fclose(file);
//		mem->data[mem->size - 1] = '\0';
//		return mem;
//	}
//
//	return NULL;
//}

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

//#include "bgfx/bgfx.h"
//#include <bx/readerwriter.h>
//
//static const bgfx::Memory* loadMem(bx::FileReaderI* _reader, const char* _filePath)
//{
//	if (bx::open(_reader, _filePath))
//	{
//		uint32_t size = (uint32_t)bx::getSize(_reader);
//		const bgfx::Memory* mem = bgfx::alloc(size + 1);
//		bx::read(_reader, mem->data, size, bx::ErrorAssert{});
//		bx::close(_reader);
//		mem->data[mem->size - 1] = '\0';
//		return mem;
//	}
//
//	DBG("Failed to load %s.", _filePath);
//	return NULL;
//}
//
//static bgfx::ShaderHandle loadShader(bx::FileReaderI* _reader, const char* _name)
//{
//	char filePath[512];
//
//	const char* shaderPath = "???";
//
//	switch (bgfx::getRendererType())
//	{
//	case bgfx::RendererType::Noop:
//	case bgfx::RendererType::Direct3D9:  shaderPath = "shaders/dx9/";   break;
//	case bgfx::RendererType::Direct3D11:
//	case bgfx::RendererType::Direct3D12: shaderPath = "shaders/dx11/";  break;
//	case bgfx::RendererType::Agc:
//	case bgfx::RendererType::Gnm:        shaderPath = "shaders/pssl/";  break;
//	case bgfx::RendererType::Metal:      shaderPath = "shaders/metal/"; break;
//	case bgfx::RendererType::Nvn:        shaderPath = "shaders/nvn/";   break;
//	case bgfx::RendererType::OpenGL:     shaderPath = "shaders/glsl/";  break;
//	case bgfx::RendererType::OpenGLES:   shaderPath = "shaders/essl/";  break;
//	case bgfx::RendererType::Vulkan:     shaderPath = "shaders/spirv/"; break;
//	case bgfx::RendererType::WebGPU:     shaderPath = "shaders/spirv/"; break;
//
//	case bgfx::RendererType::Count:
//		BX_ASSERT(false, "You should not be here!");
//		break;
//	}
//
//	bx::strCopy(filePath, BX_COUNTOF(filePath), shaderPath);
//	bx::strCat(filePath, BX_COUNTOF(filePath), _name);
//	bx::strCat(filePath, BX_COUNTOF(filePath), ".bin");
//
//	bgfx::ShaderHandle handle = bgfx::createShader(loadMem(_reader, filePath));
//	bgfx::setName(handle, _name);
//
//	return handle;
//}
//
//bgfx::ShaderHandle loadShader(const char* _name)
//{
//	return loadShader(entry::getFileReader(), _name);
//}
//
//bgfx::ProgramHandle loadProgram(bx::FileReaderI* _reader, const char* _vsName, const char* _fsName)
//{
//	bgfx::ShaderHandle vsh = loadShader(_reader, _vsName);
//	bgfx::ShaderHandle fsh = BGFX_INVALID_HANDLE;
//	if (NULL != _fsName)
//	{
//		fsh = loadShader(_reader, _fsName);
//	}
//
//	return bgfx::createProgram(vsh, fsh, true /* destroy shaders when program is destroyed */);
//}
//
//bgfx::ProgramHandle loadProgram(const char* _vsName, const char* _fsName)
//{
//	return loadProgram(entry::getFileReader(), _vsName, _fsName);
//}