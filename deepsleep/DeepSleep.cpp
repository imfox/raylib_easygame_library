#include "DeepSleep.h"

ds::Loader* ds::loader;
ds::Stage* ds::stage;
ds::TouchManager* ds::touchManager;

void ds::init(int width, int height) {
	ds::loader = new Loader();
	ds::stage = (new Stage());
	stage->size(width, height);
	ds::touchManager = new TouchManager(ds::stage);
}
