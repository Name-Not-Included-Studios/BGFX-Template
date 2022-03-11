#pragma once

#include <bgfx/bgfx.h>

struct CubeQuad {
    // 3d space position
    float m_x;
    float m_y;
    float m_z;
    // Color value
    uint32_t m_abgr;

    static void init() {
        // start the attribute declaration
        cube_layout
            .begin()
            // Has three float values that denote position
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            // and a uint8 color value that denotes color
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
            .end();
    };

    static bgfx::VertexLayout cube_layout;
};

bgfx::VertexLayout CubeQuad::cube_layout;

static CubeQuad s_quadVertices[] =
{
    { 1.0f, 1.0f, 0.0f, 0xff0000ff },
    { 1.0f, 0.0f, 0.0f, 0xff0000ff },
    { 0.0f, 0.0f, 0.0f, 0xff00ff00 },
    { 0.0f, 1.0f, 0.0f, 0xff00ff00 }
};

static const uint16_t s_quadTriList[] =
{
    0,1,3,
    1,2,3
};