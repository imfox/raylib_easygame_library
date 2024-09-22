#pragma once
#include "Stage.h"
#include "DisplayObject.h"
namespace ds {

	typedef int TouchID;

	class TouchManager {
	private:
		Vector2	mousePositionLast;
		std::uint16_t doubleClickTime = 500;

	public:
		Stage* stage = nullptr;
		bool disabled = false;

	public:
		TouchManager(Stage* stage);
		void update();
		DisplayObject* hitTest(DisplayObject* start, TouchID id, Vector2 pos);
		DisplayObject* hitNodeTest(DisplayObject* node, Vector2 pos, bool touchThrough);
		void cancelTouchChildren(DisplayObject* endNode, TouchID id);
		void onTouchBegin(DisplayObject* node, TouchID id, const Vector2 pos);
		void onTouchMove(DisplayObject* node, TouchID id, const Vector2 pos);
		void onTouchEnd(DisplayObject* node, TouchID id, const Vector2 pos);
	};
} // namespace ds
