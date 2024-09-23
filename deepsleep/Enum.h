#pragma once
namespace ds {
	enum TouchMode {
		Mouse = 0,
		Touch,
	};

	enum class LoaderResType {
		None = 0,
		Texture,
	};

	enum class BlendMode {
		NONE = 0,
		ADD,
	};

	enum class FillMode {
		NONE = 0,
		SCALE = 1,
		CLIP,
		HORIZON_CLIP,
		VERTICAL_CLIP,
	};

	enum class TextAlign {
		LEFT = 0,
		CENTER = 1,
		RIGHT = 2,
	};

	enum class TextVAlign {
		TOP = 0,
		MIDDLE = 1,
		BOTTOM = 2,
	};

	enum class Event :int {
		ADD,
		REMOVE,
		ADD_TO_STAGE,
		REMOVE_FROM_STAGE,
		RESIZE,
		WINDOW_FOCUS,
		//ENTER_FRAME,
	};

	enum class KeyboardEvent : int {
		KEY_DOWN = 10,
		KEY_UP,
		KEY_TAP,
	};

	enum class TouchEvent : int {
		TAP = 20,
		TOUCH_BEGIN,
		TOUCH_END,
		TOUCH_ENTER,
		TOUCH_OUT,
		TOUCH_MOVE,
		TOUCH_CANCEL,
		TOUCH_RELEASE_OUTSIDE,
		MOVE,
		RCLICK,
		RMOUSE_BEGIN,
		RMOUSE_END,
		RMOUSE_RELEASE_OUTSIDE,
		MOUSE_WHEEL,
		DOUBLE_CLICK,
		DOUBLE_RCLICK,
	};
}
