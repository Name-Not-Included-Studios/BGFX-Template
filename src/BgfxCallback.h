#pragma once

#include "bgfx/bgfx.h"

//#include <iostream>

//class BGFX_Callback : public bgfx::CallbackI
//{
//	void fatal(const char* _filePath, uint16_t _line, bgfx::Fatal::Enum _code, const char* _str) override
//	{
//		std::cout << "Fatal Error at: (" << _filePath << ":" << _line << ")\nCode: (" << _code << ")\nMessage : " << _str << std::endl;
//	}
//
//	void traceVargs(const char* _filePath, uint16_t _line, const char* _format, va_list _argList) override
//	{
//		std::cout << "Debug Message at: (" << _filePath << ":" << _line << ")\nCode: (" << _format << ")\nMessage : " << _argList << std::endl;
//	}
//};



//void savePng(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, bimg::TextureFormat::Enum _format, bool _yflip)
//{
//	bx::FileWriter writer;
//	bx::Error err;
//	if (bx::open(&writer, _filePath, false, &err))
//	{
//		bimg::imageWritePng(&writer, _width, _height, _srcPitch, _src, _format, _yflip, &err);
//		bx::close(&writer);
//	}
//}
//
//void saveTga(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, bool _grayscale, bool _yflip)
//{
//	bx::FileWriter writer;
//	bx::Error err;
//	if (bx::open(&writer, _filePath, false, &err))
//	{
//		bimg::imageWriteTga(&writer, _width, _height, _srcPitch, _src, _grayscale, _yflip, &err);
//		bx::close(&writer);
//	}
//}
//
//struct BgfxCallback : public bgfx::CallbackI
//{
//	virtual ~BgfxCallback()
//	{
//	}
//
//	virtual void fatal(const char* _filePath, uint16_t _line, bgfx::Fatal::Enum _code, const char* _str) override
//	{
//		BX_UNUSED(_filePath, _line);
//
//		// Something unexpected happened, inform user and bail out.
//		bx::debugPrintf("Fatal error: 0x%08x: %s", _code, _str);
//
//		// Must terminate, continuing will cause crash anyway.
//		abort();
//	}
//
//	virtual void traceVargs(const char* _filePath, uint16_t _line, const char* _format, va_list _argList) override
//	{
//		bx::debugPrintf("%s (%d): ", _filePath, _line);
//		bx::debugPrintfVargs(_format, _argList);
//	}
//
//	virtual void profilerBegin(const char* /*_name*/, uint32_t /*_abgr*/, const char* /*_filePath*/, uint16_t /*_line*/) override
//	{
//	}
//
//	virtual void profilerBeginLiteral(const char* /*_name*/, uint32_t /*_abgr*/, const char* /*_filePath*/, uint16_t /*_line*/) override
//	{
//	}
//
//	virtual void profilerEnd() override
//	{
//	}
//
//	virtual uint32_t cacheReadSize(uint64_t _id) override
//	{
//		char filePath[256];
//		bx::snprintf(filePath, sizeof(filePath), "temp/%016" PRIx64, _id);
//
//		// Use cache id as filename.
//		bx::FileReaderI* reader = entry::getFileReader();
//		bx::Error err;
//		if (bx::open(reader, filePath, &err))
//		{
//			uint32_t size = (uint32_t)bx::getSize(reader);
//			bx::close(reader);
//			// Return size of shader file.
//			return size;
//		}
//
//		// Return 0 if shader is not found.
//		return 0;
//	}
//
//	virtual bool cacheRead(uint64_t _id, void* _data, uint32_t _size) override
//	{
//		char filePath[256];
//		bx::snprintf(filePath, sizeof(filePath), "temp/%016" PRIx64, _id);
//
//		// Use cache id as filename.
//		bx::FileReaderI* reader = entry::getFileReader();
//		bx::Error err;
//		if (bx::open(reader, filePath, &err))
//		{
//			// Read shader.
//			uint32_t result = bx::read(reader, _data, _size, &err);
//			bx::close(reader);
//
//			// Make sure that read size matches requested size.
//			return result == _size;
//		}
//
//		// Shader is not found in cache, needs to be rebuilt.
//		return false;
//	}
//
//	virtual void cacheWrite(uint64_t _id, const void* _data, uint32_t _size) override
//	{
//		char filePath[256];
//		bx::snprintf(filePath, sizeof(filePath), "temp/%016" PRIx64, _id);
//
//		// Use cache id as filename.
//		bx::FileWriterI* writer = entry::getFileWriter();
//		bx::Error err;
//		if (bx::open(writer, filePath, false, &err))
//		{
//			// Write shader to cache location.
//			bx::write(writer, _data, _size, &err);
//			bx::close(writer);
//		}
//	}
//
//	virtual void screenShot(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t /*_size*/, bool _yflip) override
//	{
//		char temp[1024];
//
//		// Save screen shot as PNG.
//		bx::snprintf(temp, BX_COUNTOF(temp), "%s.png", _filePath);
//		savePng(temp, _width, _height, _pitch, _data, bimg::TextureFormat::BGRA8, _yflip);
//
//		// Save screen shot as TGA.
//		bx::snprintf(temp, BX_COUNTOF(temp), "%s.tga", _filePath);
//		saveTga(temp, _width, _height, _pitch, _data, false, _yflip);
//	}
//
//	virtual void captureBegin(uint32_t _width, uint32_t _height, uint32_t /*_pitch*/, bgfx::TextureFormat::Enum /*_format*/, bool _yflip) override
//	{
//		m_writer = BX_NEW(entry::getAllocator(), AviWriter)(entry::getFileWriter());
//		if (!m_writer->open("temp/capture.avi", _width, _height, 60, _yflip))
//		{
//			BX_DELETE(entry::getAllocator(), m_writer);
//			m_writer = NULL;
//		}
//	}
//
//	virtual void captureEnd() override
//	{
//		if (NULL != m_writer)
//		{
//			m_writer->close();
//			BX_DELETE(entry::getAllocator(), m_writer);
//			m_writer = NULL;
//		}
//	}
//
//	virtual void captureFrame(const void* _data, uint32_t /*_size*/) override
//	{
//		if (NULL != m_writer)
//		{
//			m_writer->frame(_data);
//		}
//	}
//
//	AviWriter* m_writer;
//};