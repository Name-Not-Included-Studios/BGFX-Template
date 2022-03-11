#pragma once

#include <bgfx/bgfx.h>

struct QuadVerts {
    // 3d space position
    float m_x;
    float m_y;
    float m_z;

    // Color value
    //uint32_t m_abgr;

    float m_tx;
    float m_ty;

    static void init() {
        // start the attribute declaration
        quad_layout
            .begin()
            // Has three float values that denote position
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            // and a uint8 color value that denotes color
            //.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
            .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
            .end();
    };

    static bgfx::VertexLayout quad_layout;
};

bgfx::VertexLayout QuadVerts::quad_layout;

//static CubeQuad s_quadVertices[] =
//{
//    { 1.0f, 1.0f, 0.0f, 0xff0000ff },
//    { 1.0f, 0.0f, 0.0f, 0xff0000ff },
//    { 0.0f, 0.0f, 0.0f, 0xff00ff00 },
//    { 0.0f, 1.0f, 0.0f, 0xff00ff00 }
//};

static QuadVerts s_quadVertices[] =
{
    /*    POSITION    /  TXCOORDS  */
    { 1.0f, 1.0f, 0.0f, 1.0f, 1.0f },
    { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f }
};

static const uint16_t s_quadTriList[] =
{
    0,1,3,
    1,2,3
};