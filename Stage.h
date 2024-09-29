#pragma once
#include "DisplayObjectContainer.h"

namespace ds {
	class Stage : public DisplayObjectContainer {
	public:
		::Camera2D* viewport = nullptr;
		Stage();
		Stage(const Stage& s) = delete;
	public:
		void render();
		void setViewport(int x, int y, int width, int height);
		void update();
		void gameLoop();
	};
}