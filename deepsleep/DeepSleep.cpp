#include "DeepSleep.h"

ds::Loader* ds::loader;
ds::Stage* ds::stage;
ds::TouchManager* ds::touchManager;
ds::Validator* ds::validator;

void ds::init(int width, int height) {
	ds::loader = new Loader();
	ds::validator = new Validator();
	ds::stage = new Stage();
	ds::stage->size(width, height);
	ds::touchManager = new TouchManager(ds::stage);
}
