# raylib_easynode
raylib_easynode

### usage

```
#include "deepsleep/Import.h"

int main() {
	InitWindow(1280, 720, "testGame");
	SetTargetFPS(60);
	ds::init(1280, 720);

	ds::loader->load("0.png");
	ds::DisplayObject::defaultTouchEnabled = true;

	auto stage = ds::stage;
	auto image = new ds::Image();
	image->setSkin("0.png")->addTo(stage);

	while (WindowShouldClose() == false) {
		stage->update();

		BeginDrawing();
		stage->render();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

```
