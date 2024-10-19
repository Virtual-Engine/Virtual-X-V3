#pragma once
#include "common.hpp"
#include "invoker/Natives.hpp"
using namespace VX;

class SpriteAnimation {
public:
	SpriteAnimation() {};
	SpriteAnimation(int delay, bool backAndForth) : m_delay(delay), m_backAndForth(backAndForth) {}

	void AddTexture(Texture texture) {
		m_textures.push_back(texture);
		if (!m_currentTexture) m_currentTexture = &m_textures[0];
	}
	void DrawSpriteV3(Texture texture, float x, float y, float w, float h, float heading, RGBA color, bool renderIfNotStreamed) {
		bool streamed = GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(texture.dict);
		if (streamed || renderIfNotStreamed) GRAPHICS::DRAW_SPRITE(texture.dict, texture.id, x, y, w, h, heading, color.r, color.g, color.b, color.a);
		if (!streamed) GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(texture.dict, 0);
	}
	void Draw(float x, float y, float w, float h, RGBA color = { 255, 255, 255, 255 }) {
		DrawSpriteV3(GetCurrentTexture(), x, y, w, h, 0, color, true);
	}

private:
	bool m_backAndForth;
	bool m_isGoingBackwards;
	int m_timer;
	int m_current;
	int m_delay;
	Texture* m_currentTexture;
	std::vector<Texture> m_textures;

	Texture& GetCurrentTexture() {
		g_utility.DoTimedFunctionV2(&m_timer, m_delay);
			if (!m_backAndForth) { if (m_current++ >= m_textures.size() - 1) m_current = 0; }
			else {
				if (m_isGoingBackwards) {
					if (m_current-- <= 0) {
						m_current = 1;
						m_isGoingBackwards = false;
					}
				}
				else {
					if (m_current++ >= m_textures.size() - 1) {
						m_current = m_textures.size() - 2;
						m_isGoingBackwards = true;
					}
				}
			}
			m_currentTexture = &m_textures[m_current];
			

		return *m_currentTexture;
	}
};