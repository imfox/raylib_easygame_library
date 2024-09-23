#pragma once
#include "Loader.h"
#include "Stage.h"
#include "TouchManager.h"
#include "Validator.h"

namespace ds {
	extern ds::Stage* stage;
	extern ds::Loader* loader;
	extern ds::TouchManager* touchManager;
	extern ds::Validator* validator;
} // namespace ds