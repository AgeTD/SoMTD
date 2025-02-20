#include <iostream>

#include "game.h"
#include "./player.hpp"

#include <ijengine/canvas.h>
#include <ijengine/engine.h>
#include <ijengine/texture.h>

#include "texture_bar.h"

SoMTD::TextureBar::TextureBar(std::string texture_name, unsigned id, int x, int y, int s_offset, int e_offset) :
    m_id(id),
    m_x(x),
    m_y(y),
    m_start(-1),
    m_priority(500100),
    m_percentage(50.0),
    m_start_offset(s_offset),
    m_end_offset(e_offset)
{
    m_texture = ijengine::resources::get_texture(texture_name);
    ijengine::event::register_listener(this);
}

SoMTD::TextureBar::~TextureBar()
{
    ijengine::event::unregister_listener(this);
}

bool
SoMTD::TextureBar::on_event(const ijengine::GameEvent&)
{
    return false;
}

void
SoMTD::TextureBar::draw_self(ijengine::Canvas *canvas, unsigned, unsigned)
{
    ijengine::Rectangle offset1 { 0, 0, (m_texture->w()*(m_percentage/100)), (double)m_texture->h() };
    canvas->draw(m_texture.get(), offset1, m_x, m_y);
}

void
SoMTD::TextureBar::update_self(unsigned, unsigned)
{
    if (player::get().hp() > 1) {
        m_percentage = (player::get().hp() *100/50);
    }
}
