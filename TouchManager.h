#pragma once
#include "Stage.h"
#include "Enum.h"
#include "DisplayObject.h"
#include <unordered_set>
#include <unordered_map>

namespace ds {

	typedef int TouchID;

	class TouchManager {
	private:
		Vector2	mousePositionLast = { 0 };
		std::uint16_t doubleClickTime = 500;

	public:
		bool disabled = false;
		TouchMode mode = TouchMode::Touch;
		Stage* stage = nullptr;
		std::unordered_set<TouchID> touchList;
		std::unordered_map<TouchID, DisplayObject*> touchNodes;

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
