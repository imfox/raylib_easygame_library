#include <raylib.h>
#include "Stage.h"
#include "Runtime.h"

ds::Stage::Stage()
{
}

void ds::Stage::render()
{
	if (this->viewport) {
		BeginMode2D(*this->viewport);
		this->$render();
		EndMode2D();
	} else {
		this->$render();
	}
}

void ds::Stage::update() {
	ds::touchManager->update();
}

void ds::Stage::gameLoop()
{
	while (WindowShouldClose() == false) {
		update();
		BeginDrawing();
		render();
		EndDrawing();
	}

}
